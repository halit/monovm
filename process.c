// =====================================================================================
//
//       Filename:  process.c
//
//    Description:  
//
//        Version:  1.0
//        Created:  03/22/2014 12:07:47 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//   Organization:  
//
// =====================================================================================

#include "process.h"

void carry_control(unsigned int first_r, short last_r, _flags* current){
    if(first_r != last_r) current->C = 1;
    else current->C = 0;
}

void overflow_control(short first_r, short last_r, _flags* current){
    if((first_r >> 15) != (last_r >> 15)) current->V = 1; // V = 1
    else current->V = 0;
}

void zero_sign_control(short first_r, short last_r, _flags* current){
    if(first_r >> 15) current->S = 1; // S = 1
    else current->S = 0;

    if(!first_r) current->Z = 1; // Z = 1
    else current->Z = 0;
}

void process(virtual_machine* vm){
    short first_result;
    short last_result;
    unsigned int tmp;
    switch(vm->current_word->F){
        case 0:
            /* TSF */
            vm->registers[vm->current_word->D] = vm->registers[vm->current_word->A]; // transfer A to D
            break;

        case 1:
            /* INC */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            last_result = first_result++; // last_result = first_result + 1
            zero_sign_control(first_result, last_result, vm->flags); // update the flag status
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 2:
            /* ADD */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            tmp = first_result + vm->registers[vm->current_word->B]; // tmp = first_result + B
            last_result = tmp;

            zero_sign_control(first_result, last_result, vm->flags); // update the Z, S flags
            carry_control(tmp, last_result, vm->flags); // Update the C flag
            overflow_control(first_result, last_result, vm->flags); // Update the V flag
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 5:
            /* SUB */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            tmp = first_result - vm->registers[vm->current_word->B]; // tmp = first_result - B
            last_result = tmp;

            zero_sign_control(first_result, last_result, vm->flags); // update the Z, S flags
            carry_control(tmp, last_result, vm->flags); // Update the C flag
            overflow_control(first_result, last_result, vm->flags); // Update the V flag
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 6:
            /* DEC */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            last_result = first_result--;
            zero_sign_control(last_result, last_result, vm->flags); // Update the Z, S flags
            vm->registers[vm->current_word->D] = last_result; // D = result 
            break;

        case 7:
            /* TRC */
            vm->registers[vm->current_word->D] = vm->registers[vm->current_word->A]; // transfer A to D
            zero_sign_control(vm->registers[vm->current_word->A], vm->registers[vm->current_word->A], vm->flags); // Flags
            vm->flags->C = 0; // clear carry flag
            break;

        case 8:
            /* AND */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            last_result = first_result & vm->registers[vm->current_word->B]; // last_result = first_result & B
            zero_sign_control(first_result, last_result, vm->flags); // update the flag status
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 10:
            /* OR */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            last_result = first_result | vm->registers[vm->current_word->B]; // last_result = first_result | B
            zero_sign_control(first_result, last_result, vm->flags); // update the flag status
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 12:
            /* XOR */
            first_result = vm->registers[vm->current_word->A]; // first_result = A
            last_result = first_result ^ vm->registers[vm->current_word->B]; // last_result = first_result ^ B
            zero_sign_control(first_result, last_result, vm->flags); // update the flag status
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 14:
            /* COM */
            first_result = vm->registers[vm->current_word->A];
            last_result = ~vm->registers[vm->current_word->A]; // last_result = ~A
            zero_sign_control(first_result, last_result, vm->flags); // update the flag status
            vm->registers[vm->current_word->D] = last_result; // D = result
            break;

        case 15:
            /* HLT */
            vm->flags->R = 0x0;
            break;

        default:
            /* NOP */
            break;
    }
}