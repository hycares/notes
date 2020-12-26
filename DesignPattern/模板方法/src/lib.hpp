#include <iostream>

class Lib
{
  // 不变的方法可以放在protected
  // 算法流程也是不变但需要暴露给外层
protected:
  void step1() {
    std::cout << "step1" << std::endl;
  }

  void step3() {
    std::cout << "step3" << std::endl;
  }

  void step5() {
    std::cout << "step5" << std::endl;
  }

public:
  virtual int step2() = 0;
  virtual void step4() = 0;
  Lib() {}

  void run() {
    step1();
    int t = step2();
    step3();
    for (int i=0; i<t; ++i)
      step4();
    step5();
  }

  virtual ~Lib() {}
};
