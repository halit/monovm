// =====================================================================================
//
//       Filename:  vm.c
//
//    Description:  Virtual machine for Morris Mono Book
//
//        Version:  1.0
//        Created:  03/22/2014 12:03:01 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//   Organization:  
//
// =====================================================================================
#include "vm.h"
#include <stdlib.h>
#include <stdio.h>

static _flags* flag_init(){
    _flags* flags_i = (_flags*)malloc(sizeof(_flags));
    flags_i->Z = 0x0;
    flags_i->S = 0x0;
    flags_i->C = 0x0;
    flags_i->V = 0x0;
    flags_i->R = 0x1;

    return flags_i;
}

virtual_machine* machine_init(unsigned int reg_number, unsigned int program_memory){
    /* Create new virtual machine */
    virtual_machine* new_machine = (virtual_machine*)malloc(sizeof(virtual_machine));
    
    /* Create flags */
    new_machine->flags = flag_init();
    
    /* Create control word and select word */
    new_machine->current_word = (_control_word*)malloc(sizeof(_control_word));
    new_machine->select = (_select*)malloc(sizeof(_select));
    
    /* Create registers */
    new_machine->registers = (short*)malloc(sizeof(short)*reg_number);
    new_machine->reg_num = reg_number;
    
    /* Create car and counter */
    new_machine->car = (unsigned int*)malloc(sizeof(int)*program_memory);
    new_machine->car_counter = 0;

    return new_machine;
};

void decode(virtual_machine* vm, unsigned int cw){
    vm->select->MUX1 = (cw & 0x800) >> 11; // 0b0000000000000000100000000000 
    vm->select->MUX2 = (cw & 0x700) >> 8;  // 0b0000000000000000011100000000
    vm->select->ADDRESS = (cw & 0xFF);     // 0b0000000000000000000011111111
    cw >>= 12;
    vm->current_word->A = (cw & 0xE000) >> 13; // 0b1110000000000000
    vm->current_word->B = (cw & 0x1C00) >> 10; // 0b0001110000000000
    vm->current_word->D = (cw & 0x380) >> 7;   // 0b0000001110000000
    vm->current_word->F = (cw & 0x78) >> 3;    // 0b0000000001111000
    vm->current_word->H = (cw & 0x7);          // 0b0000000000000111
}

void execute(virtual_machine* vm, unsigned char flag){
    while(vm->flags->R){
        decode(vm, vm->car[vm->car_counter]);
        process(vm);
        shifter(vm);
        selector(vm);
        if(flag) debugger(vm);
    }
    cleaner(vm);
}

void printer(virtual_machine* vm, unsigned int i){
    printf("# Register[%d]: %d\n", i, vm->registers[i]);
}

void cleaner(virtual_machine* vm){
    free(vm->current_word);
    free(vm->flags);
    free(vm->select);
    free(vm->registers);
    free(vm->car);
    free(vm);
}

void debugger(virtual_machine* vm){
    int i;
    for(i=0;i<vm->reg_num;i++){
        printf("# Register[%d]: %d\n", i, vm->registers[i]);
    }
    printf("# Flag[C]: %d\n", vm->flags->C);
    printf("# Flag[V]: %d\n", vm->flags->V);
    printf("# Flag[S]: %d\n", vm->flags->S);
    printf("# Flag[Z]: %d\n", vm->flags->Z);
    printf("# Flag[R]: %d\n", vm->flags->R);
    
    printf("# Car counter: %d\n", vm->car_counter);
    printf("##########\n");
}

Registers make_register(Registers R, unsigned char c){
    if(c) return R >> 3; // if c == 1 return R as B register
    else return R >> 6; // if c == 0 return R as D register
}
