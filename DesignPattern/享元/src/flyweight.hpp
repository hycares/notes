#include <iostream>
#include <map>

enum class COLOR {
  BLACK,
  WHITE
};

class Chess {
protected:
  COLOR C; // internal state
public:
  Chess(COLOR color) : C(color) {}

  // x, y is external state
  virtual void draw(unsigned x, unsigned y) = 0;
};

class WhiteChess : public Chess {
public:
  WhiteChess() : Chess(COLOR::WHITE) {}
  
  void draw(unsigned x, unsigned y) {
    std::cout << "White at " << x << ", " << y << std::endl;
  }
};

class BlackChess : public Chess {
public:
  BlackChess() : Chess(COLOR::BLACK) {}
  
  void draw(unsigned x, unsigned y) {
    std::cout << "Black at " << x << ", " << y << std::endl;
  }
};

class ChessFactory {
  std::map<COLOR, Chess *> chessmap;

public:
  Chess* get(COLOR c) {
    if (chessmap.find(c) == chessmap.end()) {
      if (c == COLOR::WHITE) chessmap[c] = new WhiteChess;
      else chessmap[c] = new BlackChess;
    }
    return chessmap[c];
  }
};