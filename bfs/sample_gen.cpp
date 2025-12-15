#include "graph.cpp"

constexpr LL MAX_ALLOWED_SIZE = 1'000'000'000;

void makeK4(const GraphBuilder &g) {
    for (uint16_t i = 0; i < 3; i++) {
        for (uint16_t j = i + 1; j < 4; ++j) {
            g.addBiEdge(i, j);
        }
    }
}

std::pair<int, int> sampleAdjacent(const GraphBuilder &g, const PSeq<int> &randIndices, int &ptr, const int &maxId) {
    int i1 = randIndices[(ptr++) % randIndices.size()] % maxId; // std::cout <<i1 <<" ";
    int i2 = g.normalize(*g.vertexes[i1]->neighboursBuff.begin());

    return {i1, i2};
}

void extendTo2(const GraphBuilder &g, const int &curId, const int &id1, const int &id2, const int &id3,
               const int &id4) {
    /*
     * have e1 = (id1, id2), e2 = (id3, id4); remove e1, e2 => deg(id1)--, deg(id2)-- ,...
     * add e3 = (n1, n2) => deg(n1) = deg(n2) = 1;
     * add e4 = (n1, id1), add e5 = (n1, id2) => deg(id1)++, deg(id2++, deg(n1)+=2 = 3
     * add e6 = (n2, id3), add e7 = (n2, id4) => deg(id3)++, deg(id4)++, deg(n2)+=2 = 3
    */
    g.rmBiEdge(id1, id2);
    g.rmBiEdge(id3, id4);
    g.addBiEdge(curId, curId + 1);
    g.addBiEdge(curId, id1);
    g.addBiEdge(curId, id2);
    g.addBiEdge(curId + 1, id3);
    g.addBiEdge(curId + 1, id4);
}

void makeCubic(GraphBuilder &g) {
    if (g.sz % 2) {
        throw std::invalid_argument("Cubical graph should have even number of vertices");
    }
    const PSeq<int> randIndices = generate_uniform(0, g.sz - 1)(g.sz);
    int ptr = 0;
    makeK4(g);
    for (int i = 4; i < g.sz; i += 2) {
        if (!(i % 1000000)) std::cout << i << ": ";
        auto [id1, id2] = sampleAdjacent(g, randIndices, ptr, i - 1);
        bool built = false;
        while (!built) {
            // 3 unique vertexes are enough
            if (auto [id3, id4] = sampleAdjacent(g, randIndices, ptr, i - 1);
                (id3 != id1 && id3 != id2) || (id4 != id1 && id4 != id2)) {
                extendTo2(g, i, id1, id2, id3, id4);
                built = true;
            }
        }
    }
    for (Vertex *v: g.vertexes) {
        v->setNeighbours();
    }
    std::cout << "Finished building a cubic graph" << std::endl;
}

void makeCubicPrism(GraphBuilder &g) {
    const int s2 = g.edge * g.edge * g.edge / 2;
    for (int i = 0; i < s2; ++i) {
        if (i % 1000000 == 0 || i == s2 - 1) {
            std::cout << i << " ";
        }
        g.addBiEdge(i, (i + 1) % s2);
        g.addBiEdge(i + s2, (i + 1) % s2 + s2);
        g.addBiEdge(i, i + s2);
    }
    for (Vertex *v: g.vertexes) {
        v->setNeighbours();
    }
    std::cout << "Finished building a cubic prism" << std::endl;
}

static bool validateIsCubical(const GraphBuilder &g) {
    for (int i = 0; i < g.vertexes.size(); i++) {
        if (const Vertex *v = g.vertexes[i]; v->neighbours.size() != 3) {
            return false;
        }
        for (CoordinateRecord c: g.vertexes[i]->neighbours) {
            int f = 0;
            for (const int cId = g.normalize(c); CoordinateRecord n: g.vertexes[cId]->neighbours) {
                if (g.normalize(n) == i) {
                    f++;
                }
                if (cId == g.normalize(n)) {
                    return false;
                }
            }
            if (f != 1) {
                return false;
            }
        }
    }
    std::cout << "Graph is cubic" << std::endl;
    return true;
}

