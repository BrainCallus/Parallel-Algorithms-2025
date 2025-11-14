#include <random>
#include <string>
#include <sstream>
#include <parlay/primitives.h>

typedef long long LL;
template<typename S>
using PSeq = parlay::sequence<S>;
typedef std::function<PSeq<int>(int)> SampleGen;

struct RunResult {
    std::string name;
    int nThreads;
    int parallelBlockSize;
    LL duration;
    bool isCorrect;

    RunResult() = default;

    RunResult(const std::string &n, int th, int bs, LL dur, bool c)
        : name(n), nThreads(th), parallelBlockSize(bs), duration(dur), isCorrect(c) {
    }

    std::string asMdRow() const {
        std::stringstream ss;
        ss << "| " << name << " | " << nThreads << " | " << parallelBlockSize << " | " << duration << " | " << isCorrect
                << " |";
        return ss.str();
    }
};

int genRandInt(const int &mn, const int &mx) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(mn, mx);
    return dist(gen);
}

PSeq<int> genSample(const int &sz, const std::function<int(int)> &gen) {
    PSeq<int> sample = parlay::tabulate(sz, gen);
    return sample;
}

SampleGen randIntegersSample = [](const int sz) {
    return genSample(2 * sz, [](int) { return genRandInt(INT_MIN, INT_MAX); });
};

SampleGen constSample(int c) {
    return [c](int sz) { return genSample(sz, [c](int) { return c; }); };
}

SampleGen randConstSample =
        [](const int sz) {
    int c = genRandInt(INT_MIN, INT_MAX);
    return constSample(c)(sz);
};

SampleGen reversedSample =
        [](const int sz) {
    return genSample(2 * sz, [sz](int i) { return sz - i; });
};


SampleGen sortedSample =
        [](const int sz) {
    return genSample(2 * sz, [](int i) { return i; });
};


SampleGen shuffledRangeSample =
        [](const int sz) {
    PSeq<int> sample = sortedSample(sz);
    std::shuffle(sample.begin(), sample.end(), std::mt19937(std::random_device()()));
    return sample;
};


void setNumThereads(const int &nThreads) {
    // Uncomment next line if you use linux
    // setenv("PARLAY_NUM_THREADS", std::to_string(nThreads).c_str(), 1);
    _putenv_s("PARLAY_NUM_THREADS", std::to_string(nThreads).c_str());
    std::cout << "Current amount of threads " << parlay::num_workers() << std::endl;
}
