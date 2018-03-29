/*
 **
 **  WHY PI 2.0
 **  BigFloat.h
 **  Created by cHoon on 2017. 12. 7..
 **  Copyright © 2017년 cHoon. All rights reserved.
 */


#include "BigFloat.h"



PBF BF_create(UINT32 size){
    PBF newPBF = (PBF)malloc(sizeof(BF));
    if(newPBF == NULL){
        printf("ERROR : Memory lack.");
        exit(1);
    }
    
    newPBF->size = MAX(size, 4);            //  minimum size is 4
    newPBF->sign = 0;
    newPBF->frac = (UINT32*)calloc(newPBF->size, sizeof(UINT32));       //  allocate fixed-point part
    if(newPBF->frac == NULL){
        printf("ERROR : Memory lack.");
        exit(1);
    }
    
    return newPBF;
}

PBF BF_copyCreate(PBF bf){
    PBF newPBF = (PBF)malloc(sizeof(BF));
    if(newPBF == NULL){
        printf("ERROR : Memory lack.");
        exit(1);
    }
    
    newPBF->size = bf->size;
    newPBF->sign = bf->sign;
    newPBF->frac = (UINT32*)calloc(newPBF->size, sizeof(UINT32));
    if(newPBF->frac == NULL){
        printf("ERROR : Memory lack.");
        exit(1);
    }
    memcpy(newPBF->frac, bf->frac, sizeof(UINT32) * bf->size);
    
    
    return newPBF;
}


void BF_delete(PBF bf){
    free(bf->frac);
    free(bf);
}


EXCEPTION BF_initialize(PBF bf, double num){
    if(num >= 4294967296. | num <= -4294967296.)return EXC_SETTING_NUMBER_OVERFLOW;
    
    if(num >= 0)
        bf->sign = 0;
    else{
        bf->sign = 1;
        num = -num;
    }
    
    /* base 10 to base 2^32 */
    bf->frac[0] = (UINT32)num;         //  Integer part
    num -= bf->frac[0];
    num *= 4294967296.;

    bf->frac[1] = (UINT32)num;
    num -= bf->frac[1];
    num *= 4294967296.;
    
    bf->frac[2] = (UINT32)num;
    
    memset(bf->frac + 3, 0, sizeof(UINT32) * (bf->size - 3));
    
    return EXC_NO_ERROR;
}

EXCEPTION BF_initializeInt(PBF bf, UINT32 num, int sign){
    bf->sign = sign;
    bf->frac[0] = num;
    
    memset(bf->frac + 1, 0, sizeof(UINT32) * (bf->size - 1));
    
    return EXC_NO_ERROR;
}

EXCEPTION BF_copy(PBF dest, PBF src){
    //  resize frac array
    if(src->size != dest->size){
        dest->frac = (UINT32*)realloc(dest->frac, sizeof(UINT32) * src->size);
        if(dest->frac == NULL)
            return EXC_MEMORY_LACK;
    }
    
    //  copy else things...
    
    memcpy(dest->frac, src->frac, sizeof(UINT32) * (src->size));
    
    dest->size = src->size;
    
    dest->sign = src->sign;
    
    return EXC_NO_ERROR;
}

EXCEPTION BF_extendAllocate(PBF bf, UINT32 newSize){
    if(newSize <= bf->size)
        return EXC_INVALID_VALUE;
    
    bf->frac = (UINT32*)realloc(bf->frac, sizeof(UINT32) * newSize);
    if(bf->frac == NULL)
        return EXC_MEMORY_LACK;
    
    memset(bf->frac + bf->size, 0, sizeof(UINT32) * (newSize - bf->size));
    
    bf->size = newSize;
    
    return EXC_NO_ERROR;
}


void BF_printHex(FILE* fp, PBF bf){
    if(bf->sign == 1)
        fprintf(fp,"-");
    fprintf(fp, "%x.\n", bf->frac[0]);
    
    //  print fractional part
    for(UINT32 i = 1; i<bf->size; i++){
        if(i%8 == 1)
            fprintf(fp, "\n");
        
        fprintf(fp, "%08x ", bf->frac[i]);
    }
    
    fprintf(fp, "\n");
}


