monovm
======

Virtual machine for Morris Mano's book.

### Compile & Run & Clean

    make clean
    make
    ./main

### Features

  * **8 registers:** R0, R1, R2, R3, R4, R5, R6, R7
  * **ALU operations:** TSF, INC, ADD, SUB, DEC, TRC, AND, OR, XOR, COM, HLT
  * **Shifting operations:** NSH, SHL, SHR, ZERO, RLC, ROL, ROR, RRC
  * **Address selectors:** INT, EXT
  * **Jumpers:** NEXT, LAD, LC, LNC, LZ, LNZ, LS, LV
