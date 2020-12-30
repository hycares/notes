#include "house.hpp"

int main() {
  House h1;
  Builder *b1 = new StoneHouseBuilder(&h1);
  Director d1(b1);
  d1.build();
  House *p = b1->getHouse();
  std::cout << "[" << p->getDoor() << " " << p->getWall() << " " << int(p->getColor()) << "]" << std::endl;

  Builder *b2 = new FlatHouseBuilder();
  Director d2(b2);
  d2.build();
  p = b2->getHouse();
  std::cout << "[" << p->getDoor() << " " << p->getWall() << " " << int(p->getColor()) << "]" << std::endl;
  delete p;
}