void BF_printDec(FILE* fp, PBF bf, UINT64 precision){
    /*
     first, write to string buffer
     */
    
    char *buffer, *currStrPtr;
    
    PBF tempBF = BF_create(bf->size);
    BF_copy(tempBF, bf);
    
    if(precision == 0 || precision > (tempBF->size - 1) * 9)         //   in this case, print all fractional part
        precision = (tempBF->size - 1) * 9;
    
    buffer = (char*)calloc(precision + 18, sizeof(char));
    currStrPtr = buffer;
    
    if(tempBF->sign == 1)                   //  negative number
        currStrPtr += sprintf(currStrPtr,"-");
    currStrPtr += sprintf(currStrPtr, "%u.", tempBF->frac[0]);
    tempBF->frac[0] = 0;
    
    for(;precision >= 9;precision-=9){              //  base2^32 to base10
        BF_mulInteger(tempBF, tempBF, 1000000000);
        
        currStrPtr += sprintf(currStrPtr, "%09u", tempBF->frac[0]);
        tempBF->frac[0] = 0;
    }
    
    
    BF_mulInteger(tempBF, tempBF, (int)pow(10.0, precision));
    switch (precision) {
        case 1: sprintf(currStrPtr, "%01u", tempBF->frac[0]);
            break;
            
        case 2: sprintf(currStrPtr, "%02u", tempBF->frac[0]);
            break;
            
        case 3: sprintf(currStrPtr, "%03u", tempBF->frac[0]);
            break;
            
        case 4: sprintf(currStrPtr, "%04u", tempBF->frac[0]);
            break;
            
        case 5: sprintf(currStrPtr, "%05u", tempBF->frac[0]);
            break;
            
        case 6: sprintf(currStrPtr, "%06u", tempBF->frac[0]);
            break;
            
        case 7: sprintf(currStrPtr, "%07u", tempBF->frac[0]);
            break;
            
        case 8: sprintf(currStrPtr, "%08u", tempBF->frac[0]);
            break;
    }
    

    /*
     next, write to file according to the form
     */
    
    currStrPtr = buffer;
    
    writeNumStrToFile(fp, currStrPtr);
    
    BF_delete(tempBF);
    free(buffer);
}



int BF_isEqual(PBF src1, PBF src2){
    if(src1->sign != src2->sign)
        return 0;
    
    if(src1->size != src2->size)
        return 0;
    
    for(UINT32 i = 0;i<src1->size;i++){
        if(src1->frac[i] != src2->frac[i])
            return 0;
    }
    
    return 1;
}

int BF_isZero(PBF bf){
    for(UINT32 i = 0;i<bf->size;i++){
        if(bf->frac[i] != 0)
            return 0;
    }
    
    return 1;
}

int BF_isClose(PBF src1, PBF src2){
    int result = 0;
    
    PBF tolerance = BF_create(MAX(src1->size, src2->size));
    tolerance->frac[tolerance->size - 2] = 0x10000000;
    
    PBF diff = BF_create(MAX(src1->size, src2->size));
    diff->sign = src1->sign;
    memcpy(diff->frac, src1->frac, sizeof(UINT32) * src1->size);
    
    BF_sub(diff, src2);
    diff->sign = 0;                     //  diff = abs(src1 - src2)
    
    BF_sub(diff, tolerance);
    
    if(diff->sign == 1)                 //  difference < tolerance (is close)
        result = 1;
    else
        result = 0;
    
    BF_delete(tolerance);
    BF_delete(diff);
    
    return result;
}

long long BF_standardize(PBF dest, PBF src){
    UINT32 block = 0;                   //  num of shifting block of array
    int offset = 0;                     //  num of shifting digit in block
    long long shiftingNum = 0;          //  total num of shifting digit
    memcpy(dest->frac, src->frac, src->size * sizeof(UINT32));

    for(UINT32 i = 0;i < src->size;i++){
        if(src->frac[i] > 0){
            block = i;
            break;
        }
    }
    offset = (int)log2(src->frac[block]);
    
    shiftingNum = (long long)block*32 - offset;
    
    if(shiftingNum > 0)
        BF_inline_sll(dest->frac, dest->size, shiftingNum);
    else if(shiftingNum < 0)
        BF_inline_srl(dest->frac, dest->size, -shiftingNum);
    
    return shiftingNum;
}


