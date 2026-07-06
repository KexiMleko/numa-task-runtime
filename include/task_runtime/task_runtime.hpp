#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <stop_token>
#include <thread>

namespace numart {
class task_runtime {
  std::mutex q_mtx;
  std::queue<std::packaged_task<void()>> work_q;
  std::vector<std::jthread> thread_pool;

  void spin(std::stop_token stoken);

public:
  task_runtime(unsigned int thread_count = std::thread::hardware_concurrency());
  std::future<void> submit(std::function<void()> task);
};
} // namespace numart
