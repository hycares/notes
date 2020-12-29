#include "part.hpp"


class AbstractFactory {
public:
  virtual AbstractPartA* buildPartA() = 0;
  virtual AbstractPartB* buildPartB() = 0;
  virtual ~AbstractFactory() {}
};

// 抽象工厂, 将有依赖的组件放到一个工厂里！
class FactoryOne : public AbstractFactory {
public:
  virtual AbstractPartA* buildPartA() {
    return new PartA1();
  }
  virtual AbstractPartB* buildPartB() {
    return new PartB1();
  };
};

class FactoryTwo : public AbstractFactory {
public:
  virtual AbstractPartA* buildPartA() {
    return new PartA2();
  }
  virtual AbstractPartB* buildPartB() {
    return new PartB2();
  }
};

