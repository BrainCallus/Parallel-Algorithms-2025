#include "generators.cpp"

typedef parlay::sequence<int>::iterator SeqIt;
typedef std::function<void(PSeq<int> &)> QSortingFunc;

static void sortSlice(const int &startIndex, const int &endIndex, PSeq<int> &arr) {
    if (endIndex - startIndex <= 1) {
        return;
    }
    const int x = arr[startIndex + genRandInt(0, endIndex - startIndex - 1)];
    int m1 = startIndex;
    int i = startIndex;
    while (i != endIndex) {
        if (arr[i] < x) {
            std::swap(arr[i], arr[m1]);
            ++m1;
        }
        ++i;
    }

    int m2 = m1;
    i = m1;
    while (i != endIndex) {
        if (arr[i] == x) {
            std::swap(arr[i], arr[m2]);
            ++m2;
        }
        ++i;
    }

    sortSlice(startIndex, m1, arr);
    sortSlice(m2, endIndex, arr);
}


void sequentialQuickSort(PSeq<int> &arr) {
    sortSlice(0, arr.size(), arr);
};

static void sortInternal(const int &startIndex, const int &endIndex, PSeq<int> &arr,
                         const int &bls) {
    const int lenTotal = endIndex - startIndex;
    if (lenTotal <= bls) {
        sortSlice(startIndex, endIndex, arr);
        return;
    }

    auto s = parlay::make_slice(arr.begin() + startIndex, arr.begin() + endIndex);
    const int x = arr[genRandInt(0, lenTotal - 1)];

    auto left = filter(s, [&](const int a) { return a < x; });
    auto right = filter(s, [&](const int a) { return a > x; });

    parlay::parallel_do(
        [&]() {
            sortInternal(0, left.size(), left, bls);
        },
        [&]() {
            sortInternal(0, right.size(), right, bls);
        }
    );

    const size_t midSize = lenTotal - left.size() - right.size();
    const auto lOffset = startIndex + left.size();
    const auto mOffset = lOffset + midSize;
    parlay::parallel_for(0, left.size(),
                         [&](const int i) { arr[startIndex + i] = left[i]; }, bls);
    parlay::parallel_for(0, midSize,
                         [&](const int i) { arr[i + lOffset] = x; }, bls);
    parlay::parallel_for(0, right.size(),
                         [&](const int i) { arr[i + mOffset] = right[i]; }, bls);
}

static void sortInternal2(const int &startIndex, const int &endIndex, PSeq<int> &arr,
                          const int &bls) {
    const int lenTotal = endIndex - startIndex;
    if (lenTotal <= bls) {
        sortSlice(startIndex, endIndex, arr);
        return;
    }

    const auto s = parlay::make_slice(arr.begin() + startIndex, arr.begin() + endIndex);
    const int x = arr[genRandInt(0, lenTotal - 1)];

    PSeq<int> left;
    PSeq<int> right;
    for (int a: s) {
        if (a < x) {
            left.push_back(a);
        } else if (a > x) {
            right.push_back(a);
        }
    }

    parlay::parallel_do(
        [&]() {
            sortInternal2(0, left.size(), left, bls);
        },
        [&]() {
            sortInternal2(0, right.size(), right, bls);
        }
    );

    const size_t midSize = lenTotal - left.size() - right.size();
    const auto lOffset = startIndex + left.size();
    const auto mOffset = lOffset + midSize;
    parlay::parallel_for(0, left.size(),
                         [&](const int i) { arr[startIndex + i] = left[i]; }, bls);
    parlay::parallel_for(0, midSize,
                         [&](const int i) { arr[i + lOffset] = x; }, bls);
    parlay::parallel_for(0, right.size(),
                         [&](const int i) { arr[i + mOffset] = right[i]; }, bls);

    /*const int m = std::max(left.size(), std::max(midSize, right.size()));
    parlay::parallel_for(0, m,
                         [&](const int i) {
                             if(i < left.size()) arr[startIndex + i] = left[i];
                             if(i < midSize) arr[i + lOffset] = x;
                             if(i < right.size()) arr[i + mOffset] = right[i];
                         }, bls);*/
}

static void sortInternal3(const int &startIndex, const int &endIndex, PSeq<int> &arr,
                          const int &bls) {
    const int lenTotal = endIndex - startIndex;
    if (lenTotal <= bls) {
        sortSlice(startIndex, endIndex, arr);
        return;
    }

    const auto s = parlay::make_slice(arr.begin() + startIndex, arr.begin() + endIndex);
    const int x = arr[genRandInt(0, lenTotal - 1)];

    PSeq<int> left;
    PSeq<int> right;
    for (int a: s) {
        if (a < x) {
            left.push_back(a);
        } else if (a > x) {
            right.push_back(a);
        }
    }

    parlay::parallel_do(
        [&]() {
            sortInternal2(0, left.size(), left, bls);
        },
        [&]() {
            sortInternal2(0, right.size(), right, bls);
        }
    );

    const size_t midSize = lenTotal - left.size() - right.size();
    const auto lOffset = startIndex + left.size();
    const auto mOffset = lOffset + midSize;

    for (int i = 0; i < left.size(); ++i) {
        arr[startIndex + i] = left[i];
    }
    for (int i = 0; i < midSize; ++i) {
        arr[lOffset + i] = x;
    }
    for (int i = 0; i < right.size(); ++i) {
        arr[mOffset + i] = right[i];
    }
}

void parallelQuickSortParFull(PSeq<int> &arr, const int &blockSize) {
    sortInternal(0, arr.size(), arr, blockSize);
}

void parallelQuickSortSeqFilter(PSeq<int> &arr, const int &blockSize) {
    sortInternal2(0, arr.size(), arr, blockSize);
}

void parallelQuickSortForkOnly(PSeq<int> &arr, const int &blockSize) {
    sortInternal3(0, arr.size(), arr, blockSize);
}
