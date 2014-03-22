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
            zero_sign_control(vm->registers[vm->current_word->D], vm->registers[vm->current_word->D], vm->flags); 
            break;

        case 0x1:
            /* SHL */
            current = vm->registers[vm->current_word->D];
            temp = current << 1; // shift left with input 0
            zero_sign_control(current, temp, vm->flags);
            vm->registers[vm->current_word->D] = temp;
            break;

        case 0x2:
            /* SHR */
            current = vm->registers[vm->current_word->D];
            temp = current >> 1; // shift left with input 0
            zero_sign_control(current, temp, vm->flags);
            vm->registers[vm->current_word->D] = temp;
            break;

        case 0x3:
            /* ZERO */
            vm->registers[vm->current_word->D] = 0; // all zeros in output of shifte
            vm->flags->Z = 1;
            break;

        case 0x4:
            /* RLC */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (current << 1) + ((unsigned char)(vm->registers[vm->current_word->D] & 0x8000));
            temp += vm->flags->C;
            zero_sign_control(current, temp, vm->flags);
            vm->registers[vm->current_word->D] = temp;
            break;

        case 0x5:
            /* ROL */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (current << 1) + ((unsigned char)(vm->registers[vm->current_word->D] & 0x8000));
            zero_sign_control(current, temp,  vm->flags);
            vm->registers[vm->current_word->D] = current; // D = current
            break;

        case 0x6:
            /* ROR */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (current >> 1) + ((unsigned char)(vm->registers[vm->current_word->D] & 0x1) << 15);
            zero_sign_control(current, temp,  vm->flags);
            vm->registers[vm->current_word->D] = current; // D = current
            break;

        case 0x7:
            /* RRC */
            current = vm->registers[vm->current_word->D]; // current = D
            temp = (current >> 1) + ((unsigned char)(current & 0x1) << 15);
            zero_sign_control(current, temp, vm->flags);
            vm->registers[vm->current_word->D] = current + vm->flags->C; // D = current + carry
            break;

        default:
            /* NOSHIFT */
            break;
    }
}
