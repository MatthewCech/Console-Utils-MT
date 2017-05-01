#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>

class Semaphore
{
private:
  std::condition_variable cv_;
  std::mutex cv_m_;
  std::atomic<unsigned int> value_;
public:
  Semaphore(unsigned value) 
    : cv_()
    , cv_m_()
    , value_(value) {}
  inline void wait() {
    std::unique_lock<std::mutex> lk(cv_m_);
    cv_.wait(lk, [this]{ return value_ > 0; });
    --value_;
  }
  inline void signal() { ++value_; cv_.notify_one(); }
  inline void signal(unsigned count) { value_ += count; cv_.notify_all(); }
};
