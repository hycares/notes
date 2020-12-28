#include "stream.hpp"

int main() {
  FileStream fs;
  fs.read(10);
  NetworkStream ns;
  ns.read(10);

  BufferedStream bfs(&fs);
  bfs.seek(100);
  CryptoStream cns(&ns);
  cns.write("123", 3);

  CryptoStream cbfs(&bfs);
  cbfs.write("crypto", 6);
}