void BF_inline_calcTwosComplement(UINT32* array, UINT32 size){
    UINT32 i = 0;

    //  find out LSB
    for(i=size - 1;i != (UINT32)-1;i--){
        if(array[i] != 0)
            break;
    }
    
    //  take 1's complement (bit flip)
    for(UINT32 j = i;j != (UINT32)-1;j--){
        array[j] = ~array[j];
    }
    
    //  plus 1 at LSB
    array[i]++;
}


void BF_inline_sll(UINT32* bigFloat, UINT32 size, UINT64 num){
    UINT32 block = (UINT32) (num/32);
    UINT32 offset = num%32;
    
    UINT32* buffer = (UINT32*)calloc(size, sizeof(UINT32));
    UINT32 overflowedNum = 0;
    UINT32 extractor = 0;
    
    
    //  calc extractor of overflowed bits
    for(int i = 0;i<offset;i++)
        extractor += 0x80000000>>i;
    
    for(UINT32 i = size - 1;i != (UINT32)-1 + block;i--){
        buffer[i - block] = bigFloat[i] << offset;                  //  shift
        buffer[i - block] |= (overflowedNum >> (32 - offset));      //  add previous overflowed num to current block
        
        overflowedNum = bigFloat[i] & extractor;                    //  extract overflowed number at this block
    }
    
    memcpy(bigFloat, buffer, size * sizeof(UINT32));
    free(buffer);
}

void BF_inline_srl(UINT32* bigFloat, UINT32 size, UINT64 num){
    UINT32 block = (UINT32) (num/32);
    UINT32 offset = num%32;
    
    UINT32* buffer = (UINT32*)calloc(size, sizeof(UINT32));
    UINT32 underflowedNum = 0;
    UINT32 extractor = 0;
    
    //  calc extractor of underflowed bit
    for(int i = 0;i<offset;i++)
        extractor += 1<<i;
    
    for(UINT32 i = 0;i<size - block;i++){
        buffer[i + block] = bigFloat[i] >> offset;                       //  shift
        buffer[i + block] |= (underflowedNum << (32 - offset));          //  add previous underflowed num to current block
        
        underflowedNum = bigFloat[i] & extractor;                        //  extract underflowed number at this block
    }
    
    memcpy(bigFloat, buffer, size * sizeof(UINT32));
    free(buffer);
}




EXCEPTION BF_add(PBF dest, PBF src){                //  dest += src
    int result = EXC_NO_ERROR;
    
    if(dest->sign == src->sign)                     //  + (+) + , - (+) - are real add
        result = BF_add_controller(dest, src);
    else                                            //  + (+) - , - (+) + are real sub
        result = BF_sub_controller(dest, src);
    
    return result;
}

EXCEPTION BF_add_controller(PBF augend, PBF addend){
    EXCEPTION result = EXC_NO_ERROR;
    
    if(BF_inline_add(augend->frac, addend->frac, MIN(augend->size, addend->size)) != 0)         // handle carry in MSB (= handle overflow)
        result = EXC_CALC_NUMBER_OVERFLOW;
    
    return result;
}

int BF_inline_add(UINT32* augend, UINT32* addend, UINT32 size){
    int prevCarry = 0;
    int carryFlag = 0;
    UINT32 tempResult1 = 0;
    UINT32 tempResult2 = 0;
    
    for(UINT32 i = size - 1;i != (UINT32)-1;i--){           //  add from LSB
        tempResult1 = augend[i] + addend[i];
        if(tempResult1 < augend[i])           //  overflow occured
            carryFlag = 1;
        else
            carryFlag = 0;
        
        tempResult2 = tempResult1 + prevCarry;
        if(tempResult2 < tempResult1)         //  overflow occured
            carryFlag |= 1;
        else
            carryFlag |= 0;
        
        augend[i] = tempResult2;
        prevCarry = carryFlag;
    }
    
    return prevCarry;
}





EXCEPTION BF_sub(PBF dest, PBF src){                //  dest -= src
    int result = EXC_NO_ERROR;
    
    if(dest->sign == src->sign)                     //  + (-) +, - (-) - are real sub
        result = BF_sub_controller(dest, src);
    else                                            //  + (-) -, - (-) + are real add
        result = BF_add_controller(dest, src);
    
    return result;
}

