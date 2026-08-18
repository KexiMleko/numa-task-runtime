#include "measure.hpp"
#include "task_runtime.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <future>
#include <stdio.h>

int main() {
  constexpr size_t iteration_count = 100;

  printf("Benchmark invoked\n");
  uint64_t time_buf;
  numart::task_runtime tr;
  std::vector<std::future<void>> futv;

  warmup_measure_icache();
  measure_start(time_buf);
  for (int i = 0; i < iteration_count; i++) {
    std::future<void> fut = tr.submit([i]() -> void {
      volatile int x;
      x = i + 10;
      // printf(":%d:", i);
      // fflush(stdout);
    });
    futv.push_back(std::move(fut));
  }
  for (int i = 0; i < futv.size(); i++) {
    futv.at(i).get();
  }
  uint64_t elapsed = measure_end(time_buf);

  printf("Benchmark done - avg: %lu cycles\n", elapsed / iteration_count);
  return EXIT_SUCCESS;
}