void makeGrid(GraphBuilder &graphBuilder) {
    const int e2 = static_cast<int>(graphBuilder.edge) * static_cast<int>(graphBuilder.edge);
    for (uint16_t i = 0; i < graphBuilder.edge; ++i) {
        for (uint16_t j = 0; j < graphBuilder.edge; ++j) {
            for (uint16_t k = 0; k < graphBuilder.edge; ++k) {
                //IdTuple curCoord = {i, j, k};
                int curId = toId({i, j, k}, graphBuilder.edge);
                // {i, j, k + 1}
                int next = curId + 1;
                if (next < graphBuilder.sz) { graphBuilder.addBiEdge(curId, next); } else continue;

                // {i, j + 1, k}
                next = curId + graphBuilder.edge;
                if (next < graphBuilder.sz) { graphBuilder.addBiEdge(curId, next); } else continue;

                // {i + 1, j, k}
                next = curId + e2;
                if (next < graphBuilder.sz) { graphBuilder.addBiEdge(curId, next); }
            }
        }
    }
}

void makePathGraph(const GraphBuilder &grBuilder) {
    for (int i = 1; i < grBuilder.sz; ++i) {
        grBuilder.addBiEdge(i - 1, i);
    }
}

/**
 * Builds a connected graph, whose vertices have degree in [1, maxDeg]
 * E(deg(v)) <= maxDeg / 2;
 */
void buildWithBoundedDeg(const GraphBuilder &grBuilder, const int &maxDeg) {
    log("Started building graph with bounded degree");
    makePathGraph(grBuilder); // in order to connectivity

    const LL sizeLL = (LL) grBuilder.sz;
    const LL sampleSize = std::max((LL) maxDeg, std::min(MAX_ALLOWED_SIZE / sizeLL, sizeLL));
    const int factor = sizeLL / sampleSize;

    StdVector<int> indices(sampleSize);
    std::iota(indices.rbegin(), indices.rend(), 0);

    for (int iId = 0; iId < grBuilder.sz - 2; ++iId) {
        if (!(iId % 1'000'000)) std::cout << iId << ": ";
        const int curMax = genRandInt(1, maxDeg);
        const int degBound = std::min(std::max(0, curMax - (int) grBuilder.vertexes[iId]->neighboursBuff.size()),
                                      grBuilder.sz - 1 - iId);
        if (degBound == 0) {
            continue;
        }

        // sample distinct values
        std::shuffle(indices.begin(), indices.end(), gen);
        int skipped = 0;
        for (int j = 0; j < degBound; ++j) {
            int jId = (indices[j % sampleSize] + sampleSize * genRandInt(0, factor)) % sizeLL;
            if (jId <= iId + 1) {
                // +1 from bamboo
                int d1 = iId + 2 - jId;
                int d2 = grBuilder.sz - jId - 1;
                jId += genRandInt(d1, d2);
            }

            if (grBuilder.vertexes[jId]->neighboursBuff.size() >= maxDeg) {
                ++skipped;
                continue;
            }
            grBuilder.addBiEdge(iId, jId);
        }
    }
    log("Finished building graph with bounded degree");
}

/**
 *
 * @param grBuilder builder
 * @param prob probability of each edge in graph. Note that due to memory limitations it will be implicitly
 * adjusted to probAdj = prob * min(1.0, MAX_ALLOWED_SIZE / n^2)
 */
void buildWithEdgeProbability(const GraphBuilder &grBuilder, const double &prob) {
    makePathGraph(grBuilder);

    log(std::format("Probability={}", prob));
    std::bernoulli_distribution distribution(prob);
    const LL sizeLL = (LL) grBuilder.sz;
    const LL n2 = sizeLL * sizeLL;
    const int factor = (int) (n2 / MAX_ALLOWED_SIZE);
    const LL sampleSize = std::min(MAX_ALLOWED_SIZE, n2);
    StdVector<LL> edgeIndices(sampleSize);
    std::iota(edgeIndices.begin(), edgeIndices.end(), 0);
    std::shuffle(edgeIndices.begin(), edgeIndices.end(), gen);


    int i = 0;
    for (LL idx: edgeIndices) {
        if (i % 1'000'000 == 0) {
            std::cout << i << " ";
        }
        const int m = genRandInt(0, factor);
        const LL adjustedIdx = (m * MAX_ALLOWED_SIZE + idx) % n2;
        int id1 = (int) (adjustedIdx / sizeLL);
        int id2 = (int) (adjustedIdx % sizeLL);
        if (std::abs(id1 - id2) == 1) {
            continue; // alredy exists in bamboo
        }

        if (distribution(gen)) {
            grBuilder.addBiEdge(id1, id2);
        }
        ++i;
    }
    std::cout << "\n";

    log("Finished build graph edge probability");
}