EXCEPTION BF_sub_controller(PBF minuend, PBF subtrahend){
    EXCEPTION result = EXC_NO_ERROR;
    
    if(BF_inline_sub(minuend->frac, subtrahend->frac, MIN(minuend->size, subtrahend->size)) != 0){       //  borrow in MSB (= underflowed in MSB)
        //  2's complement
        BF_inline_calcTwosComplement(minuend->frac, minuend->size);         //  convert fraction to absolute value
        
        //  sign switch
        minuend->sign = ~(minuend->sign) + 2;
    }
    
    return result;
}

int BF_inline_sub(UINT32* minuend, UINT32* subtrahend, UINT32 size){
    int prevBorrow = 0;
    int borrowFlag = 0;
    UINT32 tempResult1 = 0;
    UINT32 tempResult2 = 0;
    
    for(UINT32 i = size - 1;i != (UINT32)-1;i--){           //  sub from LSB
        tempResult1 = minuend[i] - subtrahend[i];
        if(tempResult1 > minuend[i])           //  underflow occured
            borrowFlag = 1;
        else
            borrowFlag = 0;
        
        tempResult2 = tempResult1 - prevBorrow;
        if(tempResult2 > tempResult1)          //  underflow occured
            borrowFlag |= 1;
        else
            borrowFlag |= 0;
        
        minuend[i] = tempResult2;
        prevBorrow = borrowFlag;
    }
    
    return prevBorrow;
}





EXCEPTION BF_mul(PBF dest, PBF src1, PBF src2){
    EXCEPTION result = EXC_NO_ERROR;
    
    PBF tempDest = BF_create(dest->size);
    if(src1->sign != src2->sign)
        tempDest->sign = 1;
    result = BF_mul_controller(tempDest, src1, src2);
    
    BF_copy(dest, tempDest);
    BF_delete(tempDest);
    
    return result;
}

EXCEPTION BF_mul_controller(PBF dest, PBF multiplicand, PBF multiplier){
    int result = 0;
    
    /* multiplicate each digits */
    for(UINT32 i = multiplier->size - 1;i != (UINT32)-1;i--){
        for(UINT32 j = multiplicand->size - 1;j != (UINT32)-1;j--){
            if(multiplier->frac[i] && multiplicand->frac[j])
                result |= BF_inline_add_mulValue64(dest->frac, (UINT64)multiplier->frac[i] * (UINT64)multiplicand->frac[j], dest->size, i+j);       //  add multiple result to each digits
        }
    }
    
    if(result == 1)
        return EXC_CALC_NUMBER_OVERFLOW;
        
    return EXC_NO_ERROR;
}



EXCEPTION BF_mulInteger(PBF dest, PBF src1, int src2){
    EXCEPTION result = EXC_NO_ERROR;
    
    UINT32 src2_sign = src2 < 0;
    
    PBF tempDest = BF_create(dest->size);
    
    if(src1->sign != src2_sign)
        tempDest->sign = 1;
    result = BF_mulInteger_controller(tempDest, src1, src2);
    
    BF_copy(dest, tempDest);
    BF_delete(tempDest);
    
    return result;
}

EXCEPTION BF_mulInteger_controller(PBF dest, PBF multiplicand, int multiplier){
    int result = 0;
    
    for(UINT32 i = multiplicand->size-1;i!=(UINT32)-1;i--){
        if(multiplicand->frac[i] && multiplier)
            result |= BF_inline_add_mulValue64(dest->frac, (UINT64)multiplicand->frac[i] * (UINT64)multiplier, dest->size, i);
    }
    
    if(result == 1)
        return EXC_CALC_NUMBER_OVERFLOW;
    
    return EXC_NO_ERROR;
}



int BF_inline_add_mulValue64(UINT32* dest, UINT64 mulValue, UINT32 size, UINT32 pos){
    if(pos+1>size) return 0;

    UINT32 lowNum = mulValue & 0xFFFFFFFF;          //  lower half bits
    UINT32 highNum = mulValue>>32;                  //  upper half bits
    
    if(pos == 0){
        if(BF_inline_add_mulValue32(dest, lowNum, size, pos) == 1 | highNum > 0)
            return 1;
        else
            return 0;
    }
    
    if(BF_inline_add_mulValue32(dest, lowNum, size, pos) | BF_inline_add_mulValue32(dest, highNum, size, pos-1))        //  check overflow occured
        return 1;
    
    return 0;
}


