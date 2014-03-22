// =====================================================================================
//
//       Filename:  selector.c
//
//    Description:  
//
//        Version:  1.0
//        Created:  03/22/2014 12:10:28 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//   Organization:  
//
// =====================================================================================

#include "selector.h"

void selector(virtual_machine* vm){
    switch(vm->select->MUX2){
        case 0x0:
            /* NEXT */
            vm->car_counter++;
            break;

        case 0x1:
            /* LAD */
            vm->car_counter = vm->select->ADDRESS;
            break;

        case 0x2:
            /* LC */
            if(vm->flags->C) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter++;
            break;

        case 0x3:
            /* LNC */
            if(!vm->flags->C) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter++;
            break;

        case 0x4:
            /* LZ */
            if(vm->flags->Z) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter++;
            break;

        case 0x5:
            /* LNZ */
            if(!vm->flags->Z) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter++;
            break;

        case 0x6:
            /* LS */
            if(vm->flags->S) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter++;
            break;

        case 0x7:
            /* LC */
            if(vm->flags->V) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter++;
            break;

        default:
            break;
    }
}
