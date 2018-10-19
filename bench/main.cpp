#include "benchmark/benchmark.h"
#include "threadpool.hpp"
#include <set>
#include <vector>

static void BM_ThreadPool_SingleQueue_NoBlockingTasks(benchmark::State& state)
{
  while (state.KeepRunning())
  {
    ThreadPool::ThreadPool<ThreadPool::SingleQueue> pool;
    std::vector<std::future<int>> results;
    std::set<std::thread::id> threads_id;

    auto i_end = state.range(0);
    for (int i = 0; i < i_end; i++)
      results.push_back(pool.run([i]() { return i * i; }));
    for (int i = 0; i < i_end; i++)
      results[i].get();
  }
}

/*BENCHMARK(BM_ThreadPool_SingleQueue_NoBlockingTasks)
  ->Range(8, 8 << 10)
  ->Unit(benchmark::kMillisecond);*/

static void BM_ThreadPool_MultipleQueue_NoBlockingTasks(benchmark::State& state)
{
  while (state.KeepRunning())
  {
    ThreadPool::ThreadPool<ThreadPool::MultipleQueue> pool;
    std::vector<std::future<int>> results;
    std::set<std::thread::id> threads_id;

    auto i_end = state.range(0);
    for (int i = 0; i < i_end; i++)
      results.push_back(pool.run([i]() { return i * i; }));
    for (int i = 0; i < i_end; i++)
      results[i].get();
  }
}

BENCHMARK(BM_ThreadPool_MultipleQueue_NoBlockingTasks)
  ->Range(8, 8 << 10)
  ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