int BF_inline_add_mulValue32(UINT32* dest, UINT32 mulValue, UINT32 size, UINT32 pos){
    if(pos+1>size) return 0;
    
    int carry = 0;
    
    if(dest[pos] > dest[pos] + mulValue)
        carry = 1;
    
    dest[pos] += mulValue;
    
    while(carry){
        pos--;
        
        if(pos == (UINT32)-1)
            break;
        
        dest[pos] += carry;
        
        if(dest[pos] != 0)
            carry = 0;
    }
    
    return carry;
}



EXCEPTION BF_div(PBF dest, PBF dividend, PBF divisor){                   //    calc N/D
    if(BF_isZero(divisor))                      //  if N/0
        return EXC_INVALID_VALUE;
    
    if(BF_isZero(dividend)){                    //  if 0/D
        BF_initializeInt(dest, 0, 0);
        return EXC_NO_ERROR;
    }
    
    long long shiftingNum = 0;
    PBF stdDivisor = BF_create(divisor->size + 1);
    PBF tempDest = BF_create(dest->size);
    
    shiftingNum = BF_standardize(stdDivisor, divisor);            //    make divisor's range  1 <= D < 2 using shift operation
    BF_calcInverse(tempDest, stdDivisor);                                 //    calculate 1/D using newton-raphson method
    tempDest->sign = divisor->sign;                                       //    apply divisor's sign
    BF_mul(tempDest, tempDest, dividend);                                 //    N * 1/D
    /* recover previous shift operation */
    if(shiftingNum > 0)
        BF_inline_sll(tempDest->frac, tempDest->size, shiftingNum);
    else if(shiftingNum < 0)
        BF_inline_srl(tempDest->frac, tempDest->size, -shiftingNum);
    
    BF_copy(dest, tempDest);
    
    BF_delete(stdDivisor);
    BF_delete(tempDest);
    
    return EXC_NO_ERROR;
}

EXCEPTION BF_inv(PBF dest, PBF src){                                    //  calc 1/D
    if(BF_isZero(src))                      //  if 1/0
        return EXC_INVALID_VALUE;
    
    long long shiftingNum = 0;
    PBF stdSrc = BF_create(src->size + 1);
    PBF tempDest = BF_create(dest->size);
    
    shiftingNum = BF_standardize(stdSrc, src);            //    make src's range  1 <= D < 2 using shift operation
    BF_calcInverse(tempDest, stdSrc);                                 //    calculate 1/D using newton-raphson method
    tempDest->sign = src->sign;                                       //    apply src's sign
    /* recover previous shift operation */
    if(shiftingNum > 0)
        BF_inline_sll(tempDest->frac, tempDest->size, shiftingNum);
    else if(shiftingNum < 0)
        BF_inline_srl(tempDest->frac, tempDest->size, -shiftingNum);
    
    BF_copy(dest, tempDest);
    
    BF_delete(stdSrc);
    BF_delete(tempDest);
    
    return EXC_NO_ERROR;
}

