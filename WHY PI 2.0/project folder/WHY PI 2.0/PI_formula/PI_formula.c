//
//  PI_formula.c
//  WHY PI 2.0
//
//  Created by 황치훈 on 2018. 2. 20..
//  Copyright © 2018년 황치훈. All rights reserved.
//

#include "PI_formula.h"
#include "BigFloat.h"

/* 16*arctan(1/5) - 4*arctan(1/239) */
void PI_calcMachin1(PBF calcPI, int arctan_mode){
    PBF operand1 = BF_create(calcPI->size);
    PBF operand2 = BF_create(calcPI->size);
    
    BF_initializeInt(operand1, 5, 0);
    BF_initializeInt(operand2, 239, 0);
    
    BF_inv(operand1, operand1);             //  operand1 = 1/5
    BF_inv(operand2, operand2);             //  operand2 = 1/239
    
    if(arctan_mode == SERIES){
        arctan_series(operand1, operand1);      //  operand1 = arctan(1/5)
        arctan_series(operand2, operand2);      //  operand2 = arctan(1/239)
    }else if(arctan_mode == EULER){
        arctan_euler(operand1, operand1);
        arctan_euler(operand2, operand2);      
    }
    
    BF_mulInteger(operand1, operand1, 16);  //  operand1 = 16*arctan(1/5)
    BF_mulInteger(operand2, operand2, 4);   //  operand2 = 4*arctan(1/239)
    
    BF_sub(operand1, operand2);             //  operand1 = 16*arctan(1/5) - 4*arctan(1/239)
    
    BF_copy(calcPI, operand1);
    
    BF_delete(operand1);
    BF_delete(operand2);
}

/* 48*arctan(1/49) + 128*arctan(1/57) - 20*arctan(1/239) + 48*arctan(1/110443) */
void PI_calcMachin2(PBF calcPI, int arctan_mode){
    PBF operand1 = BF_create(calcPI->size);
    PBF operand2 = BF_create(calcPI->size);
    PBF operand3 = BF_create(calcPI->size);
    PBF operand4 = BF_create(calcPI->size);
    
    BF_initializeInt(operand1, 49, 0);
    BF_initializeInt(operand2, 57, 0);
    BF_initializeInt(operand3, 239, 0);
    BF_initializeInt(operand4, 110443, 0);
    
    BF_inv(operand1, operand1);
    BF_inv(operand2, operand2);
    BF_inv(operand3, operand3);
    BF_inv(operand4, operand4);
    
    if(arctan_mode == SERIES){
        arctan_series(operand1, operand1);
        arctan_series(operand2, operand2);
        arctan_series(operand3, operand3);
        arctan_series(operand4, operand4);
    }else if(arctan_mode == EULER){
        arctan_euler(operand1, operand1);
        arctan_euler(operand2, operand2);
        arctan_euler(operand3, operand3);
        arctan_euler(operand4, operand4);
    }
    
    BF_mulInteger(operand1, operand1, 48);
    BF_mulInteger(operand2, operand2, 128);
    BF_mulInteger(operand3, operand3, 20);
    BF_mulInteger(operand4, operand4, 48);
    
    BF_add(operand1, operand2);
    BF_sub(operand1, operand3);
    BF_add(operand1, operand4);
    
    BF_copy(calcPI, operand1);
    
    BF_delete(operand1);
    BF_delete(operand2);
    BF_delete(operand3);
    BF_delete(operand4);
}

/* pi = 732*arctan(1/239) + 128*arctan(1/1023) - 272*arctan(1/5832) + 48*arctan(1/110443) - 48*arctan(1/4841182) - 400*arctan(1/6826318) */
void PI_calcMachin3(PBF calcPI, int arctan_mode){
    PBF operand1 = BF_create(calcPI->size);
    PBF operand2 = BF_create(calcPI->size);
    PBF operand3 = BF_create(calcPI->size);
    PBF operand4 = BF_create(calcPI->size);
    PBF operand5 = BF_create(calcPI->size);
    PBF operand6 = BF_create(calcPI->size);
    
    BF_initializeInt(operand1, 239, 0);
    BF_initializeInt(operand2, 1023, 0);
    BF_initializeInt(operand3, 5832, 0);
    BF_initializeInt(operand4, 110443, 0);
    BF_initializeInt(operand5, 4841182, 0);
    BF_initializeInt(operand6, 6826318, 0);
    
    BF_inv(operand1, operand1);
    BF_inv(operand2, operand2);
    BF_inv(operand3, operand3);
    BF_inv(operand4, operand4);
    BF_inv(operand5, operand5);
    BF_inv(operand6, operand6);
    
    if(arctan_mode == SERIES){
        arctan_series(operand1, operand1);
        arctan_series(operand2, operand2);
        arctan_series(operand3, operand3);
        arctan_series(operand4, operand4);
        arctan_series(operand5, operand5);
        arctan_series(operand6, operand6);
    }else if(arctan_mode == EULER){
        arctan_euler(operand1, operand1);
        arctan_euler(operand2, operand2);
        arctan_euler(operand3, operand3);
        arctan_euler(operand4, operand4);
        arctan_euler(operand5, operand5);
        arctan_euler(operand6, operand6);
    }
    
    BF_mulInteger(operand1, operand1, 732);
    BF_mulInteger(operand2, operand2, 128);
    BF_mulInteger(operand3, operand3, 272);
    BF_mulInteger(operand4, operand4, 48);
    BF_mulInteger(operand5, operand5, 48);
    BF_mulInteger(operand6, operand6, 400);
    
    BF_add(operand1, operand2);
    BF_sub(operand1, operand3);
    BF_add(operand1, operand4);
    BF_sub(operand1, operand5);
    BF_sub(operand1, operand6);
    
    BF_copy(calcPI, operand1);
    
    BF_delete(operand1);
    BF_delete(operand2);
    BF_delete(operand3);
    BF_delete(operand4);
    BF_delete(operand5);
    BF_delete(operand6);
}

