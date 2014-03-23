#ifndef VM_H
#define VM_H

/* Control word struct */
typedef struct{
    unsigned short A:3;
    unsigned short B:3;
    unsigned short D:3;
    unsigned short F:4;
    unsigned short H:3;
}_control_word;

/* Flags struct */
typedef struct{
    unsigned char Z:1;
    unsigned char S:1;
    unsigned char C:1;
    unsigned char V:1;
    unsigned char R:1;
}_flags;

/* Select */
typedef struct{
    unsigned short MUX1:1;
    unsigned short MUX2:3;
    unsigned short ADDRESS:8;
}_select;

/* Virtual machine base struct */
typedef struct{
    _control_word* current_word;
    _flags* flags;
    _select* select;
    short* registers;
    unsigned int reg_num;
    unsigned int* car;
    unsigned int car_counter;
}virtual_machine;

/* Registers 0-7 */
typedef enum { R0 = 0b000 << 25, R1 = 0b001 << 25, R2 = 0b010 << 25, R3 = 0b011 << 25, 
	R4 = 0b100 << 25, R5 = 0b101 << 25, R6 = 0b110 << 25, R7 = 0b111 << 25} Registers;

/* A register family */
typedef enum { RA0 = 0b000 << 25, RA1 = 0b001 << 25, RA2 = 0b010 << 25, RA3 = 0b011 << 25, 
	RA4 = 0b100 << 25, RA5 = 0b101 << 25, RA6 = 0b110 << 25, RA7 = 0b111 << 25} RegistersA;

/* B register family */
typedef enum { RB0 = 0b000 << 22, RB1 = 0b001 << 22, RB2 = 0b010 << 22, RB3 = 0b011 << 22, 
	RB4 = 0b100 << 22, RB5 = 0b101 << 22, RB6 = 0b110 << 22, RB7 = 0b111 << 22} RegistersB;

/* D register family */
typedef enum { RD0 = 0b000 << 19, RD1 = 0b001 << 19, RD2 = 0b010 << 19, RD3 = 0b011 << 19, 
	RD4 = 0b100 << 19, RD5 = 0b101 << 19, RD6 = 0b110 << 19, RD7 = 0b111 << 19} RegistersD;

/* ALU operations */
typedef enum { TSF = 0b0000 << 15, INC = 0b0001 << 15, ADD = 0b0010 << 15, SUB = 0b0101 << 15,
    DEC = 0b0110 << 15, TRC = 0b0111 << 15, AND = 0b1000 << 15, OR = 0b1010 << 15, 
    XOR = 0b1100 << 15, COM = 0b1110 << 15, HLT = 0b1111 << 15} Operations;

/* Shifting operations  */
typedef enum { NSH = 0b000 << 12, SHL = 0b001 << 12, SHR = 0b010 << 12, ZERO = 0b011 << 12,
    RLC = 0b100 << 12, ROL = 0b101 << 12, ROR = 0b110 << 12, RRC = 0b111 << 12} Shifters;

/* Mux1 select address */
typedef enum { INT = 0 << 11, EXT = 1 << 11} Mux1;

/* Mux2 select */
typedef enum { NEXT = 0b000 << 8, LAD = 0b001 << 8, LC = 0b010 << 8, LNC = 0b011 << 8,
    LZ = 0b100 << 8, LNZ = 0b101 << 8, LS = 0b110 << 8, LV = 0b111 << 8} Mux2;

virtual_machine* machine_init(unsigned int, unsigned int);
void decode(virtual_machine*, unsigned int);
void debugger(virtual_machine*);
void printer(virtual_machine*, unsigned int);
void cleaner(virtual_machine*);
#endif
