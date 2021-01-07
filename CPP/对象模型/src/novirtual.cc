#include <iostream>

class NoVirtual {
public:
  NoVirtual(int i) : val(i) {}

  static int hello(int a, int b) {
    int c = 1;
    return c + a + b;
  }

  static int sval;

  int getVal() {return val;}
  void setVal(int v) {val = v;}
  int val;
};

int NoVirtual::sval = 1;

int main() {
  NoVirtual n(1);
  std::cout << "n address: " << &n << std::endl;         // the same address as below
  std::cout << "n.val address: " << &n.val << std::endl;
  
  std::cout << "n.getVal address: " << (void *)&NoVirtual::getVal << std::endl;

  // 静态变量地址 明显不在一个区域
  std::cout << "hello address: " << (void *)&NoVirtual::hello << std::endl;
  std::cout << "sval address: " << &NoVirtual::sval << std::endl;
}