/* x_n+1 = x_n + cos(x_n),  x_infinite = pi/2 */
void PI_calcCosRecurrence(PBF calcPI){
    PBF x_n = BF_create(calcPI->size);
    PBF cos_x_n = BF_create(calcPI->size);
    PBF zero = BF_create(calcPI->size);
    //  task for optimizing (minimize unnecessary calculating) ,it is possible because this recurrence relation is incremental.
    x_n->size = 4;
    cos_x_n->size = 4;
    zero->size = 4;
    
    //  set initial value
    BF_initialize(x_n, 3.1415926535/2.);
    
    do{
        cos_halfAngle_formula(cos_x_n, x_n);        //  much faster than normal cosine
        BF_add(x_n, cos_x_n);               //  x_n+1 = x_n + cos_x_n
        
        //  gradually increase size (according to the increase in precision)
        x_n->size = MIN(x_n->size * 2.5, calcPI->size);
        cos_x_n->size = MIN(cos_x_n->size * 2.5, calcPI->size);
        zero->size = MIN(zero->size * 2.5, calcPI->size);
    }while(BF_isClose(zero, cos_x_n) == 0 || x_n->size != calcPI->size);

    BF_mulInteger(calcPI, x_n, 2);               //  pi = 2 * pi/2
    
    BF_delete(x_n);
    BF_delete(cos_x_n);
    BF_delete(zero);
}


void PI_calcGaussLegendre(PBF calcPI){
    PBF curr_a = BF_create(calcPI->size);
    PBF next_a = BF_create(calcPI->size);
    PBF curr_b = BF_create(calcPI->size);
    PBF curr_t = BF_create(calcPI->size);

    PBF tempSF = BF_create(4);
    PBF tempBF = BF_create(calcPI->size);
    
    
    /*  set initial value  */
    BF_initializeInt(curr_a, 1, 0);                 //  a0 = 1
    
    BF_initializeInt(tempSF, 2, 0);
    BF_sqrt(curr_b, tempSF);
    BF_inline_srl(curr_b->frac, curr_b->size, 1);   //  b0 = 1/sqrt(2)
    
    BF_initialize(curr_t, 0.25);                    //  t0 = 1/4
    
    BF_copy(next_a, curr_a);
    BF_add(next_a, curr_b);
    BF_inline_srl(next_a->frac, next_a->size, 1);   //  a1 = (a0 + b0) / 2
    
    UINT32 n = 0;
    do{
        BF_mul(curr_b, curr_a, curr_b);             //  b_n+1 = a_n*b_n
        BF_sqrt(curr_b, curr_b);                    //  b_n+1 = sqrt(a_n*b_n)
        
        BF_copy(tempBF, curr_a);
        BF_sub(tempBF, next_a);                             //  tempBF = a_n - a_n+1
        BF_mul(tempBF, tempBF, tempBF);                     //  tempBF = (a_n - a_n+1)^2
        BF_inline_sll(tempBF->frac, tempBF->size, n);       //  tempBF = 2^n * (a_n - a_n+1)^2
        BF_sub(curr_t, tempBF);                             //  t_n+1 = t_n - 2^n * (a_n - a_n+1)^2
        
        BF_copy(curr_a, next_a);                            //  move a_n+1
        BF_add(next_a, curr_b);                             //  a_n+2 = a_n+1 + b_n+1
        BF_inline_srl(next_a->frac, next_a->size, 1);       //  a_n+2 = (a_n+1 + b_n+1) / 2
        
        n++;
    }while(BF_isClose(curr_a, curr_b) == 0);
    

    BF_mul(calcPI, next_a, next_a);
    BF_div(calcPI, calcPI, curr_t);                   //  pi_n+1 = a_n+1^2 / t_n
    
    
    BF_delete(curr_a);
    BF_delete(next_a);
    BF_delete(curr_b);
    BF_delete(curr_t);
    BF_delete(tempSF);
    BF_delete(tempBF);
}


