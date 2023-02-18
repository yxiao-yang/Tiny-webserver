#ifndef THREAD_H
#define THREAD_H

#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <atomic>

#include "noncopyable.h"

class Thread : noncopyable {
 public:
  using ThreadFunc = std::function<void()>;
  explicit Thread(ThreadFunc, const std::string &name = std::string());
  ~Thread();

  void Start(); // 开启线程
  void Join();  // 等待线程

  bool Started() const { return started_; }
  pid_t Tid() const { return tid_; }
  const std::string& Name() const { return name_; }

  static int NumCreated() { return numCreated_; }

 private:
  void SetDefaultName();  // 设置线程名

  bool started_;  // 是否启动线程
  bool joined_;   // 是否等待该线程
  std::shared_ptr<std::thread> thread_;
  pid_t tid_;     // 线程tid
  // Thread::start() 调用的回调函数
  // 其实保存的是 EventLoopThread::threadFunc()
  ThreadFunc func_;   
  std::string name_;  // 线程名
  static std::atomic_int32_t numCreated_; // 线程索引
};

#endif // THREAD_H