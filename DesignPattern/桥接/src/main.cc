#include "control.hpp"

int main() {
  // 动态组合
  ControlImp *dimp = new DarwinImp();
  ControlBase *pcb = new PanelControl(dimp);
  pcb->login();
  pcb->exit();

  ControlImp *wimp = new WinNTImp();
  ControlBase *tcb = new TextControl(wimp);
  tcb->login();
  tcb->exit();

  delete dimp;
  delete pcb;
  delete wimp;
  delete tcb;
}