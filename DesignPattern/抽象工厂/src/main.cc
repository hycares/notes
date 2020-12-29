#include "factory.hpp"

int main(int argc, char const *argv[])
{
  AbstractFactory* af1 = new FactoryOne();
  AbstractFactory* af2 = new FactoryTwo();

  AbstractPartA* pa1 = af1->buildPartA();
  AbstractPartB* pb1 = af1->buildPartB();

  pa1->partA();
  pb1->partB();

  AbstractPartA* pa2 = af2->buildPartA();
  AbstractPartB* pb2 = af2->buildPartB();

  pa2->partA();
  pb2->partB();

  return 0;
}
