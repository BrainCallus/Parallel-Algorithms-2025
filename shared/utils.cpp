#include <random>
#include <string>
#include <sstream>
#include <parlay/primitives.h>

typedef long long LL;
template<typename S>
using PSeq = parlay::sequence<S>;
template<typename V>
using StdVector = std::vector<V>;
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

LL foldToAvg(PSeq<RunResult> &results) {
    PSeq<LL> mapped = parlay::map(results, [](RunResult r) { return r.duration; });
    return std::reduce(mapped.begin(), mapped.end(), 0,
                       [&](const LL a, const LL b) { return a + b; }) / mapped.size();
}

void printResults(PSeq<PSeq<RunResult> > &sseq, const int &n = 1) {
    // assert(seq.size() == par.size() && seq.size() > 0);
    std::cout << "| # | Name | Threads | BlockSize | Time (ms) | Correct | " << std::endl;
    std::cout << "|:-:|:-:|:-:|:-:|:-:|:-:|" << std::endl;
    // auto indices = parlay::tabulate(seq.size(), [](int i) { return i + 1; });
    // auto zipped = zip(indices, seq, par);
    assert(sseq.size()>1 && sseq[0].size() > 0);
    int sampleSize = sseq[0].size();
    for (auto r: sseq) {
        assert(r.size()==sampleSize);
    }
    for (int j = 0; j < sseq[0].size(); j++) {
        for (PSeq<RunResult> results: sseq) {
            std::cout << "| " << j << results[j].asMdRow() << std::endl;
        }
    }
    // for (std::tuple<int, RunResult, RunResult> iterRes: zipped) {
    //     int it = std::get<0>(iterRes);
    //     std::cout << "| " << it << std::get<1>(iterRes).asMdRow() << std::endl;
    //     std::cout << "| " << it << std::get<2>(iterRes).asMdRow() << std::endl;
    // }
    std::cout << "\n";
    StdVector<double> sequentialResults(n);

    std::cout << "| Name |";
    for (int i = 0; i < n; ++i) {
        sequentialResults[i] = foldToAvg(sseq[i]);
        std::cout << " " << sseq[i][0].name << " |";
    }
    std::cout << "\n|:-:|";
    for (int i = 0; i < n; ++i) {
        std::cout << ":-:|";
    }
    std::cout << "\n";
    for (int i = n; i < sseq.size(); i++) {
        const double ri = foldToAvg(sseq[i]);
        std::cout << "| " << sseq[i][0].name << " |";
        for (double s: sequentialResults) {
            std::cout << " " << s / ri << " |";
        }
        std::cout << "" << std::endl;
    }

    std::cout << std::endl;
    // std::cout << "**Parallel acceleration: " << avg << "**" << std::endl;
}

void setNumThereads(const int &nThreads) {
    // Uncomment next line if you use linux
    // setenv("PARLAY_NUM_THREADS", std::to_string(nThreads).c_str(), 1);
    _putenv_s("PARLAY_NUM_THREADS", std::to_string(nThreads).c_str());
    std::cout << "Current number of threads " << parlay::num_workers() << std::endl;
}

std::string nowSting() {
    auto now = std::chrono::system_clock::now() + std::chrono::hours(3);
    auto nowSeconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    return std::format("[{:%FT%T}]", nowSeconds);
}

void log(const std::string &text) {
    std::cout << std::format("{} {}", nowSting(), text) << std::endl;
}
