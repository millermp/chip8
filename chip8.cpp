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
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            gfx[i * j] = 0;
        }
    }

    // clear stack
    for (int i = 0; i < 16; i++) {
        stack[i] = 0;
    }

    // clear registers V0-VF
    for (int i = 0; i < 16; i++) {
        V[i] = 0;
    }

    // clear memory
    for (int i = 0; i< 4096; i++) {
        memory[i] = 0;
    }

    // load fonts
    for (int i = 0; i < 80; ++i) {
        memory[i+80] = chip8_fontset[i];
    }

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
            switch(opcode & 0x000F) {
                case 0x0000: // 0x00E0: Clears the screen
                {
                    printf("Clear Screen\n");
                    pc += 2;
                }
                    break;
                case 0x000E: // 0x00EE: Returns from subroutine
                    // execute
                    // pop value from stack and set PC to value
                    {
                    printf("Unimplemented 0x00EE\n");
                    }
                    break;
                
                default:
                {
                    printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
                    pc += 2;
                }
            }
            break;
        case 0x1000: // 1NNN: Jump
        {
            if ((opcode & 0xFFF) == pc) break;
            printf("JUMP 0x%03X\n", (opcode & 0xFFF));
            pc = opcode & 0xFFF;
        }
            break;
        case 0x2000: // 2NNN: Subroutine
            // push current PC value to stack and set PC to NNN
            {
            printf("Unimplemented 0x2NNN\n");
            pc += 2;
            }
            break;
        case 0x6000: // 6XNN: Set register VX to NN
        {
            printf("LD V%d, %X\n", (opcode >> 8) & 0x0F, opcode & 0x00FF);
            int reg = (opcode >> 8) & 0x0F;
            V[reg] = opcode & 0x00FF;
            pc += 2;
        }
            break;
        case 0x7000: // 7XNN: Add NN to register VX
        {
            printf("ADD V%d, %X\n", (opcode >> 8) & 0x0F, opcode & 0x00FF);
            int reg = (opcode >> 8) & 0x0F;
            V[reg] += opcode & 0x00FF;
            pc += 2;
        }
            break;
        case 0xA000: // ANNN: Sets I to the address NNN
        {
            printf("LD I, 0x%03X\n", opcode & 0x0FFF);
            I = opcode & 0x0FFF;
            pc += 2;
        }
            break;
        case 0xD000: // DXYN: Draw stuff
        {
            // TODO: Add drawing
            printf("DRW V%d, V%d, %X\n", (opcode >> 8) & 0x0F, (opcode >> 4) & 0xF, opcode & 0xF);
            pc += 2;
        }
            break;

        default:
        {
            printf("Unknown opcode: 0x%X\n", opcode);
            pc += 2;
        }
    }

    // Update timers
    if (delay_timer > 0)
        --delay_timer;

    if (sound_timer > 0) {
        if (sound_timer == 1)
            printf("BEEP!\n");
        --sound_timer;
    }
}

void chip8::loadFile(const char *filename)
{
    uint8_t buffer[4096-512];
    FILE *rom = fopen(filename, "rb");
    if (rom != NULL) {
        size_t newLen = fread(buffer, sizeof(uint8_t), 4096-512, rom);
        if (ferror(rom) != 0) {
            fputs("error reading file", stderr);
        } else {
            buffer[newLen++] = '\0';
        }
    }
    fclose(rom);

    for (int i=0; i<(int)sizeof(buffer); ++i) {
        memory[i+512] = buffer[i];
    }
}

uint8_t chip8::getMemory(const int address) const
{
    return memory[address];
}

uint16_t chip8::getI() const
{
    return I;
}

uint16_t chip8::getSp() const
{
    return sp;
}

uint16_t chip8::getStackEntry(const int index) const
{
    return stack[index];
}