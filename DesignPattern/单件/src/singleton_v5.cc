class Singleton
{
private:
  Singleton() {};
  Singleton(const Singleton& s) = delete;
  Singleton& operator=(const Singleton&) = delete;
public:
  static Singleton& getInstance();
  ~Singleton();
};

// 前提 使用 C++11
// C++11规定，在一个线程开始local static 对象的初始化后到完成初始化前，
// 其他线程执行到这个local static对象的初始化语句就会等待，
// 直到该local static 对象初始化完成。
Singleton& Singleton::getInstance() {
  static Singleton instance;
  return instance;
}