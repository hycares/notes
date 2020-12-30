#include "spliter.hpp"


class MainForm {
private:
  ISpliter *spliter;
public:
  MainForm(ISpliter *f) : spliter(f) {}
  void click() {
    // 通过已有的状态clone一个新的对象
    ISpliter *s = spliter->clone();
    s->split();
    delete s;
  }
};


int main() {
  BinarySpliter bs{"path", 4};
  MainForm mf1(&bs);

  mf1.click();
  mf1.click();
}