#include <iostream>
#include <string>

class ISpliter {
protected:
  std::string filepath;
  size_t count;
public:
  ISpliter(std::string path, size_t c) : filepath(path), count(c) {}
  virtual void split() = 0;
  virtual ~ISpliter() {}
};


class BinarySpliter : public ISpliter{
public:
  BinarySpliter(std::string path, size_t c) : ISpliter(path, c) {}
  void split() {
    std::cout << "Binary Spliter: " << filepath << " " << count << std::endl;
  }
};


class PictureSpliter : public ISpliter{
public:
  PictureSpliter(std::string path, size_t c) : ISpliter(path, c) {}
  void split() {
    std::cout << "Picture Spliter: " << filepath << " " << count << std::endl;
  }
};


class VideoSpliter : public ISpliter{
public:
  VideoSpliter(std::string path, size_t c) : ISpliter(path, c) {}
  void split() {
    std::cout << "Video Spliter: " << filepath << " " << count << std::endl;
  }
};