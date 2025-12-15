#include <iostream>
#include "quick_sort.cpp"

bool validateSorted(PSeq<int> &actual, PSeq<int> &expected) {
    assert(is_sorted(expected));
    if (actual.size() != expected.size()) {
        return false;
    }

    for (int i = 0; i < expected.size(); ++i) {
        if (actual[i] != expected[i]) {
            return false;
        }
    }

    return true;
}

LL runTimed(QSortingFunc &quickSort, PSeq<int> &arr) {
    const auto start{std::chrono::high_resolution_clock::now()};
    quickSort(arr);
    const auto end{std::chrono::high_resolution_clock::now()};
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

std::function<LL(PSeq<int> &)> runTimedF(QSortingFunc &quickSort) {
    return [&quickSort](PSeq<int> &arr) { return runTimed(quickSort, arr); };
}

std::function<LL(PSeq<int> &)> runWithResultsF(QSortingFunc &quickSort, PSeq<int> &expectedSorted,
                                               PSeq<RunResult> &results,
                                               std::function<RunResult(LL, bool)> &resBuilder) {
    return [&quickSort, &expectedSorted, &results, resBuilder](PSeq<int> &arr) {
        LL t = runTimed(quickSort, arr);
        results.push_back(resBuilder(t, validateSorted(arr, expectedSorted)));
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


int findOptimalBlock(const int maxSize, std::function<void(PSeq<int> &, const int &)> qsortInstance,
                     const int startExp = 4, const int nTrials = 3) {
    PSeq<int> sample = generateUniformUnbounded(maxSize);
    std::pair<int, LL> bestTime = {-1, LONG_LONG_MAX};

    std::cout << "Started trials to search for the optimal block size" << std::endl;

    int curV = startExp;
    const int maxBs = maxSize / 2;
    const std::function<QSortingFunc(int)> fBuilder = [qsortInstance](int v) {
        return [v, qsortInstance](PSeq<int> &a) { qsortInstance(a, v); };
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
    auto sortedSample = sample;
    std::sort(sortedSample.begin(), sortedSample.end());
    auto g = runWithResultsF(quickSort, sortedSample, results, f);
    approximateRun(sample, nTrials, g);
    return results;
}

PSeq<RunResult> runParallel(PSeq<int> &sample, const int &nTrials, const int blockSize,
                            std::function<void(PSeq<int> &, const int &)> qsortInstance, std::string name) {
    PSeq<RunResult> results;
    QSortingFunc quickSort = [blockSize, qsortInstance](PSeq<int> &a) { qsortInstance(a, blockSize); };
    std::function<RunResult(LL, bool)> f = [&blockSize, name](const LL dur, const bool isCorrect) {
        int curThreads = parlay::num_workers();
        return RunResult(name, curThreads, blockSize, dur, isCorrect);
    };
    auto sortedSample = sample;
    std::sort(sortedSample.begin(), sortedSample.end());
    const auto g = runWithResultsF(quickSort, sortedSample, results, f);
    approximateRun(sample, nTrials, g);
    return results;
}

void runCompetition(const int &sz, const int &nTrials, const int &bs, const int &bs2,
                    const std::function<PSeq<int>(int)> &sampleGen, const std::string &annotation = "") {
    PSeq<int> sample = sampleGen(sz);

    std::cout << "### Run on " << (annotation.empty() ? "sample" : annotation) << std::endl;
    std::cout << "```" << std::endl;
    std::cout << "Sequential trials started\n" << std::endl;
    PSeq<RunResult> sequentialResults = runSequential(sample, nTrials);
    std::cout << "Parallel trials started (all parallelized)" << std::endl;
    const PSeq<RunResult> parallelResults = runParallel(sample, nTrials, bs, parallelQuickSortParFull,
                                                        "Parallel. All parallelized");
    std::cout << "Parallel trials started (sequential filter)" << std::endl;
    const PSeq<RunResult> parallelResultsN = runParallel(sample, nTrials, bs, parallelQuickSortSeqFilter,
                                                         "Parallel. Sequential filter");

    std::cout << "Parallel trials started (only fork)" << std::endl;
    const PSeq<RunResult> parallelResultsF = runParallel(sample, nTrials, bs2, parallelQuickSortForkOnly,
                                                         "Parallel. Only fork");

    std::cout << "```" << std::endl;
    PSeq<PSeq<RunResult> > all{sequentialResults, parallelResults, parallelResultsN, parallelResultsF};

    printResults(all);
    std::cout << "\n" << std::endl;
}

void benchmarks() {
    constexpr int nTrials = 5;
    constexpr int sz = 1'0000'0000;
    PSeq<int> sample = generateUniformUnbounded(sz);

    std::cout << "```" << std::endl;
    const int bs = findOptimalBlock(sz, parallelQuickSortParFull);
    const int bs2 = findOptimalBlock(sz, parallelQuickSortForkOnly);
    std::cout << "```" << std::endl;

    runCompetition(sz, nTrials, bs, bs2, generateUniformUnbounded, "random integers from [INT_MIN; INT_MAX]");
    runCompetition(sz, nTrials, bs, bs2, randConstSample, "the same values equal to integer from [INT_MIN; INT_MAX]");
    runCompetition(sz, nTrials, bs, bs2, sortedSample, "already sorted distinct values");
    runCompetition(sz, nTrials, bs, bs2, reversedSample, "reversed sorted sequence of distinct integers");

    runCompetition(sz, nTrials, bs, bs2, generate_uniform(-1e8, 1e8), "Uniform; 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_uniform(-1e6, 1e6), "Uniform; 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_uniform(-1e4, 1e4), "Uniform; 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_uniform(-1e2, 1e2), "Uniform; 10^2 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_student(1, 1e8), "StudentT ν=1(cauchy); 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_student(1, 1e6), "StudentT ν=1(cauchy); 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_student(1, 1e4), "StudentT ν=1(cauchy); 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_student(1, 1e2), "StudentT ν=1(cauchy); 10^2 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_student(1000, 1e8), "StudentT ν=1000(normal); 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_student(1000, 1e6), "StudentT ν=1000(normal); 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_student(1000, 1e4), "StudentT ν=1000(normal); 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_student(1000, 1e2), "StudentT ν=1000(normal); 10^2 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(2, 1e8), "LogNormal σ=2; 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(2, 1e6), "LogNormal σ=2; 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(2, 1e4), "LogNormal σ=2; 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(2, 1e2), "LogNormal σ=2; 10^2 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(0.3, 1e8), "LogNormal σ=0.3; 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(0.3, 1e6), "LogNormal σ=0.3; 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(0.3, 1e4), "LogNormal σ=0.3; 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_log_normal(0.3, 1e2), "LogNormal σ=0.3; 10^2 unique");

    PSeq<double> intervals1 = {0, 7, 8, 10};
    PSeq<double> weights1 = {10, 80, 10};
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e8, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 1 mode; 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e8, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 5 modes; 10^8 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e6, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 1 mode; 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e6, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 5 modes; 10^6 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e4, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 1 mode; 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e4, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 5 modes; 10^4 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e2, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 1 mode; 10^2 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e2, intervals1, weights1),
                   "\"Paretto\" {10, 80, 10}, 5 modes; 10^2 unique");

    PSeq<double> intervals2 = {0, 2, 3, 7, 8, 10};
    PSeq<double> weights2 = {8, 40, 6, 41, 7};
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e8, intervals2, weights2),
                   "\"Paretto\" {8, 40, 6, 41, 7}, 1 mode; 10^8 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e8, intervals2, weights2),
                   "\"Paretto\" {8, 40, 6, 41, 7}, 5 modes; 10^8 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e6, intervals2, weights2),
                   "\"Paretto\" {8, 40, 6, 41, 7}, 1 mode; 10^6 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e6, intervals2, weights2),
                   "\"Paretto\" {8, 40, 6, 41, 7}, 5 modes; 10^6 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e4, intervals2, weights2),
                   "\"Paretto\" {8, 40, 6, 41, 7}, 1 mode; 10^4 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e4, intervals2, weights2),
                   "\"Paretto\" {8, 40, 6, 41, 7}, 5 modes; 10^4 unique");

    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(1, 1e2, intervals2, weights2),
                   "Paretto {8, 40, 6, 41, 7}, 1 mode; 10^2 unique");
    runCompetition(sz, nTrials, bs, bs2, generate_piecewise(5, 1e2, intervals2, weights2),
                   "Paretto {8, 40, 6, 41, 7}, 5 modes; 10^2 unique");
}

int main() {
    setNumThereads(4);
    benchmarks();
    return 0;
}
