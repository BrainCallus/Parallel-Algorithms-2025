#include "sample_gen.cpp"
#include <queue>

class BFS {
public:
    virtual ~BFS() = default;

    StdVector<int> distances;

    virtual void bfs(const SimpleGraph &g, const CoordinateRecord &src) = 0;

    void reset() {
        for (int &distance: distances) {
            distance = -1;
        }
    }

    void assignDistances(const int &sz) {
        distances.assign(sz, -1);
    }
};

class SequentialBfsSuccinctVisited : public BFS {
public:
    void bfs(const SimpleGraph &g, const CoordinateRecord &src) override {
        assignDistances(g.matrix.size());
        const int visited_size = g.matrix.size() / 64 + (g.matrix.size() % 64 > 0 ? 1 : 0);
        StdVector<ULL> visitedp(visited_size, 0);

        const int srcId = g.normalize(src);

        std::queue<int> q;
        setVisited(srcId, visitedp);
        distances[srcId] = 0;
        q.push(srcId);
        while (!q.empty()) {
            const int vId = q.front();
            q.pop();

            for (CoordinateRecord coord_u: g.matrix[vId]) {
                const int uId = g.normalize(coord_u);
                if (!isVisited(uId, visitedp)) {
                    setVisited(uId, visitedp);
                    distances[uId] = distances[vId] + 1;
                    q.push(uId);
                }
            }
        }
    }
};

class SequentialBfsImplicitVisited : public BFS {
public:
    void bfs(const SimpleGraph &g, const CoordinateRecord &src) override {
        assignDistances(g.matrix.size());
        StdVector<bool> visited(g.matrix.size(), false);
        const int srcId = g.normalize(src);

        std::queue<int> q;
        visited[srcId] = true;
        distances[srcId] = 0;
        q.push(srcId);
        while (!q.empty()) {
            int vId = q.front();
            q.pop();

            for (CoordinateRecord coord_u: g.matrix[vId]) {
                int uId = g.normalize(coord_u);
                if (!visited[uId]) {
                    visited[uId] = true;
                    distances[uId] = distances[vId] + 1;
                    q.push(uId);
                }
            }
        }
    }
};

class ParallelBfs : public BFS {
private:
    int blockSize;

public:
    explicit ParallelBfs(const int &bs) {
        blockSize = bs;
    }

    void setBlockSize(const int &bs) {
        blockSize = bs;
    }

    void bfs(const SimpleGraph &g, const CoordinateRecord &src) override {
        assignDistances(g.matrix.size());
        StdVector<std::atomic<bool> > visited(g.matrix.size());
        const int srcId = g.normalize(src);

        PSeq<int> frontier;
        visited[srcId].store(true);
        distances[srcId] = 0;
        frontier.push_back(srcId);
        while (!frontier.empty()) {
            auto offsets = parlay::tabulate(frontier.size(), [&](int i) {
                return g.matrix[frontier[i]].size();
            }, blockSize);
            auto sum = parlay::scan_inplace(offsets);
            parlay::sequence<int> new_frontier(sum, -1);


            parlay::parallel_for(0, frontier.size(), [&](int i) {
                int vId = frontier[i];
                int newDist = distances[vId] + 1;
                for (size_t j = 0; j < g.matrix[vId].size(); j++) {
                    int uId = g.normalize(g.matrix[vId][j]);
                    bool expected = false;

                    if (visited[uId].compare_exchange_strong(expected, true)) {
                        distances[uId] = newDist;
                        new_frontier[offsets[i] + j] = uId;
                    }
                }
            }, blockSize);

            frontier = parlay::filter(new_frontier, [](int id) {
                return id >= 0;
            });
        }
    }
};

class ParallelBfs2 : public BFS {
private:
    int blockSize;

public:
    explicit ParallelBfs2(const int &bs) {
        blockSize = bs;
    }

    void setBlockSize(const int &bs) {
        blockSize = bs;
    }

    void bfs(const SimpleGraph &g, const CoordinateRecord &src) override {
        assignDistances(g.matrix.size());
        StdVector<std::atomic<bool> > visited(g.matrix.size());
        const int srcId = g.normalize(src);

        PSeq<int> frontier;
        PSeq<int> frontierDegs;
        visited[srcId].store(true);
        distances[srcId] = 0;
        frontier.push_back(srcId);
        frontierDegs.push_back(g.matrix[srcId].size());
        while (!frontier.empty()) {
            auto [offsets, newFrontierSize] = parlay::scan(frontierDegs);
            PSeq<int> newFrontier(newFrontierSize, -1);
            frontierDegs.assign(newFrontierSize, -1);


            parlay::parallel_for(0, frontier.size(), [&](const int i) {
                const int vId = frontier[i];
                const int newDist = distances[vId] + 1;
                int j = 0;
                for (CoordinateRecord coordU: g.matrix[vId]) {
                    int uId = g.normalize(coordU);
                    bool expected = false;

                    if (visited[uId].compare_exchange_strong(expected, true)) {
                        distances[uId] = newDist;
                        newFrontier[offsets[i] + j] = uId;
                        frontierDegs[offsets[i] + j] = g.matrix[uId].size() - 1; // at least vId won't be added
                        ++j;
                    }
                }
            }, blockSize);

            frontier = parlay::filter(newFrontier, [&](const int i) { return i >= 0; });
            frontierDegs = parlay::filter(frontierDegs, [&](const int i) { return i >= 0; });
        }
    }
};
