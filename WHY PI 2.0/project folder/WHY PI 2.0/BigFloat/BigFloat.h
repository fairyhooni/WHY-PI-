/*
**
**  WHY PI 2.0
**  BigFloat.h
**  Created by cHoon on 2017. 12. 7..
**  Copyright © 2017년 cHoon. All rights reserved.
*/

#ifndef BigFloat_h
#define BigFloat_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "File_util.h"


#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y)  ((X) > (Y) ? (X) : (Y))

typedef unsigned int UINT32;
typedef unsigned long long UINT64;


/* BigFloat struct
**
**
** fixed-point system
 */
typedef struct _BF{
    UINT32* frac;       //  fixed-point part (integer part is 1 and the rest are all fractional part.)
    UINT32 size;        //  length of array
    UINT32 sign;        //  positive & zero is 0, negative is 1.
} BF;
typedef BF* PBF;


/*
 enum about possible error
 */
enum _exception{
    EXC_NO_ERROR = 0,
    EXC_MEMORY_LACK = 1,
    EXC_SETTING_NUMBER_OVERFLOW = 2,
    EXC_CALC_NUMBER_OVERFLOW = 3,
    EXC_INVALID_VALUE = 4
};
typedef enum _exception EXCEPTION;


/*
 constructor & destructor
 */
PBF BF_create(UINT32 size);
PBF BF_copyCreate(PBF bf);
void BF_delete(PBF bf);


/*
 basic functions for BigFloat
 */
EXCEPTION BF_initialize(PBF bf, double num);
EXCEPTION BF_initializeInt(PBF bf, UINT32 num, int sign);
EXCEPTION BF_copy(PBF dest, PBF src);               //  deep copy
EXCEPTION BF_extendAllocate(PBF bf, UINT32 newSize);            //  extend BigFloat's size

/*
 BigFloat output functions
 */
void BF_printHex(FILE* fp, PBF bf);                     //  print BigFloat in hex
void BF_printDec(FILE* fp, PBF bf, UINT64 precision);   //  print BigFloat in dec


/*
 utility fuctions
 */
int BF_isEqual(PBF src1, PBF src2);
int BF_isZero(PBF bf);
int BF_isClose(PBF src1, PBF src2);

long long BF_standardize(PBF dest, PBF src);        //  standardize src in range of 1 <= src < 2 using shift operation


/*
 bit operator functions
 */
inline void BF_inline_calcTwosComplement(UINT32* array, UINT32 size);       //  take 2's complement

inline void BF_inline_sll(UINT32* bigFloat, UINT32 size, UINT64 num);       //  shift left logical (bigFloat << num)
inline void BF_inline_srl(UINT32* bigFloat, UINT32 size, UINT64 num);       //  shift right logical (bigFloat >> num)


/*
 basic operator functions
 */
EXCEPTION BF_add(PBF dest, PBF src);        //  dest += src
EXCEPTION BF_add_controller(PBF augend, PBF addend);
inline int BF_inline_add(UINT32* augend, UINT32* addend, UINT32 size);              //  add each digit


EXCEPTION BF_sub(PBF dest, PBF src);        //  dest -= src
EXCEPTION BF_sub_controller(PBF minuend, PBF subtrahend);
inline int BF_inline_sub(UINT32* minuend, UINT32* subtrahend, UINT32 size);         //  sub each digit


EXCEPTION BF_mul(PBF dest, PBF src1, PBF src2);        //   dest = src1 * src2
EXCEPTION BF_mul_controller(PBF dest, PBF multiplicand, PBF multiplier);
EXCEPTION BF_mulInteger(PBF dest, PBF src1, int src2);          //  multiply by integer
EXCEPTION BF_mulInteger_controller(PBF dest, PBF multiplicand, int multiplier);
inline int BF_inline_add_mulValue64(UINT32* dest, UINT64 mulValue, UINT32 size, UINT32 pos);      //  add multiplication value(64bit) to pos_th digit
inline int BF_inline_add_mulValue32(UINT32* dest, UINT32 mulValue, UINT32 size, UINT32 pos);      //  add multiplication value(32bit) to pos_th digit


EXCEPTION BF_div(PBF dest, PBF dividend, PBF divisor);          //  dest = dividend / divisor
EXCEPTION BF_inv(PBF dest, PBF src);                            //  dest = 1/src
void BF_calcInverse(PBF dest, PBF src);


EXCEPTION BF_sqrt(PBF dest, PBF src);              //   dest = square root of src
void BF_calcSqrt(PBF dest, PBF src);


#endif /* BigFloat_h */

