#include <iostream>

struct Context {
  int val;
  Context(int v) : val(v) {}
};

class Strategy {
public:
  virtual void algorithm(const Context& context) = 0;
  virtual ~Strategy() {}
};


class StrategyA : public Strategy{
public:
  void algorithm(const Context& context) {
    std::cout << "algoA: " << context.val << std::endl;
  }
};


class StrategyB : public Strategy{
public:
  void algorithm(const Context& context) {
    std::cout << "algoB: " << context.val << std::endl;
  }
};


class StrategyOp {
private:
  Strategy* strategy;
public:
  StrategyOp(Strategy* s) : strategy(s) {}
  void call(const Context& context) {
    strategy->algorithm(context);
  }
};