#include <iostream>
#include "quick_sort.cpp"

LL runTimed(QSortingFunc &quickSort, PSeq<int> &arr) {
    const auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr);
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

std::function<LL(PSeq<int> &)> runTimedF(QSortingFunc &quickSort) {
    return [&quickSort](PSeq<int> &arr) { return runTimed(quickSort, arr); };
}

std::function<LL(PSeq<int> &)> runWithResultsF(QSortingFunc &quickSort, PSeq<RunResult> &results,
                                               std::function<RunResult(LL, bool)> &resBuilder) {
    return [&quickSort, &results, resBuilder](PSeq<int> &arr) {
        LL t = runTimed(quickSort, arr);
        results.push_back(resBuilder(t, is_sorted(arr)));
        return t;
    };
}

LL approximateRun(const PSeq<int> &sample, const int &nTrials,
                  const std::function<LL(PSeq<int> &)> &runTimedFunc) {
    LL t = 0;
    for (int i = 0; i < nTrials; i++) {
        PSeq<int> arr = sample;
        t += runTimedFunc(arr);
    }

    return t / nTrials;
}


int findOptimalBlock(const int maxSize, const int startExp = 4, const int nTrials = 3) {
    PSeq<int> sample = randIntegersSample(maxSize);
    std::pair<int, LL> bestTime = {-1, LONG_LONG_MAX};

    std::cout << "Started trials to search for the optimal block size" << std::endl;

    int curV = startExp;
    const int maxBs = maxSize / 2;
    const std::function<QSortingFunc(int)> fBuilder = [](int v) {
        return [v](PSeq<int> &a) { parallelQuickSort(a, v); };
    };
    for (int i = 0; curV < maxBs;) {
        QSortingFunc par = fBuilder(curV);
        LL t = approximateRun(sample, nTrials, runTimedF(par));
        if (t < bestTime.second) {
            bestTime = {curV, t};
        }
        std::cout << i << ": block " << curV << " finished in " << t << std::endl;
        ++i;
        curV = 1 << startExp + i;
    }
    std::cout << "Exponential search finished with best time " << bestTime.second << " reached on " << bestTime.first <<
            std::endl;

    const int left = bestTime.first / 2;
    curV = 5 * left / 2;
    int curV2 = curV;
    for (int i = 0; curV > left; ++i) {
        int delta = 1 << (i + startExp);
        curV -= delta;
        curV2 += 1 << delta;
        QSortingFunc par1 = fBuilder(curV);
        QSortingFunc par2 = fBuilder(curV2);
        LL t1 = approximateRun(sample, nTrials, runTimedF(par1));
        LL t2 = approximateRun(sample, nTrials, runTimedF(par2));
        if (t1 < bestTime.second) {
            bestTime = {curV, t1};
        }
        if (t2 < bestTime.second) {
            bestTime = {curV2, t2};
        }
        std::cout << i << ": block " << curV << " finished in " << t1 << "; block " << curV2 << " finished in " << t2 <<
                std::endl;
    }
    std::cout << "2nd phase finished with best time " << bestTime.second << " reached on " << bestTime.first <<
            std::endl;


    return bestTime.first;
}


PSeq<RunResult> runSequential(PSeq<int> &sample, const int &nTrials) {
    PSeq<RunResult> results;
    int lastSortedSize = -1;
    QSortingFunc quickSort = [& lastSortedSize](PSeq<int> &a) {
        sequentialQuickSort(a);
        lastSortedSize = a.size();
    };
    std::function<RunResult(LL, bool)> f = [&lastSortedSize](LL dur, bool isCorrect) {
        return RunResult("Sequential", 1, lastSortedSize, dur, isCorrect);
    };
    auto g = runWithResultsF(quickSort, results, f);
    approximateRun(sample, nTrials, g);
    return results;
}

PSeq<RunResult> runParallel(PSeq<int> &sample, const int &nTrials, const int blockSize) {
    PSeq<RunResult> results;
    QSortingFunc quickSort = [blockSize](PSeq<int> &a) { parallelQuickSort(a, blockSize); };
    std::function<RunResult(LL, bool)> f = [&blockSize](const LL dur, const bool isCorrect) {
        int curThreads = parlay::num_workers();
        return RunResult("Parallel", curThreads, blockSize, dur, isCorrect);
    };
    const auto g = runWithResultsF(quickSort, results, f);
    approximateRun(sample, nTrials, g);
    return results;
}

LL foldToAvg(PSeq<RunResult> &results) {
    PSeq<LL> mapped = parlay::map(results, [](RunResult r) { return r.duration; });
    return std::reduce(mapped.begin(), mapped.end(), 0,
                       [&](const LL a, const LL b) { return a + b; }) / mapped.size();
}

void printResults(PSeq<RunResult> &seq, PSeq<RunResult> &par) {
    assert(seq.size() == par.size() && seq.size() > 0);
    std::cout << "| # | Name | Threads | BlockSize | Time (ms) | Correct | " << std::endl;
    std::cout << "|:-:|:-:|:-:|:-:|:-:|:-:|" << std::endl;
    auto indices = parlay::tabulate(seq.size(), [](int i) { return i + 1; });
    auto zipped = zip(indices, seq, par);
    for (std::tuple<int, RunResult, RunResult> iterRes: zipped) {
        int it = std::get<0>(iterRes);
        std::cout << "| " << it << std::get<1>(iterRes).asMdRow() << std::endl;
        std::cout << "| " << it << std::get<2>(iterRes).asMdRow() << std::endl;
    }
    const LL r1 = foldToAvg(seq);
    const LL r2 = foldToAvg(par);
    const double avg = r1 / (double) r2;
    std::cout << "| avg | Sequential | " << r1 << " | Parallel | " << r2 << " | " << avg << " |" <<
            std::endl;
    std::cout << "**Parallel acceleration: " << avg << "**" << std::endl;
}

void runCompetition(const int &sz, const int &nTrials, const int &bs,
                    std::function<PSeq<int>(int)> &sampleGen, std::string annotation = "") {
    PSeq<int> sample = sampleGen(sz);
    std::cout << "### Run on " << (annotation.length() ? annotation : "sample") << std::endl;
    std::cout << "```" << std::endl;
    std::cout << "Sequential trials started\n" << std::endl;
    PSeq<RunResult> sequentialResults = runSequential(sample, nTrials);
    std::cout << "Parallel trials started" << std::endl;
    PSeq<RunResult> parallelResults = runParallel(sample, nTrials, bs);
    std::cout << "```" << std::endl;
    printResults(sequentialResults, parallelResults);
    std::cout << "\n" << std::endl;
}

void benchmarks() {
    const int nTrials = 5;
    const int sz = 1'0000'0000;
    PSeq<int> sample = randIntegersSample(sz);

    std::cout << "```" << std::endl;
    const int bs = findOptimalBlock(sz);
    std::cout << "```" << std::endl;

    runCompetition(sz, nTrials, bs, randIntegersSample, "random integers from [INT_MIN; INT_MAX]");
    runCompetition(sz, nTrials, bs, randConstSample, "the same values equal to integer from [INT_MIN; INT_MAX]");
    runCompetition(sz, nTrials, bs, sortedSample, "already sorted distinct values");
    runCompetition(sz, nTrials, bs, reversedSample, "reversed sorted sequence of distinct integers");
    runCompetition(sz, nTrials, bs, shuffledRangeSample, "shuffled sequence of distinct integers");
}

int main() {
    setNumThereads(4);
    benchmarks();
    return 0;
}
