#include <bits/stdc++.h>

class Semaphore {
public:
  Semaphore(int value = 0) {
    this->value = value;
  }
  
  void post() {
    std::lock_guard<std::mutex> lck(mtx);
    value++;
    cv.notify_all();
  }
  
  void wait() {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck, [this]{ return value > 0; });
    value--;
  }
private:
  int value;
  std::mutex mtx;
  std::condition_variable cv;
};
