// =====================================================================================
//
//       Filename:  main.c
//
//    Description:  
//
//        Version:  1.0
//        Created:  03/22/2014 12:21:24 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//   Organization:  
//
// =====================================================================================

#include "vm.h"

void first_example(virtual_machine* my_vm){

	my_vm->registers[0b001] = 12;
	my_vm->registers[0b010] = 5;

	Registers A, B, D;
	A = R1;
	B = make_register(R2, 1);
	D = make_register(R3, 0);
	
    my_vm->car[0x0] = A | B | D | ADD | NSH | INT | NEXT;
	my_vm->car[0x1] = A | B | D | HLT | NSH | INT | NEXT;

	execute(my_vm);
}

void second_example(virtual_machine* my_vm){

    my_vm->registers[0b001] = 6;
    Registers A, D;

    A = R1;
    D = make_register(R1, 0);
    my_vm->car[0x0] = A | D | DEC | NEXT;
    my_vm->car[0x1] = A | D | TSF | LZ | 0x3;
    my_vm->car[0x2] = TSF | LAD | 0x0;
    my_vm->car[0x3] = A | HLT;

    execute(my_vm);
}

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

void fib_example(virtual_machine* my_vm){
    my_vm->registers[1] = 6; // n + 1 = 6, n = 5
    my_vm->registers[2] = 1; // fib(0) = 1
    my_vm->registers[3] = 1; // fib(1) = 1
    my_vm->registers[4] = 0; // fib(n)

    Registers A, B, D;

    my_vm->car[0x0] = LZ | 0x5; // if z == 1 goto: 6
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

    execute(my_vm);
}
int main(){
    virtual_machine* my_vm = machine_init(8, 32);
    fib_example(my_vm);

}
