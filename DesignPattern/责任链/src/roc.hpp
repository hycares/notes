#include <iostream>

using namespace std;

enum class COLOR {
  RED,
  GREEN,
  BLUE
};

class Request {
  COLOR c;
public:
  Request(COLOR clr) : c(clr) {}
  COLOR getColor() const {
    return c;
  }
};

class Handler {
protected:
  Handler* pNext;
public:
  Handler() : pNext(nullptr) {}
  void setNext(Handler* handler) {
    pNext = handler;
  }
  virtual void handler(Request* r) = 0;
  virtual ~Handler() {}
};

class RedHandler : public Handler {
public:
  void handler(Request* r) {
    if (r->getColor() == COLOR::RED) {
      cout << "Red Handler catch the Request" << endl;
      return;
    }
    if (this->pNext != nullptr) {
      this->pNext->handler(r);
    } else {
      cout << "Can't handle" << endl;
    }
  }
};

class GreenHandler : public Handler {
public:
  void handler(Request* r) {
    if (r->getColor() == COLOR::GREEN) {
      cout << "Green Handler catch the Request" << endl;
      return;
    }
    if (this->pNext != nullptr) {
      this->pNext->handler(r);
    } else {
      cout << "Can't handle" << endl;
    }
  }
};