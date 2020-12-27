#include "subject.hpp"
#include <iomanip>

class ProgressBar : public Observer {
public:
  void update(int val) {
    // progress logic
    std::cout << "\rProgress: [";
    for (int i=0; i<val; i++) 
      std::cout << "#";
    std::cout << std::setw(11 - val) << "]";
    std::cout << std::flush;
  }
};

class TerminalVal : public Observer {
public:
  void update(int val) {
    std::cout << " status: [" << std::setw(4) << val*10 << "%]" << std::flush;
  }
};

class MainForm {
private:
  ProgressBar pb;
  TerminalVal tv;
  DownloadStatus ds;
public:
  MainForm() {
    ds.addObserver(&pb);
    ds.addObserver(&tv);
  }
  void click() {
    ds.download(); 
  }
};

int main(int argc, char const *argv[])
{
  MainForm mf;
  mf.click();
  return 0;
}
