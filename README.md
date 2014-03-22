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

### Counting the number of 1's (Section 8-4 Example)

    void third_example(virtual_machine* my_vm){
        my_vm->registers[0b001] = 0b00011110;
        Registers A, D;
    
        D = make_register(R3, 0);
        my_vm->car[0x0] = D | TSF | ZERO | NEXT;
    
        A = R1;
        D = make_register(R1, 0);
        my_vm->car[0x1] = A | D | TRC | NSH | NEXT;
    
        my_vm->car[0x2] = TSF | NSH | EXT | LZ | 0x6;
        
        A = R1;
        D = make_register(R1, 0);
        my_vm->car[0x3] = A | D | TSF | RRC | NEXT;
        my_vm->car[0x4] = A | D | TSF | NSH | LNC | 0x3;
        
        A = R3;
        D = make_register(R3, 0);
        my_vm->car[0x5] = A | D | INC | NSH | LAD | 0x1;
    
        my_vm->car[0x6] = A | HLT;
    
        execute(my_vm);
    }
