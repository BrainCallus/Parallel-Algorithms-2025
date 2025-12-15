#include <cmath>
#include <random>
#include "../shared/utils.cpp"

static thread_local std::mt19937 gen(std::random_device{}());

PSeq<int> genSample(const int &sz, const std::function<int(int)> &gen) {
    PSeq<int> sample = parlay::tabulate(sz, gen);
    return sample;
}

SampleGen generate_log_normal(const float &s, const int &maxValue) {
    constexpr double z95 = 1.6448536269514722;
    const double mu = std::log(static_cast<double>(maxValue) + 0.5) - z95 * s;


    return [mu, s, maxValue](const int sz) {
        std::lognormal_distribution<> dist(mu, s);
        return genSample(sz, [&](int) { return std::min(maxValue, static_cast<int>(std::round(dist(gen)))); });
    };
}

SampleGen generate_student(const int &nu, const int &maxValue) {
    const std::map<int, double> t975 = {{1, 12.71}, {2, 4.303}, {3, 3.182}, {4, 2.776}, {5, 2.571}, {1000, 1.962}};
    const double s = static_cast<double>(maxValue) / t975.at(nu);

    return [nu, s,maxValue](const int sz) {
        return genSample(2 * sz, [&](int) {
            std::student_t_distribution<> dist{(double) nu};
            return std::min(maxValue, std::max(-maxValue, static_cast<int>(std::round(dist(gen) * s))));
        });
    };
}

PSeq<int> generate_piecewise(const int sz, PSeq<double> intervals, PSeq<double> weights) {
    assert(intervals.size() == weights.size() + 1);
    std::piecewise_constant_distribution<> dist(intervals.begin(), intervals.end(), weights.begin());
    PSeq<int> result;
    for (int i = 0; i < sz; ++i) {
        result.push_back(static_cast<int>(dist(gen)));
    }
    return result;
}

SampleGen generate_piecewise(const int &nModes, const int &maxValue, PSeq<double> &i, PSeq<double> &weights) {
    PSeq<double> intervals(i.size());

    const int coef = maxValue / nModes;
    std::transform(i.begin(), i.end(), intervals.begin(), [&coef, &i](const int x) {
        return x * coef / i[i.size() - 1];
    });

    return [=](const int sz) {
        PSeq<int> result;
        const int szSingle = sz / nModes;
        for (int m = 0; m < nModes; m++) {
            PSeq<int> prom = generate_piecewise(szSingle, intervals, weights);
            for (const int x: prom) {
                result.push_back(coef * m + x);
            }
        }
        std::shuffle(result.begin(), result.end(), gen);
        return result;
    };
}

int genRandInt(const int &mn, const int &mx) {
    std::uniform_int_distribution<int> dist(mn, mx);
    return dist(gen);
}

SampleGen generate_uniform(const int &mn, const int &mx) {
    return [&](const int sz) {
        return genSample(2 * sz, [&](int) { return genRandInt(mn, mx); });
    };
}

SampleGen generateUniformUnbounded = [](const int sz) {
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
