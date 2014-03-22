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

int main(){
	virtual_machine* my_vm = machine_init(8, 32);

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