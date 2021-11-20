#include <iostream>

#include <benchmark/benchmark.h>


const std::vector<std::string> words = {"hello", "world", "hello", "google", "hello", "benchmark"};

void for_lo_hi(const std::vector<std::string> &words) {
    for (auto iter = words.begin(); iter != words.end(); ++iter) {
        auto temp = *iter;
    }
}

void for_range(const std::vector<std::string> &words) {
    for (auto &word: words) {
        auto temp = word;
    }
}

void for_each_zf(const std::vector<std::string> &words) {
    for_each(words.begin(), words.end(), [](const std::string &word) {
        auto temp = word;
    });
}

static void BM_ForLoHi(benchmark::State& state) {
    for (auto _ : state) {
        for_lo_hi(words);
    }
}

static void BM_ForRange(benchmark::State& state) {
    for (auto _ : state) {
        for_range(words);
    }
}

static void BM_ForEachZf(benchmark::State& state) {
    for (auto _ : state) {
        for_each_zf(words);
    }
}

BENCHMARK(BM_ForLoHi);
BENCHMARK(BM_ForRange);
BENCHMARK(BM_ForEachZf);
BENCHMARK_MAIN();