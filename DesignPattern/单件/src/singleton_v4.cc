#include <atomic>
#include <mutex>

class Singleton
{
private:
  Singleton() {};
  Singleton(const Singleton& s) = delete;

  static std::atomic<Singleton *> m_instance;
  static std::mutex mtx;
public:
  static Singleton* getInstance();
  ~Singleton();
};

// 双检查锁的漏洞在于内存序问题，只能通过内存屏障来控制
Singleton* Singleton::getInstance() {
  Singleton *tmp = m_instance.load(std::memory_order_relaxed);

  if (tmp == nullptr) {
    std::lock_guard<std::mutex> lg(Singleton::mtx);
    tmp = m_instance.load(std::memory_order_relaxed);

    if (tmp == nullptr) {
      tmp = new Singleton();
      std::atomic_thread_fence(std::memory_order_relaxed);
      m_instance.store(tmp, std::memory_order_relaxed);
    }
  }
  
  return tmp;
}