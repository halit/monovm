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
        my_vm->registers[1] = 6; // n + 1 = 6, n = 5
        my_vm->registers[2] = 1; // fib(0) = 1
        my_vm->registers[3] = 1; // fib(1) = 1
        my_vm->registers[4] = 0; // fib(n)
        
        my_vm->car[0x0] = LZ  | 0x5;                    // if z == 1 goto: 5
        my_vm->car[0x1] = RA2 | RD4 | TSF;              // R4 <- R2
        my_vm->car[0x2] = RA3 | RB2 | RD2 | ADD;        // R2 <- R2 + R3
        my_vm->car[0x3] = RA4 | RD3 | TSF;              // R3 <- R4
        my_vm->car[0x4] = RA1 | RD1 | DEC | LAD | 0x0;  // R1 <- R1 - 1
        my_vm->car[0x5] = HLT;                          // Halt the machine
    
        execute(my_vm, 0);                              // execute commands with no output
        printer(my_vm, 4);                              // only print contains which register[4]
    
    }
    
### Counting the number of 1's (Section 8-4 Example)

    void third_example(virtual_machine* my_vm){
        my_vm->registers[0b001] = 0b00011110; // R1 = 0b00011110
        Registers A, D; // Create the A and D register
    
        D = make_register(R3, 0); // Make the R3 as D
        my_vm->car[0x0] = D | TSF | ZERO | NEXT; // Write program to 0x0.
    
        A = R1; // Make R1 as A
        D = make_register(R1, 0); // Make the R1 as D
        my_vm->car[0x1] = A | D | TRC | NSH | NEXT; // Write program to 0x1
    
        my_vm->car[0x2] = TSF | NSH | EXT | LZ | 0x6; // Write program to 0x2
        
        A = R1; // Make R1 as A
        D = make_register(R1, 0); // Make R1 as D
        my_vm->car[0x3] = A | D | TSF | RRC | NEXT; // Write program to 0x3
        my_vm->car[0x4] = A | D | TSF | NSH | LNC | 0x3; // Write program to 0x4
        
        A = R3; // Make R3 as A
        D = make_register(R3, 0); // Make R3 as A
        my_vm->car[0x5] = A | D | INC | NSH | LAD | 0x1; // Write program to 0x5
    
        my_vm->car[0x6] = A | HLT; // Halt the machine
    
        execute(my_vm, 1); // Run the machine with output
    }
    
### Fibonacci numbers(old version)
    void fib_example(virtual_machine* my_vm){
        my_vm->registers[1] = 6; // n + 1 = 6, n = 5
        my_vm->registers[2] = 1; // fib(0) = 1
        my_vm->registers[3] = 1; // fib(1) = 1
        my_vm->registers[4] = 0; // fib(n)
    
        Registers A, B, D;
    
        my_vm->car[0x0] = LZ | 0x5; // if z == 1 goto: 5
        A = R2;
        D = make_register(R4, 0);
        my_vm->car[0x1] = A | D | TSF; // R4 <- R2
    
        A = R3;
        B = make_register(R2, 1);
        D = make_register(R2, 0);
        my_vm->car[0x2] = A | B | D | ADD; // R2 <- R2 + R3
    
        A = R4;
        D = make_register(R3, 0);
        my_vm->car[0x3] = A | D | TSF; // R3 <- R4
    
        A = R1;
        D = make_register(R1, 0);
        my_vm->car[0x4] = A | D | DEC | LAD | 0x0; // R1 <- R1 - 1
    
        my_vm->car[0x5] = HLT;
    
        execute(my_vm, 1);
    }
