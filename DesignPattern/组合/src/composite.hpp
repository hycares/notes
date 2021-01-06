#include <iostream>
#include <list>
#include <string>
using namespace std;

class Component {
public:
  virtual void process() = 0;
  virtual ~Component() {};
};

class Node : public Component {
private:
  string id;
  list<Component *> nodes;
public:
  Node(const string& str) : id(str) {}
  void add(Component* node) {
    nodes.push_back(node);
  }
  void remove(Component* node) {
    nodes.remove(node);
  }
  void process() {
    cout << id << endl;
    for (auto& n : nodes) {
      n->process();
    }
  }
};

class Leaf : public Component {
private:
  int id;
public:
  Leaf(int i) : id(i) {}
  void process() {
    cout << "leaf: " << id << endl;
  }
};