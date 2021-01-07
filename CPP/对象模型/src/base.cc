#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
 
    Base(int i) :baseI(i){};

    virtual void print(void){ cout << "调用了虚函数Base::print()"; }

    virtual void setI(){cout<<"调用了虚函数Base::setI()";}

    virtual ~Base(){}
 
private:
 
    int baseI;

};

int main(int argc, char const *argv[])
{
  Base b(1000);
  int * vptrAdree = (int *)(&b);  
  cout << "虚函数指针（vprt）的地址是：\t"<<vptrAdree << endl;
  typedef void(*Fun)(void);
  Fun vfunc = (Fun)*( (int *)*(int*)(&b));
  cout << "第一个虚函数的地址是：" << (int *)*(int*)(&b) << endl;
  cout << "通过地址，调用虚函数Base::print()：";
  vfunc();
  return 0;
}