void BF_calcInverse(PBF dest, PBF src){                     //  calc 1/D using Newton-Raphson method  (src is D)
    PBF param1_calcInit = BF_create(4);
    PBF param2_calcInit = BF_create(4);
    
    /* for setting optimal initial value (optimized in 1 <= src < 2) */
    BF_initialize(param1_calcInit, -0.476649250079016);         //  a
    BF_initialize(param2_calcInit, 1.408121055678469);          //  b
    
    PBF x_n = BF_create(dest->size);
    PBF term_x = BF_create(dest->size);
    PBF diff_x = BF_create(dest->size);
    
    //  task for optimizing (minimize unnecessary calculating) ,it is possible because this recurrence relation is incremental.
    x_n->size = 4;
    term_x->size = 4;
    diff_x->size = 4;
    
    /* set initial value */
    BF_mul(x_n, param1_calcInit, src);                    //  x0 = a*D
    BF_add(x_n, param2_calcInit);                         //  x0 = a*D + b
    
    do{
        BF_initializeInt(diff_x, 1, 0);                 //  diff_x = 1
        BF_mul(term_x, src, x_n);                       //  term_x = D*x
        BF_sub(diff_x, term_x);                         //  diff_x = 1 - D*x
        BF_mul(diff_x, x_n, diff_x);                    //  diff_x = x*(1 - D*x)
        BF_add(x_n, diff_x);                            //  x_n+1 = x_n + x_n*(1 - D*x_n)
        
        //  gradually increase size (according to the increase in precision)
        x_n->size = MIN(x_n->size * 1.5, dest->size);
        term_x->size = MIN(term_x->size * 1.5, dest->size);
        diff_x->size = MIN(diff_x->size * 1.5, dest->size);
    }while(BF_isZero(diff_x) == 0 || x_n->size != dest->size);      //  repeat until converge

    memcpy(dest->frac, x_n->frac, x_n->size * sizeof(UINT32));
    
    BF_delete(param1_calcInit);
    BF_delete(param2_calcInit);
    BF_delete(x_n);
    BF_delete(term_x);
    BF_delete(diff_x);
}



EXCEPTION BF_sqrt(PBF dest, PBF src){                   //  calc D^(0.5)
    if(src->sign)
        return EXC_INVALID_VALUE;
    
    if(BF_isZero(src)){
        BF_initializeInt(dest, 0, 0);
        return EXC_NO_ERROR;
    }
    
    long long shiftingNum = 0;
    PBF stdSrc= BF_create(src->size + 1);
    PBF tempDest = BF_create(dest->size);
    
    shiftingNum = BF_standardize(stdSrc, src);
    if(shiftingNum%2 != 0){          //  if odd num
        shiftingNum++;               //  fit to even num (for take off the root)
        BF_inline_sll(stdSrc->frac, stdSrc->size, 1);
    }
    BF_calcSqrt(tempDest, stdSrc);
    /* recover previous shift operation */
    if(shiftingNum < 0)
        BF_inline_sll(tempDest->frac, tempDest->size, -shiftingNum/2);
    else if(shiftingNum > 0)
        BF_inline_srl(tempDest->frac, tempDest->size, shiftingNum/2);
    
    BF_copy(dest, tempDest);
    
    BF_delete(stdSrc);
    BF_delete(tempDest);
    
    return EXC_NO_ERROR;
}

void BF_calcSqrt(PBF dest, PBF src){                    //  calc D^(0.5) using Newton-Raphson method  (src is D)
    PBF param1_calcInit = BF_create(4);
    PBF param2_calcInit = BF_create(4);
    
    /* for setting optimal initial value (optimized in 1 <= src < 4) */
    BF_initialize(param1_calcInit, 0.325925925925926);         //  a
    BF_initialize(param2_calcInit, 0.740740740740741);          //  b
    
    PBF old_x = BF_create(dest->size);
    PBF x_n = BF_create(dest->size);
    PBF term_x = BF_create(dest->size);
    
    //  task for optimizing (minimize unnecessary calculating) ,it is possible because this recurrence relation is incremental.
    old_x->size = 4;
    x_n->size = 4;
    term_x->size = 4;
    
    /* set initial value */
    BF_mul(x_n, param1_calcInit, src);                      //  x0 = a*D
    BF_add(x_n, param2_calcInit);                           //  x0 = a*D + b
    

    do{
        BF_copy(old_x, x_n);
        BF_div(term_x, src, x_n);                       //  term_x = D/x
        BF_add(x_n, term_x);                            //  x = x + D/x
        BF_inline_srl(x_n->frac, x_n->size, 1);         //  x_n+1 = 1/2 * (x_n + D/x_n)
        //  gradually increase size (according to the increase in precision)
        old_x->size = MIN(old_x->size * 1.5, dest->size);
        x_n->size = MIN(x_n->size * 1.5, dest->size);
        term_x->size = MIN(term_x->size * 1.5, dest->size);
    }while(BF_isClose(old_x, x_n) == 0 || x_n->size != dest->size);
    
    memcpy(dest->frac, x_n->frac, x_n->size * sizeof(UINT32));
    
    BF_delete(param1_calcInit);
    BF_delete(param2_calcInit);
    BF_delete(old_x);
    BF_delete(x_n);
    BF_delete(term_x);
}
