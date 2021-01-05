#include "state.hpp"

class Client {
private:
  TCPState* state;
public:
  Client(TCPState* s) : state(s) {
  }

  void ACK() {
    state->ACK();
    state = state->next;
  }

  void SYN() {
    state->SYN();
    state = state->next;
  }

  void FIN() {
    state->FIN();
    state = state->next;
  }
};


int main(int argc, char const *argv[])
{
  Client c(Init::instance());
  c.ACK();
  c.FIN();
  c.SYN();
  return 0;
}
