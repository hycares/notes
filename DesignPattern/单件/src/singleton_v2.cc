#include <mutex>
#include <thread>

class Singleton
{
private:
  Singleton() {};
  Singleton(const Singleton& s) = delete;
  static std::mutex mtx;
  static Singleton *m_instance;
public:
  static Singleton* getInstance();
  ~Singleton();
};

Singleton* Singleton::getInstance() {

  // 加锁使得线程同步，避开竞争
  mtx.lock();
  
  if (m_instance == nullptr) {
    m_instance = new Singleton();
  }

  mtx.unlock();

  // 存在问题，这种竞争实际上只有第一次才会有，之后可以直接返回，每次加锁
  // 会带来很大的性能损失，所以这种方法降低了性能，而单例模式的初衷就是提高性能

  return m_instance;
}
