#include <iostream>

class TCPState {
public:
  TCPState* next;
public:
  virtual void ACK() = 0;
  virtual void FIN() = 0;
  virtual void SYN() = 0;
};

class Close : public TCPState {
private:
  Close() {}

  static Close* self;
public:
  static TCPState* instance() {
    if (self == nullptr) {
      self = new Close();
    }
    return self;
  }

  void ACK() {
    std::cout << "Close ACK" << std::endl;
    next = instance();
  }

  void FIN() {
    std::cout << "Close FIN" << std::endl;
    next = instance();
  }

  void SYN() {
    std::cout << "Close SYN" << std::endl;
    next = instance();
  }
};

Close* Close::self = nullptr;

class Connect : public TCPState {
private:
  Connect() {}

  static Connect* self; // singleton
public:
  static TCPState* instance() {
    if (self == nullptr) {
      self = new Connect();
    }
    return self;
  }

  void ACK() {
    std::cout << "Connect SYN" << std::endl;
    next = instance();
  }

  void FIN() {
    std::cout << "Connect FIN" << std::endl;
    next = Close::instance();
  }

  void SYN() {
    std::cout << "Connect SYN" << std::endl;
    next = instance();
  }
};

Connect* Connect::self = nullptr;

class Init : public TCPState {
private:
  Init() {}
  static Init* self;
public:
  static TCPState* instance() {
    if (self == nullptr) {
      self = new Init();
    }
    return self;
  }

  void ACK() {
    std::cout << "Init ACK" << std::endl;
    next = Connect::instance();
  }

  void FIN() {
    std::cout << "Init FIN" << std::endl;
    next = instance();
  }

  void SYN() {
    std::cout << "Init SYN" << std::endl;
    next = instance();
  }
};

Init* Init::self = nullptr;

