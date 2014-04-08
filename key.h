#ifndef KEY_H
#define KEY_H

#include "fxlib.h"

#define K_0 71
#define K_1 72
#define K_2 62
#define K_3 52
#define K_4 73
#define K_5 63
#define K_6 53
#define K_7 74
#define K_8 64
#define K_9 54
#define K_DP 61
#define K_EXP 51
#define K_PMINUS 41
#define K_PLUS 42
#define K_MINUS 32
#define K_MULT 43
#define K_DIV 33
#define K_FRAC 75
#define K_LPAR 55
#define K_RPAR 45
#define K_COMMA 35
#define K_STORE 25
#define K_LOG 66
#define K_LN 56
#define K_SIN 46
#define K_COS 36
#define K_TAN 26
#define K_SQUARE 67
#define K_POW 57
#define K_EXE 31
#define K_DEL 44
#define K_AC 32
#define K_FD 65
#define K_EXIT 47
#define K_SHIFT 78
#define K_ALPHA 77
#define K_OPTN 68
#define K_VARS 58
#define K_UP 28
#define K_DOWN 37
#define K_LEFT 38
#define K_RIGHT 27
#define K_F1 79
#define K_F2 69
#define K_F3 59
#define K_F4 49
#define K_F5 39
#define K_F6 29
#define K_MENU 48
#ifndef OS2Change
#define OS2Change
#ifndef OS2Change_GetOS2
#define OS2Change_GetOS2

typedef int(*sc_i2cp2sip)(char*, char*, short int*, short int*);
#define GlibGetOSVersionInfo (*(sc_i2cp2sip)sc0015)
int OSVersionAsInt(void);

#define isOS2 (OSVersionAsInt() >= 0x02020000)
#define OS2(x,y) ((OSVersionAsInt() >= 0x02020000)?y:x)

#endif

#ifndef OS2Change_Keyboard
#define OS2Change_Keyboard

void delay(void);

unsigned char CheckKeyRow(unsigned char code);


unsigned char KeyDown(unsigned char keycode);

unsigned char GetKeyMod(unsigned int *key);


#define KeyUp(x) !KeyDown(x)
#define GetKey(x) GetKeyMod(x)
#endif
#endif

#endif