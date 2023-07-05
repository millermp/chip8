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

Translation of IBM Logo.ch8:
 1. 00E0 CLS            # Clear Screen
 2. A22A LD I, 22A      # Set I to 22A
 3. 600C LD V0, 0C      # Set V0 to 0C
 4. 6108 LD V1, 08      # Set V1 to 08
 5. D01F DRW V0, V1, F  # Draw 16 bytes from memory, starting at 22A at coord C, 8
 6. 7009 ADD V0, 09     # Add 9 to V0, = 15
 7. A239 LD I, 239      # Set I to 239
 8. D01F DRW V0, V1, F  # Draw 16 bytes from memory, starting at 239 at coord 15, 8
 9. A248 LD I, 248      # Set I to 248
10. 7008 ADD V0, 08     # Add 8 to V0 = 1D
11. D01F DRW V0, V1, F  # Draw 16 bytes from memory, starting at 248 at coord 1D, 8
12. 7004 ADD V0, 04
13. A257 LD I, 257
14. D01F DRW V0, V1, F
15. 7008 ADD V0, 08
16. A266 LD I, 266
17. D01F DRW V0, V1, F
18. 7008 ADD V0, 08
19. A275 LD I, 275
20. D01F DRW V0, V1, F
21. 1228 JMP 228        # End Program