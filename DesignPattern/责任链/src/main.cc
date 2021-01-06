#include "roc.hpp"

int main() {
  RedHandler rh;
  GreenHandler gh;
  rh.setNext(&gh);

  Request r{COLOR::GREEN};
  Request b{COLOR::BLUE};

  rh.handler(&r);  
  rh.handler(&b);  
}