#include "lib.hpp"


// 实现具体逻辑
class App : public Lib {
private:
  int times;
public:
  App(int t) : times(t) {}
  
  virtual int step2() {
    std::cout << "step2: " << times << std::endl;
    return times;
  }

  virtual void step4() {
    std::cout << "step4" << std::endl;
  }
};


// 动态绑定可以借助指针和引用
void func(Lib& lib) {
  lib.run();
}

int main(int argc, char const *argv[])
{
  Lib *lib = new App(2);
  lib->run();
  delete lib;

  App app{1};
  func(app);

  return 0;
}  