#include <stdint.h>

class chip8
{
private:
    uint16_t opcode;
    uint8_t memory[4096];
    uint8_t V[16];
    uint16_t I;
    uint16_t pc;
    uint8_t gfx[64 * 32];
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t stack[16];
    uint16_t sp;
    uint8_t key[16];

public:
    chip8();
    ~chip8();
    void initialize();
    void emulateCycle();

    uint8_t getRegister(const int regname) const;
    uint16_t getPc() const;
};

