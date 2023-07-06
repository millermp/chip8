CHIP-8 interpreter

Needs
- Memory: 4 KiB RAM
- Display: 64 x 32 pixel (or 128 x 64 for SUPER-CHIP)
- Program Counter: PC
- Index Register: 16 bit - I
- Stack: 16 bit
- Delay Timer: 8 bit, decremented at 60Hz
- Sound Timer: 
- GP Registers: 16 x 8 bit, V0 - VF. VF is also the Flag Register

TO DO:
- Add Delay Timers
  - Sync Timer to 60 Hz
- Add sound timer
- Add input handler
- Add File handling (Open, Recent, etc.)
- Complete opcode handlers
- Add stack implementation
- Instruction stepper, pause, run, restart
- Add memory & register editor
- Add Disassembler view
- Make graphical display nicer
- Refactor & cleanup
  - Opcodes as function pointers?
  - Make into more pure C++

Translation of IBM Logo.ch8:
200. 00E0 CLS            # Clear Screen
202. A22A LD I, 22A      # Set I to 22A
204. 600C LD V0, 0C      # Set V0 to 0C
206. 6108 LD V1, 08      # Set V1 to 08
208. D01F DRW V0, V1, F  # Draw 16 bytes from memory, starting at 22A at coord C, 8
20A. 7009 ADD V0, 09     # Add 9 to V0, = 15
20C. A239 LD I, 239      # Set I to 239
20E. D01F DRW V0, V1, F  # Draw 16 bytes from memory, starting at 239 at coord 15, 8
210. A248 LD I, 248      # Set I to 248
212. 7008 ADD V0, 08     # Add 8 to V0 = 1D
214. D01F DRW V0, V1, F  # Draw 16 bytes from memory, starting at 248 at coord 1D, 8
216. 7004 ADD V0, 04     # Add 4 to V0 = 21
218. A257 LD I, 257      # Set I to 257
21A. D01F DRW V0, V1, F
21C. 7008 ADD V0, 08     # Add 8 to V0 = 29
21E. A266 LD I, 266      # Set I to 266
220. D01F DRW V0, V1, F
222. 7008 ADD V0, 08     # Add 8 to V0 = 31
224. A275 LD I, 275      # Set I to 275
226. D01F DRW V0, V1, F
228. 1228 JMP 228        # End Program