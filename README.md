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

### Machine structure
  * **virtual_machine :** Base virtual machine struct
  * **virtual_machine->car[] :** Program memory
  * **execute:** Executer
  * **debugger:** Debugger

### Fibonacci numbers(small version)

    void another_fib_example(virtual_machine* my_vm){
        my_vm->registers[1] = 6;                        // n + 1 = 6, n = 5
        my_vm->registers[2] = 1;                        // fib(0) = 1
        my_vm->registers[3] = 1;                        // fib(1) = 1
        my_vm->registers[4] = 0;                        // fib(n)
        
        my_vm->car[0x0] = LZ  | 0x5;                    // if z == 1 goto: 5
        my_vm->car[0x1] = RA2 | RD4 | TSF;              // R4 <- R2
        my_vm->car[0x2] = RA3 | RB2 | RD2 | ADD;        // R2 <- R2 + R3
        my_vm->car[0x3] = RA4 | RD3 | TSF;              // R3 <- R4
        my_vm->car[0x4] = RA1 | RD1 | DEC | LAD | 0x0;  // R1 <- R1 - 1
        my_vm->car[0x5] = HLT;                          // Halt the machine
    
        execute(my_vm, 0);                              // execute commands with no output
        printer(my_vm, 4);                              // only print contains which register[4]
    
    }

### Counting the number of 1's (Section 8-4 example)

    void another_one_counter(virtual_machine* my_vm){
        my_vm->registers[1] = 127;                      // R1 <- 127 or 0b1111111
    
        my_vm->car[0x0] = RD3 | TSF | ZERO;             // R3 <- 0
        my_vm->car[0x1] = RA1 | RD1 | TRC;              // RA1 <- RA1 + C
        my_vm->car[0x2] = LZ | 0x6;                     // if Z == 1 goto:6
        my_vm->car[0x3] = RA1 | RD1 | RRC;              // R1 = R1 >> 1
        my_vm->car[0x4] = RA1 | RD1 | TSF | LNC | 0x3;  // if C == 0 goto 3 else R1 <- R1
        my_vm->car[0x5] = RA3 | RD3 | INC | LAD | 0x1;  // R3 <- R3 + 1 and goto 1
        my_vm->car[0x6] = HLT;                          // Halt the program
    
        execute(my_vm, 0);                              // Execute program with no output
        printer(my_vm, 3);                              // Only print R3
    }

