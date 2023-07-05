#include "chip8.h"
#include <stdio.h>

unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

chip8::chip8()
{
}

chip8::~chip8()
{
}

uint8_t chip8::getRegister(const int regname) const
{
    return V[regname];
}

uint16_t chip8::getPc() const
{
    return pc;
}

void chip8::initialize()
{
    // Initialize registers and memory once
    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;

    // clear display
    // clear stack
    // clear registers V0-VF
    for (int i = 0; i < 16; i++) {
        V[i] = 0;
    }

    // clear memory
    for (int i = 0; i< 4096; i++) {
        memory[i] = 0;
    }

    // load fonts

    // reset timers
    delay_timer = 0;
    sound_timer = 0;
}

void chip8::emulateCycle()
{
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];

    // Decode Opcode
    switch(opcode & 0xF000) {
        case 0x0000:
            break;
        default:
            printf("Unknown opcode: 0x%X\n", opcode);
    }
    // Execute Opcode

    // Update timers
    if (delay_timer > 0)
        --delay_timer;

    if (sound_timer > 0) {
        if (sound_timer == 1)
            printf("BEEP!\n");
        --sound_timer;
    }
}


