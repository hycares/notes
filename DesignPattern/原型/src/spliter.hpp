#include <iostream>
#include <string>

class ISpliter {
protected:
  std::string filepath;
  size_t count;
public:
  ISpliter(std::string path, size_t c) : filepath(path), count(c) {}
  virtual void split() = 0;
  virtual ISpliter* clone() = 0;
  virtual ~ISpliter() {}
};


class BinarySpliter : public ISpliter{
public:
  BinarySpliter(std::string path, size_t c) : ISpliter(path, c) {
  }
  
  BinarySpliter(const BinarySpliter& bs) : ISpliter(bs.filepath, bs.count) {

  }
  
  void split() {
    std::cout << "Binary Spliter: " << filepath << " " << count << std::endl;
  }


  ISpliter* clone() {
    return new BinarySpliter(*this);
  }
};