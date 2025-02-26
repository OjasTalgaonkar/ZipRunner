#include "emulate.hh"

Emulator emulator;

void Emulator::initialize() {
  pc = 0x200;
  I = 0;
  opcode = 0;
  sp = 0;

  for (int i = 0; i < 80; ++i) {
    memory[i] = fontset[i];
  }

  for (int i = 0; i < bufferSize; ++i)
    memory[i + 512] = buffer[i];
}

int main() {}
