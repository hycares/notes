#include "adapter.hpp"


void client(ITarget *p) {
  p->Do();
}

int main(int argc, char const *argv[])
{
  Adaptee old;
  Adapter adapter(&old);
  AnotherAdapter ano;

  client(&adapter);
  client(&ano);
  return 0;
}
