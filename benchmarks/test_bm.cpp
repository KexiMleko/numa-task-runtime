#include "task_runtime.hpp"
#include <cstdlib>
#include <future>
#include <stdio.h>

int main() {

  printf("Benchmark invoked\n");
  numart::task_runtime tr;
  std::vector<std::future<void>> futv;
  for (int i = 0; i < 100; i++) {
    std::future<void> fut = tr.submit([i]() -> void { printf(":%d:", i); });
    futv.push_back(std::move(fut));
  }
  for(int i=0;i<futv.size();i++){
    futv.at(i).get();
  }

  printf("Benchmark done\n");
  return EXIT_SUCCESS;
}