void PI_calcChudnovsky(PBF calcPI){
    PBF sum_a = BF_create(calcPI->size);                //  sigma a_k
    PBF sum_b = BF_create(calcPI->size);                //  sigma b_k
    
    PBF curr_a = BF_create(calcPI->size);               //  a_k
    PBF curr_b = BF_create(calcPI->size);               //  b_k
    
    PBF const_1 = BF_create(calcPI->size);
    PBF const_2 = BF_create(calcPI->size);
    PBF term_k = BF_create(calcPI->size);
    
    PBF tempSF = BF_create(4);
    PBF tempBF = BF_create(calcPI->size);

    /* set constants */
    BF_initializeInt(tempSF, 320160, 1);
    BF_inv(tempBF, tempSF);
    BF_mul(const_1, tempBF, tempBF);                //  const_1 = 1/320160^2
    BF_mul(const_1, const_1, tempBF);               //  const_1 = - 1/320160^3
    
    BF_initializeInt(tempSF, 10005, 0);
    BF_sqrt(const_2, tempSF);
    BF_mulInteger(const_2, const_2, 426880);        //  const_2 = 426880*sqrt(10005)
    
    //  k = 0  ->  a_0 = 1, b_0 = 0
    BF_initializeInt(curr_a, 1, 0);
    BF_add(sum_a, curr_a);
    
    UINT32 k = 1;
    do{
        /* calc a_k using a_k-1 */
        BF_mul(curr_a, curr_a, const_1);            //  a_k = -1/320160^3 * a_k-1
        
        BF_initializeInt(tempSF, k, 0);
        BF_inv(tempBF, tempSF);
        BF_mul(term_k, tempBF, tempBF);
        BF_mul(term_k, term_k, tempBF);             //  term_1 = 1/k^3
        
        BF_mul(curr_a, curr_a, term_k);             //  a_k = -1/(320160^3 * k^3) * a_k-1
        
        BF_mulInteger(curr_a, curr_a, 6*k - 1);
        BF_mulInteger(curr_a, curr_a, 6*k - 3);
        BF_mulInteger(curr_a, curr_a, 6*k - 5);     //  a_k = -((6*k - 1)(6*k - 3)(6*k - 5))/(320160^3 * k^3) * a_k-1
        
        /* calc b_k using a_k */
        BF_mulInteger(curr_b, curr_a, k);           //  b_k = a_k * k
        
        
        BF_add(sum_a, curr_a);                      //  calc sigma a
        BF_add(sum_b, curr_b);                      //  calc sigma b
           
        k++;
    }while(BF_isZero(curr_a) == 0);                 //  if sum_a and sum_b converge to a specific value, end of loop.
    
    BF_initializeInt(calcPI, 0, 0);
    BF_mulInteger(tempBF, sum_a, 13591409);
    BF_add(calcPI, tempBF);
    BF_mulInteger(tempBF, sum_b, 545140134);
    BF_add(calcPI, tempBF);                         //  calcPI = 13591409*sum_a + 545140134*sum_b
    
    BF_div(calcPI, const_2, calcPI);                //  calcPI = 426880*sqrt(10005) / (13591409*sum_a + 545140134*sum_b)
    
    
    BF_delete(sum_a);
    BF_delete(sum_b);
    BF_delete(curr_a);
    BF_delete(curr_b);
    BF_delete(const_1);
    BF_delete(const_2);
    BF_delete(term_k);
    BF_delete(tempSF);
    BF_delete(tempBF);
}


void arctan_series(PBF dest, PBF operand){
    PBF tempDest = BF_create(dest->size);           //  result value
    PBF ratio = BF_create(dest->size);              //  x^2
    PBF divisor = BF_create(4);                     //  2n + 1
    PBF currTerm_x = BF_create(dest->size);         //  x^(2n + 1)
    PBF currTerm = BF_create(dest->size);           //  {(-1)^n * x^(2n + 1)} / (2n + 1)
    
    BF_mul(ratio, operand, operand);
    
    //  n = 0
    BF_add(currTerm_x, operand);
    BF_add(currTerm, currTerm_x);
    BF_add(tempDest, currTerm);
    
    UINT32 n = 1;
    do{
        BF_initializeInt(divisor, 2*n + 1, n%2);        //  divisor = (-1)^n * (2n + 1)
        BF_mul(currTerm_x, currTerm_x, ratio);          //  x_n = x_n-1 * x^2
        BF_div(currTerm, currTerm_x, divisor);
        
        BF_add(tempDest, currTerm);
        n++;
    }while(BF_isZero(currTerm) == 0);
    
    BF_copy(dest, tempDest);
    
    BF_delete(tempDest);
    BF_delete(ratio);
    BF_delete(divisor);
    BF_delete(currTerm_x);
    BF_delete(currTerm);
}

