#include "task_runtime.hpp"
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <stop_token>
#include <thread>
#include <vector>

constexpr unsigned int fallback_thread_count = 4;

void numart::task_runtime::spin(std::stop_token stoken) {
  while (!(stoken.stop_requested() && work_q.empty())) {
    std::unique_lock<std::mutex> q_lock{q_mtx};
    if (!work_q.empty()) {
      std::packaged_task<void()> task = std::move(work_q.front());
      work_q.pop();
      q_lock.unlock();
      task();
    }
  }
}

numart::task_runtime::task_runtime(unsigned int thread_count) {
  if (thread_count == 0)
    thread_count = fallback_thread_count;
  for (int i = 0; i < thread_count; i++) {
    std::jthread thr{std::bind_front(&task_runtime::task_runtime::spin, this)};
    thread_pool.push_back(std::move(thr));
  }
}

std::future<void> numart::task_runtime::submit(std::function<void()> task) {
  std::packaged_task<void()> p_task(task);
  std::future fut = p_task.get_future();
  std::unique_lock<std::mutex> q_lock{q_mtx};
  work_q.push(std::move(p_task));
  q_lock.unlock();

  return fut;
}
