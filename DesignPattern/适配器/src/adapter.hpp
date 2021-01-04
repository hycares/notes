#include <iostream>


// 旧的接口
class OldIpart {
public:
  virtual void doWork() = 0;
};

// 新的接口
class ITarget {
public:
  virtual void Do() = 0;
};


class Adaptee : public OldIpart {
public:
  void doWork() {
    std::cout << "old interface function" << std::endl;
  }
};

class Adapter : public ITarget {
protected:
  OldIpart *pada; // 通过指针形式 方便扩展
public:
  Adapter(OldIpart *p) : pada(p) {}

  void Do() {
    std::cout << "Using Adapter: ";
    pada->doWork();
  }
};

class AnotherAdapter : public ITarget, 
                       protected Adaptee  // 固定，不利于扩展，但是如果只有一个需要扩展可以这样写！
                       {
public:
  void Do() {
    std::cout << "Using Another Adapter: ";
    this->doWork();
  }
};
