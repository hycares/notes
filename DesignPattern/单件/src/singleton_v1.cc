class Singleton
{
private:
  Singleton() {};
  Singleton(const Singleton& s) = delete;

  static Singleton *m_instance;
public:
  static Singleton* getInstance();
  ~Singleton();
};

// 如果有多线程访问则必然会产生碎片
Singleton* Singleton::getInstance() {
  if (m_instance == nullptr) {
    m_instance = new Singleton();
  }
  return m_instance;
}
