#ifndef PROCESS_H
#define PROCESS_H

#include "vm.h"

void carry_control(unsigned int, short, _flags*);
void overflow_control(short, short, _flags*);
void zero_sign_control(short, short, _flags*);
void process(virtual_machine*);

#endif