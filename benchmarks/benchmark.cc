#include <benchmark/benchmark.h>

int add(int a, int b) {
    return a + b;
}

static void BM_Add(benchmark::State &state) {
    int a = 10;
    int b = 20;
    for (auto _: state) {
        int result = add(a, b);
        benchmark::DoNotOptimize(result); // 防止编译器对结果进行优化
    }
}

BENCHMARK(BM_Add);

BENCHMARK_MAIN();
