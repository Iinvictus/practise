#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <benchmark/benchmark.h>

#include "Timer.h"

const std::string text = "hello world hello google hello benchmark";

std::vector<std::string> splitUsingFind(const std::string& text, const std::string &delimiter = " ") {
    std::vector<std::string> tokens;
    auto pos = text.find_first_not_of(delimiter, 0);
    auto lastPos = text.find_first_of(delimiter, pos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.emplace_back(text.substr(pos, lastPos - pos));
        pos = text.find_first_not_of(delimiter, lastPos);
        lastPos = text.find_first_of(delimiter, pos);
    }
    return tokens;
}

std::vector<std::string> splitUsingRegex(const std::string &text, const std::string &delimiter = " ") {
    std::regex whitespace_re("\\s+");
    std::vector<std::string> tokens(std::sregex_token_iterator(text.begin(), text.end(), whitespace_re, -1), std::sregex_token_iterator());
    return tokens;
}

static void BM_SplitUsingFind(benchmark::State& state) {
    for (auto _ : state) {
        splitUsingFind(text);
    }
}

static void BM_SplitUsingRegex(benchmark::State& state) {
    for (auto _ : state) {
        splitUsingRegex(text);
    }
}

BENCHMARK(BM_SplitUsingFind);
BENCHMARK(BM_SplitUsingRegex);
BENCHMARK_MAIN();

int main () {
    std::string text = "hello world hello google hello benchmark";
    {
        zhuifeng::Timer timer("splitUsingFind");
        for (int i = 0; i < 10000; ++i) {
            splitUsingFind(text);
        }
    }

    {
        zhuifeng::Timer timer("splitUsingRegex");
        for (int i = 0; i < 10000; ++i) {
            splitUsingRegex(text);
        }
    }
}


// ➜  cpp g++ split.cpp -o timer && ./timer    
// splitUsingFind took:0.2ms.
// splitUsingRegex took:28.928ms.
// ➜  cpp g++ split.cpp -O3 -o timer && ./timer
// splitUsingFind took:0.049ms.
// splitUsingRegex took:5.452ms.