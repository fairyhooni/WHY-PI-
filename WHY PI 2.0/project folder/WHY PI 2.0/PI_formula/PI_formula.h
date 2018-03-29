/*
 **
 **  WHY PI 2.0
 **  PI_formula.h
 **  Created by cHoon on 2017. 12. 7..
 **  Copyright © 2017년 cHoon. All rights reserved.
 */

#ifndef PI_formula_h
#define PI_formula_h



#include "BigFloat.h"


#define SERIES 0
#define EULER 1

/*
 enum about algorithms
 */
enum _algorithm{
    AGR_MACHIN1_NORMAL = 1,
    AGR_MACHIN1_EULER = 2,
    
    AGR_MACHIN2_NORMAL = 3,
    AGR_MACHIN2_EULER = 4,
    
    AGR_MACHIN3_NORMAL = 5,
    AGR_MACHIN3_EULER = 6,
    
    AGR_COSINE_RECURRENCE = 7,
    AGR_GAUSSLEGENDRE = 8,
    AGR_CHUDNOVSKY = 9
};
typedef enum _algorithm ALGORITHM;


/* functions for PI calculation algorithms */
void PI_calcMachin1(PBF calcPI, int arctan_mode);        //  pi = 16*arctan(1/5) - 4*arctan(1/239)
void PI_calcMachin2(PBF calcPI, int arctan_mode);        //  pi = 48*arctan(1/49) + 128*arctan(1/57) - 20*arctan(1/239) + 48*arctan(1/110443)
void PI_calcMachin3(PBF calcPI, int arctan_mode);        //  pi = 732*arctan(1/239) + 128*arctan(1/1023) - 272*arctan(1/5832) + 48*arctan(1/110443) - 48*arctan(1/4841182) - 400*arctan(1/6826318)
void PI_calcCosRecurrence(PBF calcPI);                   //  x_n+1 = x_n + cos(x_n),  x_infinite = pi/2
void PI_calcGaussLegendre(PBF calcPI);
void PI_calcChudnovsky(PBF calcPI);                      

/* assistant operator functions */
void arctan_series(PBF dest, PBF operand);                //  dest = arctan(operand),   series ver.
void arctan_euler(PBF dest, PBF operand);                 //  dest = arctan(operand),   euler ver.
void cos_series(PBF dest, PBF src);               //   dest = cos(src), using talyor series
void cos_halfAngle_formula(PBF dest, PBF src);    //   dest = cos(src), using half-angle formula -> cosx = 2cos^x/2 - 1
 

#endif /* PI_formula_h */
