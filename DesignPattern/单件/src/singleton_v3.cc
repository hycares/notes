#include <mutex>

class Singleton
{
private:
  Singleton() {};
  Singleton(const Singleton& s) = delete;
  static std::mutex mtx;
  static Singleton *m_instance;
public:
  static Singleton* getInstance();
  ~Singleton() {
    if (m_instance != nullptr) delete m_instance;
    m_instance = nullptr;
  }
};


// 使用双检查锁！ [存在问题]
Singleton* Singleton::getInstance() {
  if (m_instance == nullptr) {
    Singleton::mtx.lock();
    if (m_instance == nullptr) {
      // 看上去似乎没有问题，但是这里存在内存序问题
      // 首先来分析new构造函数的过程
      // 1. 分配内存
      // 2. 调用构造函数
      // 3. 返回地址
      // 当这些步骤生成汇编代码，乃至机器码时，他们的执行顺序不一定按照 1-2-3
      // 有可能是 1-3-2
      // 在这种情况下，另外一个线程去执行时会发现 指针不为空，可是在调用相关函数时却会找不到函数地址
      // 因为没有调用构造函数
      m_instance = new Singleton();
    }
    Singleton::mtx.unlock();
  }
  return m_instance;
}