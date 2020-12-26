#include "strategy.hpp"

int main(int argc, char const *argv[])
{
  Context con{1};

  StrategyA sa;
  StrategyB sb;
  StrategyOp op1{&sa};
  StrategyOp op2{&sb};

  op1.call(con);
  op2.call(con);

  return 0;
}
