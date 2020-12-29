#include <iostream>

class AbstractPartA {
public:
  virtual void partA() = 0;
  virtual ~AbstractPartA() {}
};


class AbstractPartB {
public:
  virtual void partB() = 0;
  virtual ~AbstractPartB() {}
};


class PartA1 : public AbstractPartA {
public:
  void partA() {
    std::cout << "version 1 in partA" << std::endl;
  }
};

class PartA2 : public AbstractPartA {
public:
  void partA() {
    std::cout << "version 2 in partA" << std::endl;
  }
};

class PartB1 : public AbstractPartB {
public:
  void partB() { 
    std::cout << "version 1 in partB" << std::endl;
  }
};

class PartB2 : public AbstractPartB {
public:
  void partB() { 
    std::cout << "version 2 in partB" << std::endl;
  }
};