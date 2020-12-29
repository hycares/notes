#include "factory.hpp"


class MainForm {
private:
  SpliterFactory *factory;
public:
  MainForm(SpliterFactory *f) : factory(f) {}
  void click() {
    ISpliter *s = factory->CreateSpliter("main.cc", 4);
    s->split();
  }
};


int main() {
  BinarySpliterFactory bsf;
  PictureSpliterFactory psf;
  VideoSpliterFactory vsf;
  
  MainForm mf1(&bsf);
  MainForm mf2(&psf);
  MainForm mf3(&vsf);

  mf1.click();
  mf2.click();
  mf3.click();
}