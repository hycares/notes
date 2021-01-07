#include <iostream>

class Virtual {
public:
  Virtual(int i) : val(i) {}

  static int hello(int a, int b) {
    int c = 1;
    return c + a + b;
  }

  static int sval;

  int getVal() {return val;}
  void setVal(int v) {val = v;}

  virtual void print1() {
    std::cout << "virtual-print1: " << val << std::endl;
  }

  virtual void print2() {
    std::cout << "virtual-print2: " << val << std::endl;
  }

  int val;
};

int Virtual::sval = 1;

int main() {
  Virtual n(1);
  std::cout << "n address: " << &n << std::endl;         // 地址不一致，差了一个指针的大小
  std::cout << "n.val address: " << &n.val << std::endl;
  
  unsigned *vptr = (unsigned *)&n;  // 对象模型，第一个成员时虚函数指针
  std::cout << "vpointer: " << vptr << std::endl;

  typedef void(*FUNC)(void);

  unsigned *vtable = (unsigned *)(*vptr);
  std::cout << "vtable: " << vtable << std::endl;

  FUNC vprint1 = (FUNC)*( (int *)*(int*)(&n)); // (FUNC) *vtable
  std::cout << "virtual print1: " << vprint1 << std::endl;
  std::cout << "n.print1: " << (void *)(&Virtual::print1) << std::endl;

  /*
  std::cout << "n.getVal address: " << (void *)(&Virtual::getVal) << std::endl;
  std::cout << "n.print address: " << (void *)(&Virtual::print1) << std::endl;

  // 静态变量地址 明显不在一个区域
  std::cout << "hello address: " << (void *)&Virtual::hello << std::endl;
  std::cout << "sval address: " << &Virtual::sval << std::endl;
  */
}