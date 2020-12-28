#include <iostream>

class Stream {
public:
  virtual size_t read(size_t bytes) = 0;
  virtual size_t write(const char buf[], size_t bytes) = 0;
  virtual size_t seek(size_t bytes) = 0;
  virtual ~Stream() {};
};

// FileStream.hpp
class FileStream : public Stream{
public:
  size_t read(size_t bytes) {
    std::cout << "FileStream Read: " << bytes << std::endl;
    // ... operation
    return bytes;
  }

  size_t write(const char buf[], size_t bytes) {
    std::cout << "FileStream Write: ";
    for (size_t b=0; b<bytes; ++b) {
      std::cout << buf[b];
    }
    std::cout << std::endl;
    return bytes;
  }

  size_t seek(size_t bytes) {
    std::cout << "FileStream Seek: " << bytes << std::endl;
    return bytes;
  }
};


// NetworkStream.hpp
class NetworkStream : public Stream{
public:
  size_t read(size_t bytes) {
    std::cout << "NetworkStream Read: " << bytes << std::endl;
    // ... operation
    return bytes;
  }

  size_t write(const char buf[], size_t bytes) {
    std::cout << "NetworkStream Write: ";
    for (size_t b=0; b<bytes; ++b) {
      std::cout << buf[b];
    }
    std::cout << std::endl;
    return bytes;
  }

  size_t seek(size_t bytes) {
    std::cout << "NetworkStream Seek: " << bytes << std::endl;
    return bytes;
  }
};



// BufferedStream.hpp   Decorator
class BufferedStream : public Stream {
private:
  // !!! important
  Stream *stream;
public:
  BufferedStream(Stream *stm) : stream(stm) {}

  size_t read(size_t bytes) {
    std::cout << "Buffered Operation" << std::endl;
    auto r = stream->read(bytes);
    return r;
  }

  size_t write(const char buf[], size_t bytes) {
    std::cout << "Buffered Operation" << std::endl;
    auto r = stream->write(buf, bytes);
    return r;    
  }

  size_t seek(size_t bytes) {
    std::cout << "Buffered Operation" << std::endl;
    auto r = stream->seek(bytes);
    return r;        
  }
};


// CryptoStream.hpp   Decorator
class CryptoStream : public Stream {
private:
  // !!! important
  Stream *stream;
public:
  CryptoStream(Stream *stm) : stream(stm) {}

  size_t read(size_t bytes) {
    std::cout << "Crypto Operation" << std::endl;
    auto r = stream->read(bytes);
    return r;
  }

  size_t write(const char buf[], size_t bytes) {
    std::cout << "Crypto Operation" << std::endl;
    auto r = stream->write(buf, bytes);
    return r;    
  }

  size_t seek(size_t bytes) {
    std::cout << "Crypto Operation" << std::endl;
    auto r = stream->seek(bytes);
    return r;        
  }
};