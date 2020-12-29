#include "spliter.hpp"

class SpliterFactory {
public:
  virtual ISpliter* CreateSpliter(std::string path, size_t count) = 0;  
};


class BinarySpliterFactory : public SpliterFactory {
public:
  ISpliter* CreateSpliter(std::string path, size_t count) {
    return new BinarySpliter(path, count);
  }
};


class PictureSpliterFactory : public SpliterFactory {
public:
  ISpliter* CreateSpliter(std::string path, size_t count) {
    return new PictureSpliter(path, count);
  }
};


class VideoSpliterFactory : public SpliterFactory {
public:
  ISpliter* CreateSpliter(std::string path, size_t count) {
    return new VideoSpliter(path, count);
  }
};
