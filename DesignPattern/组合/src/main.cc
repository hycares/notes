#include "composite.hpp"

void Do(Component* c) {
  c->process();
}

int main() {
  // 数据结构组合
  Node r("root");
  Node t1("t1");
  Node t2("t2");
  Node t3("t3");
  Node t4("t4");
  Leaf l1(1);
  Leaf l2(2);
  t1.add(&t2);
  t2.add(&l1);
  t3.add(&t4);
  t4.add(&l2);
  r.add(&t1);
  r.add(&t3);

  Do(&r);
}