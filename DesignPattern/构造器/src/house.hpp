#include <iostream>
#include <string>

// 表示
class House {
private:
  std::string door;
  std::string wall;
  uint8_t color;
public:
  House() {}
  House(std::string d, std::string w, uint8_t c) : door(d), wall(w), color(c) {}
  ~House() {}

  void setDoor(std::string d) {
    this->door = d;
  }

  std::string getDoor() const {
    return this->door;
  }

  void setWall(std::string w) {
    this->wall = w;
  }

  std::string getWall() const {
    return this->wall;
  }

  void setColor(uint8_t color) {
    this->color = color;
  }

  uint8_t getColor() const {
    return this->color;
  }
};


class Builder {
protected:
  House *house;
public:
  Builder(House *h) : house(h) {}
  Builder() {
    house = new House();
  }
  ~Builder() {}

  virtual void buildDoor() = 0;
  virtual void buildWall() = 0;
  virtual void paintColor() = 0;
  House* getHouse() {
    return house;
  }
};

// 构建过程
class StoneHouseBuilder : public Builder {
public:
  StoneHouseBuilder() : Builder() {}
  StoneHouseBuilder(House *h) : Builder(h) {}

  void buildDoor() {
    house->setDoor("Stone door");
  }

  void buildWall() {
    house->setWall("Stone wall");
  }

  void paintColor() {
    house->setColor(2);
  }
};

class FlatHouseBuilder : public Builder {
public:
  FlatHouseBuilder() : Builder() {}
  FlatHouseBuilder(House *h) : Builder(h) {}

  void buildDoor() {
    house->setDoor("Steel door");
  }

  void buildWall() {
    house->setWall("Cement wall");
  }

  void paintColor() {
    house->setColor(1);
  }
};

class Director {
  Builder *builder;
public:
  Director(Builder *b) : builder(b) {}
  void build() {
    builder->buildDoor();
    builder->buildWall();
    builder->paintColor();
  }
};