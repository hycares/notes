#include <iostream>

class ControlImp;

class ControlBase {
protected:
// 拥有一个实现类指针
  ControlImp *controlImp;
public:
  ControlBase(ControlImp *imp) : controlImp(imp) {}
  virtual void login() = 0;
  virtual void exit() = 0;
  virtual ~ControlBase() {}
};


class ControlImp {
public:
  virtual void init() = 0;
  virtual void setup() = 0;
  virtual void retrieve() = 0;
};


// Refined Abstraction
class PanelControl : public ControlBase {
public:
  PanelControl(ControlImp *imp) : ControlBase(imp) {

  }

  void login() {
    controlImp->init();
    controlImp->setup();
    std::cout << "PanelLogin" << std::endl;
  }

  void exit() {
    std::cout << "PanelExit" << std::endl;
    controlImp->retrieve();
  }
};


class TextControl : public ControlBase {
public:
  TextControl(ControlImp *imp) : ControlBase(imp) {

  }

  void login() {
    controlImp->init();
    controlImp->setup();
    std::cout << "TextLogin" << std::endl;
  }

  void exit() {
    std::cout << "TextExit" << std::endl;
    controlImp->retrieve();
  }
};


// 实现维度
class DarwinImp : public ControlImp {
public:
  void init() {
    std::cout << "Darwin Init" << std::endl;
  }
  void setup() {
    std::cout << "Darwin Setup" << std::endl;
  }
  void retrieve() {
    std::cout << "Darwin Retrieve" << std::endl;
  }
};


class WinNTImp : public ControlImp {
public:
  void init() {
    std::cout << "Windows Init" << std::endl;
  }
  void setup() {
    std::cout << "Windows Setup" << std::endl;
  }
  void retrieve() {
    std::cout << "Windows Retrieve" << std::endl;
  }
};


class LinuxImp : public ControlImp {
public:
  void init() {
    std::cout << "Linux Init" << std::endl;
  }
  void setup() {
    std::cout << "Linux Setup" << std::endl;
  }
  void retrieve() {
    std::cout << "Linux Retrieve" << std::endl;
  }
};