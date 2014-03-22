// =====================================================================================
//
//       Filename:  shifter.c
//
//    Description:  
//
//        Version:  1.0
//        Created:  03/22/2014 12:10:17 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//   Organization:  
//
// =====================================================================================
#include "shifter.h"

void shifter(virtual_machine* vm){
    unsigned char current, temp;
    switch(vm->current_word->H){
        case 0x0:
            /* NSH */
            break;

        case 0x1:
            /* SHL */
            vm->registers[vm->current_word->D] <<= 1; // shift left with input 0
            break;

        case 0x2:
            /* SHR */
            vm->registers[vm->current_word->D] >> 1; // shift right with input 0
            break;

        case 0x3:
            /* ZERO */
            vm->registers[vm->current_word->D] = 0; // all zeros in output of shifter
            break;

        case 0x4:
            /* RLC */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (unsigned char)(vm->registers[vm->current_word->D] & 0x8000); // temp = msb bit
            current = (current << 1) + temp; // rotate left
            vm->registers[vm->current_word->D] = current + vm->flags->C; // D = current + carry
            break;

        case 0x5:
            /* ROL */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (unsigned char)(vm->registers[vm->current_word->D] & 0x8000); // temp = msb bit
            current = (current << 1) + temp; // rotate left
            vm->registers[vm->current_word->D] = current; // D = current
            break;

        case 0x6:
            /* ROR */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (unsigned char)(vm->registers[vm->current_word->D] & 0x1) << 15; // temp = lsb bit
            current = (current >> 1) + temp; // rotate right
            vm->registers[vm->current_word->D] = current; // D = current
            break;

        case 0x7:
            /* RRC */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (unsigned char)(vm->registers[vm->current_word->D] & 0x1) << 15; // temp = lsb bit
            current = (current >> 1) + temp; // rotate right
            vm->registers[vm->current_word->D] = current + vm->flags->C; // D = current + carry
            break;

        default:
            /* NOSHIFT */
            break;
    }
}