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
        case 0:
            /* NEXT */
            vm->car_counter += 1;
            break;

        case 1:
            /* LAD */
            vm->car_counter = vm->select->ADDRESS;
            break;

        case 2:
            /* LC */
            if(vm->flags->C) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter += 1;
            break;

        case 3:
            /* LNC */
            if(!vm->flags->C) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter += 1;
            break;

        case 4:
            /* LZ */
            if(vm->flags->Z) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter += 1;
            break;

        case 5:
            /* LNZ */
            if(!vm->flags->Z) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter += 1;
            break;

        case 6:
            /* LS */
            if(vm->flags->S) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter += 1;
            break;

        case 7:
            /* LC */
            if(vm->flags->C) vm->car_counter = vm->select->ADDRESS;
            else vm->car_counter += 1;
            break;

        default:
            vm->car_counter += 1;
            break;
    }
}
