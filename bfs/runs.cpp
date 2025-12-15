#include "bfs.cpp"
typedef std::pair<const SimpleGraph &, const CoordinateRecord &> BfsInput;

bool testDistances(const SimpleGraph &g, const StdVector<int> &distances, const int &src, int &v) {
    if (src == v) {
        return distances[v] == 0;
    }
    bool hasAncestor = false;
    for (CoordinateRecord c: g.get(v)) {
        int cId = g.normalize(c);
        if (distances[cId] < distances[v] - 1 || distances[cId] > distances[v] + 1) {
            return false;
        }
        if (distances[cId] == distances[v] - 1) {
            hasAncestor = true;
            // by induction, to check correctness it is sufficient to verify that vertex-ancestor cId satisfies the condition
            /*if (!testDistances(g, distances, src, cId)) { return false; }*/
        }
    }
    return hasAncestor;
}

bool testCorrectness(BFS &bfs, const BfsInput &bfsInput) {
    const SimpleGraph g = bfsInput.first;
    const int srcId = g.normalize(bfsInput.second);
    for (int i = 0; i < g.matrix.size(); ++i) {
        if (!testDistances(g, bfs.distances, srcId, i)) {
            return false;
        }
    }
    return true;
}

LL runTimedBfs(const std::function<void()> &bfs) {
    const auto start{std::chrono::high_resolution_clock::now()};
    bfs();
    const auto end{std::chrono::high_resolution_clock::now()};
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

LL approximateRun(const int &nTrials, const std::function<LL(int &)> &runTimedFunc) {
    LL t = 0;
    for (int i = 0; i < nTrials; ++i) {
        t += runTimedFunc(i);
    }
    return t / nTrials;
}

std::function<void()> runTimedBfsF(BFS &bfs, const BfsInput &bfsInput) {
    return [&] { bfs.bfs(bfsInput.first, bfsInput.second); };
}

std::function<LL(const BfsInput &)> runWithResultsF(BFS &instance, PSeq<RunResult> &results,
                                                    const std::function<RunResult(LL, bool)> &
                                                    resBuilder) {
    return [&](const BfsInput &bfsInput) {
        const LL t = runTimedBfs(runTimedBfsF(instance, bfsInput));
        const bool isCorrect = testCorrectness(instance, bfsInput);
        results.push_back(resBuilder(t, isCorrect));
        return t;
    };
}

PSeq<RunResult> runOnInstance(const std::string &name, BFS &instance, const BfsInput &bfsInput, const int &nTrials,
                              const int &blockSize) {
    PSeq<RunResult> results;
    approximateRun(nTrials,
                   [&](int &i) {
                       log(std::format("{}{} run started", i + 1,
                                       i % 10 == 0 ? "st" : (i % 10 == 1 ? "nd" : (i % 10 == 2 ? "rd" : "th"))));
                       return runWithResultsF(instance, results,
                                              [&](const LL t, const bool isCorrect) {
                                                  const int nThreads = blockSize == bfsInput.first.matrix.size()
                                                                           ? 1
                                                                           : parlay::num_workers();
                                                  return RunResult(name, nThreads, blockSize, t, isCorrect);
                                              })(bfsInput);
                   });
    return results;
}

void runCompetition(const BfsInput &bfsInput, const int &nTrials, const int &bs, const std::string &annotation = "") {
    std::cout << std::format("### Run on {}\n", (annotation.empty() ? "sample" : annotation));
    std::cout << "```" << std::endl;

    log("Sequential.SuccinctVisited trials started");
    auto bfsSucc = SequentialBfsSuccinctVisited();
    PSeq<RunResult> bfsSuccResults = runOnInstance("Sequential.SuccinctVisited", bfsSucc, bfsInput, nTrials,
                                                   bfsInput.first.matrix.size());
    std::cout << "\n";

    log("Sequential.ImplicitVisited trials started");
    auto bfsImplicit = SequentialBfsSuccinctVisited();
    PSeq<RunResult> bfsImplicitResults = runOnInstance("Sequential.ImplicitVisited", bfsImplicit, bfsInput,
                                                       nTrials, bfsInput.first.matrix.size());
    std::cout << "\n";

    log("Parallel1 trials started");
    auto parallel = ParallelBfs(bs);
    PSeq<RunResult> parallelResults = runOnInstance("ParallelBfs", parallel, bfsInput, nTrials, bs);
    std::cout << "\n";

    log("Parallel2 trials started");
    auto parallel2 = ParallelBfs(bs);
    PSeq<RunResult> parallelResults2 = runOnInstance("ParallelBfs2", parallel2, bfsInput, nTrials, bs);
    std::cout << "\n";

    std::cout << "```" << std::endl;

    PSeq<PSeq<RunResult> > all{bfsSuccResults, bfsImplicitResults, parallelResults, parallelResults2};
    printResults(all, 2);
    std::cout << "\n" << std::endl;
}

void launchRun(const int &nTrials, const int &blockSize, GraphBuilder &grBuilder,
               const std::function<void(GraphBuilder &)> &buildF, std::string name) {
    grBuilder.reset();
    std::cout << "\n```\n";
    buildF(grBuilder);
    SimpleGraph g = grBuilder.toSimpleGraph();
    std::cout << "\n```\n";
    runCompetition({g, 0u}, nTrials, blockSize, name);
    log(std::format("\n```\nfinished run on {}\n```", name));
}

void computeDegree(GraphBuilder &g) {
    LL avgDeg = 0;
    for (const auto v: g.vertexes) {
        avgDeg += v->neighboursBuff.size();
    }
    log(std::format("Average degree {}", avgDeg / static_cast<double>(g.sz)));
}

void benchmarks() {
    constexpr int nTrials = 5;
    constexpr int edge = 500;
    constexpr int blockSize = 100;

    const auto grBuilder = new GraphBuilder(edge);
    grBuilder->initVertices();

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  makeCubic(g);
                  std::cout << validateIsCubical(g) << std::endl;
              }, "Random cubic graph");

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  makeCubicPrism(g);
                  std::cout << validateIsCubical(g) << std::endl;
              }, "Cubic prism");


    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  makeGrid(g);
              }, "3D grid");

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithEdgeProbability(g, 3 * std::log(g.sz) / static_cast<double>(g.sz));
                  computeDegree(g);
              }, "Graph: P(edge) = 3* log(n)/n");

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithEdgeProbability(g, std::sqrt(g.sz) / static_cast<double>(g.sz));
                  computeDegree(g);
              }, "Graph: P(edge) = sqrt(n)/n");

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithEdgeProbability(g, 1e6 * std::log(g.sz) / static_cast<double>(g.sz));
                  computeDegree(g);
              }, "Graph: P(edge) = 10^6 * log(n)/n");

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithEdgeProbability(g, 4 * 1e3 * std::sqrt(g.sz) / static_cast<double>(g.sz));
                  computeDegree(g);
              }, "Graph: P(edge) = 10^4*sqrt(n)/n");


    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 5);
                  computeDegree(g);
              }, "Graph: v.deg <= 5");

    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 10);
                  computeDegree(g);
              }, "Graph: v.deg <= 10");
    launchRun(nTrials, blockSize, *grBuilder,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 100);
                  computeDegree(g);
              }, "Graph: v.deg <= 100");

    // dense graph
    const auto small = new GraphBuilder(200);
    small->initVertices();
    launchRun(nTrials, blockSize, *small,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 10);
                  computeDegree(g);
              }, "Graph (n=8'000'000): v.deg <= 10");
    launchRun(nTrials, blockSize, *small,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 20);
                  computeDegree(g);
              }, "Graph (n=8'000'000): v.deg <= 20");
    launchRun(nTrials, blockSize, *small,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 50);
                  computeDegree(g);
              }, "Graph (n=8'000'000): v.deg <= 50");
    launchRun(nTrials, blockSize, *small,
              [&](GraphBuilder &g) {
                  buildWithBoundedDeg(g, 100);
                  computeDegree(g);
              }, "Graph (n=8'000'000): v.deg <= 100");
}

int main() {
    setNumThereads(4);
    benchmarks();
}
