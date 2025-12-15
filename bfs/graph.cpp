#include <atomic>
#include <cstdint>
#include <set>
#include <tuple>
#include <random>
#include "../qsort/generators.cpp"

constexpr int Z_BITMASK = (1 << 9) - 1;
constexpr int Y_BITMASK = Z_BITMASK << 9;
constexpr int X_BITMASK = Y_BITMASK << 9;

typedef std::tuple<uint16_t, uint16_t, uint16_t> IdTuple;
typedef unsigned long long ULL;
typedef uint32_t CoordinateRecord;

static bool isBitSet(const ULL &n, const int &bit) {
    return (n >> bit) & 1;
}


static IdTuple fromId(int id, const uint16_t &edge) {
    uint16_t x = id / edge / edge;
    id %= edge * edge;
    uint16_t y = id / edge;
    id %= edge;
    return {x, y, id};
}

static IdTuple fromRecord(const CoordinateRecord &succinct) {
    return {(succinct & X_BITMASK) >> 18, (succinct & Y_BITMASK) >> 9, succinct & Z_BITMASK};
}


static int toId(const IdTuple &t, const uint16_t &edge) {
    return std::get<0>(t) * edge * edge + std::get<1>(t) * edge + std::get<2>(t);
}

static CoordinateRecord toCoordinateRec(const IdTuple &coordinates) {
    return (std::get<0>(coordinates) << 18) + (std::get<1>(coordinates) << 9) + std::get<2>(coordinates);
}

static CoordinateRecord recFromId(const int id, const uint16_t &edge) {
    return toCoordinateRec(fromId(id, edge));
}

struct Vertex {
    // todo: succinct to single integer [?????|x(9)|y(9)|z(9)]
    //uint16_t x, y, z;
    CoordinateRecord coordinateRecord;
    bool areNeighboursSet = false;
    std::set<CoordinateRecord> neighboursBuff;
    StdVector<CoordinateRecord> neighbours;

    explicit Vertex(const IdTuple &indices) {
        coordinateRecord = toCoordinateRec(indices);
    }

    uint16_t getX() const {
        return (coordinateRecord & X_BITMASK) >> 18;
    }

    uint16_t getY() const {
        return (coordinateRecord & Y_BITMASK) >> 9;
    }

    uint16_t getZ() const {
        return coordinateRecord & Z_BITMASK;
    }

    int getId(const uint16_t &edge) const {
        return edge * edge * static_cast<uint16_t>(coordinateRecord >> 18) +
               edge * static_cast<uint16_t>((coordinateRecord & Y_BITMASK) >> 9) +
               static_cast<uint16_t>(coordinateRecord & Z_BITMASK);
    }

    void addEdge(const Vertex *v) {
        neighboursBuff.insert(v->coordinateRecord);
    }

    void removeEdge(Vertex *&v) {
        neighboursBuff.erase(v->coordinateRecord);
    }

    void setNeighbours() {
        neighbours.resize(neighboursBuff.size());
        int i = 0;
        for (const CoordinateRecord n: neighboursBuff) {
            neighbours[i++] = n;
        }
        neighboursBuff.clear();
        areNeighboursSet = true;
    }

    void reset() {
        neighbours.resize(0);
        areNeighboursSet = false;
        neighboursBuff.clear();
    }
};

struct SimpleGraph {
    uint16_t edge;
    StdVector<StdVector<CoordinateRecord> > matrix;
    // todo: consider about 48 bit instead of 27 for reinsurance

    explicit SimpleGraph(const uint16_t &e, const StdVector<StdVector<CoordinateRecord> > &m) {
        edge = e;
        matrix = m;
    }

    std::vector<CoordinateRecord> get(const int &id) const {
        return matrix[id];
    }

    int normalize(const CoordinateRecord &coordinates) const {
        return toId(fromRecord(coordinates), edge);
    }
};


static bool isVisited(const int &v, const StdVector<std::atomic<ULL> > &visited) {
    return isBitSet(visited[v / 64].load(), v % 64);
}

static bool isVisited(const int &v, const StdVector<ULL> &visited) {
    return isBitSet(visited[v / 64], v % 64);
}

static void setVisited(const int &id, StdVector<ULL> &visited) {
    visited[id / 64] |= (1ULL << (id % 64));
}

static bool setVisitedCAS(const int &id, StdVector<std::atomic<ULL> > &visited) {
    ULL curVis = visited[id / 64].load();
    if (isBitSet(curVis, id % 64)) {
        return false;
    }
    const ULL newVis = curVis | (1ULL << (id % 64));
    return visited[id / 64].compare_exchange_strong(curVis, newVis);
}

struct GraphBuilder {
    uint16_t edge;
    int sz;
    std::vector<Vertex *> vertexes;

    explicit GraphBuilder(const uint16_t &e)
        : edge(e),
          sz(e * e * e),
          vertexes(sz, nullptr) {
    }

    ~GraphBuilder() {
        for (Vertex *&v: vertexes) {
            delete v;
            v = nullptr;
        }
        vertexes.resize(0);
    }

    void initVertices() {
        for (int i = 0; i < sz; i++) {
            vertexes[i] = new Vertex(fromId(i, edge));
        }
    }

    int normalize(const CoordinateRecord &coordinates) const {
        return toId(fromRecord(coordinates), edge);
    }

    void addBiEdge(const int &id1, const int &id2) const {
        vertexes[id1]->addEdge(vertexes[id2]);
        vertexes[id2]->addEdge(vertexes[id1]);
    }

    static void addBiEdge(Vertex *&v1, Vertex *&v2) {
        v1->addEdge(v2);
        v2->addEdge(v1);
    }

    void rmBiEdge(const int &id1, const int &id2) const {
        Vertex *v1 = vertexes[id1];
        Vertex *v2 = vertexes[id2];
        v1->removeEdge(v2);
        v2->removeEdge(v1);
    }

    SimpleGraph toSimpleGraph() const {
        StdVector<StdVector<CoordinateRecord> > matrix(sz);
        for (int i = 0; i < sz; ++i) {
            Vertex *v = vertexes[i];
            if (!v->areNeighboursSet) {
                v->setNeighbours();
            }
            matrix[i] = v->neighbours;
        }
        return SimpleGraph(edge, matrix);
    }

    void reset() {
        for (Vertex *v: vertexes) {
            v->reset();
        }
    }
};