void arctan_euler(PBF dest, PBF operand){
    PBF tempDest = BF_create(dest->size);
    PBF ratio1 = BF_create(dest->size);     //  x^2 / (1+x^2)
    PBF ratio2 = BF_create(dest->size);     //  2n / 2n+1
    PBF tempVar = BF_create(dest->size);
    PBF tempVar_int = BF_create(4);
    PBF currTerm = BF_create(dest->size);
    
    //  make ratio1
    BF_initializeInt(ratio1, 1, 0);         //  ratio1 = 1
    BF_mul(tempVar, operand, operand);         //  temp = x^2
    tempVar->frac[0]++;                        //  temp = 1+x^2
    BF_inv(tempVar, tempVar);                     //  temp = 1/1+x^2
    BF_sub(ratio1, tempVar);                   //  ratio1 = 1 - 1/1+x^2 = x^2 / (1+x^2)
    
    
    //  n = 0
    BF_mul(currTerm, tempVar, operand);        //  x0 = x/1+x^2
    BF_add(tempDest, currTerm);
    
    
    UINT32 n = 1;
    do{
        //  make ratio2
        BF_initializeInt(ratio2, 1, 0);             //  ratio2 = 1
        BF_initializeInt(tempVar_int, 2*n + 1, 0);  //  tempVar_int = 2n+1
        BF_inv(tempVar, tempVar_int);               //  tempVar = 1/2n+1
        BF_sub(ratio2, tempVar);                    //  ratio2 = 1 - 1/2n+1 = 2n/2n+1
        
        BF_mul(currTerm, currTerm, ratio1);
        BF_mul(currTerm, currTerm, ratio2);
        
        BF_add(tempDest, currTerm);
        n++;
    }while(BF_isZero(currTerm) == 0);
    
    
    BF_copy(dest, tempDest);
    
    BF_delete(tempDest);
    BF_delete(ratio1);
    BF_delete(ratio2);
    BF_delete(tempVar);
    BF_delete(tempVar_int);
    BF_delete(currTerm);
}

/* using talyor series */
void cos_series(PBF dest, PBF src){
    PBF tempDest = BF_create(dest->size);
    PBF currTerm = BF_create(dest->size);
    PBF ratio = BF_create(dest->size);
    PBF divisor = BF_create(4);
    
    /* ratio = -x^2 */
    BF_mul(ratio, src, src);
    ratio->sign = 1;
    
    //  n = 0
    BF_initializeInt(currTerm, 1, 0);
    BF_add(tempDest, currTerm);
    
    UINT32 n = 1;
    do{
        BF_initializeInt(divisor, (2*n - 1)*2*n, 0);        //  divisor = (2n-1)2n
        BF_mul(currTerm, currTerm, ratio);                  //  x_n+1 = x_n * -x^2
        BF_div(currTerm, currTerm, divisor);                //  x_n+1 = x_n * -x^2 / (2n-1)2n
        
        BF_add(tempDest, currTerm);
        n++;
    }while(BF_isZero(currTerm) == 0);
    
    
    BF_copy(dest, tempDest);
    
    BF_delete(tempDest);
    BF_delete(currTerm);
    BF_delete(ratio);
    BF_delete(divisor);
}

/* cosx = 2cos^x/2 - 1  (Convergence speed is fast because x becomes smaller) */
void cos_halfAngle_formula(PBF dest, PBF src){
    PBF tempDest = BF_create(dest->size + 2);
    PBF one = BF_create(4);
    BF_initializeInt(one, 1, 0);
    PBF halfAngle = BF_copyCreate(src);
    BF_extendAllocate(halfAngle, halfAngle->size + 2);
    
    BF_inline_srl(halfAngle->frac, halfAngle->size, 32);         //  halfAngle = x/2^32
    cos_series(tempDest, halfAngle);                            //  tempDest = cos x/2^32
    //  apply half-angle formula recursively (calculate cos x using cos x/2^32)
    for(int i = 0;i<32;i++){
        BF_mul(tempDest, tempDest, tempDest);                       //  tempDest = cos^2 x/2
        BF_inline_sll(tempDest->frac, tempDest->size, 1);           //  tempDest = 2*cos^2 x/2
        BF_sub(tempDest, one);                                      //  tempDest = 2*cos^2 x/2 - 1
    }
    
    tempDest->size = dest->size;
    
    BF_copy(dest, tempDest);
    
    BF_delete(tempDest);
    BF_delete(one);
    BF_delete(halfAngle);
}
