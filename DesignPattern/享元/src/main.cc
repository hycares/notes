#include "flyweight.hpp"

int main() {
  ChessFactory cf;

  auto wc = cf.get(COLOR::WHITE);
  wc->draw(0, 2);

  auto bc = cf.get(COLOR::BLACK);
  bc->draw(4, 5);

  auto wc2 = cf.get(COLOR::WHITE);

  std::cout << "wc at " << wc << std::endl;
  std::cout << "wc2 at " << wc2 << std::endl;
}