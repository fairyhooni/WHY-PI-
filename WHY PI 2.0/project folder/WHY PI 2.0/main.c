//
//  main.c
//  WHY PI 2.0
//
//  Created by 황치훈 on 2017. 12. 7..
//  Copyright © 2017년 황치훈. All rights reserved.
//

#include <limits.h>
#include "BigFloat.h"
#include "PI_formula.h"
#include "File_util.h"


void introduceWHYPI_ToConsole();
ALGORITHM getAlgorithmToUse();
UINT64 getNumOfDigit_UnderDecimalPoint();
void calculatePIandMeasureTime(PBF calcPI, ALGORITHM agr);

void normalMode();                  //  set algorithm and number of digits, then output the time and calculated pi value.
void comparePerformanceMode();      //  select algorithms to compare, then output the time(performance).



int main(int argc, const char * argv[]) {
    
    normalMode();
//    comparePerformanceMode();
    
    return 0;
}


void introduceWHYPI_ToConsole(){
    printf("Welcome to execute WHY PI 2.0\n**\n");
    printf("This is PI calculation program.\n**\n");
    printf("Please test WHY PI 2.0 and tell me your feedback or any other comment.\n\n\n");
}

ALGORITHM getAlgorithmToUse(){
    int input;
    
    printf("Select Algorithm.\n**\n");
    
    printf("1. Machin using normal arctan.\n");
    printf("2. Machin using euler arctan.\n");
    printf("3. Kikuo-takano(machin-like) using normal arctan.\n");
    printf("4. Kikuo-takano(machin-like) using euler arctan.\n");
    printf("5. Hwang Chien-Lih(machin-like) using normal arctan.\n");
    printf("6. Hwang Chien-Lih(machin-like) using euler arctan.\n");
    printf("7. Recurrence relation using cosine.\n");
    printf("8. Gauss-Legendre algorithm.\n");
    printf("9. Chudnovsky algorithm.\n\n");
    
    printf("Select algorithm: ");
    
    scanf("%d", &input);
    
    while(input<=0 | input>9){
        printf("\nInvalid value! Reselect!\n");
        printf("Select algorithm: ");
        scanf("%d", &input);
    }
    
    return input;
}

UINT64 getNumOfDigit_UnderDecimalPoint(){
    UINT64 input;
    
    printf("\nNumber of digits: ");
    scanf("%lld", &input);
    
    while(input == 0){
        printf("\nInvalid value! Re input!\n");
        printf("Number of digits: ");
        scanf("%lld", &input);
    }
    
    return input;
}


void calculatePIandMeasureTime(PBF calcPI, ALGORITHM agr){
    clock_t start_t, end_t;
    
    start_t = clock();
    switch(agr){
        case AGR_MACHIN1_NORMAL: printf("Machin normal arctan\n");
            PI_calcMachin1(calcPI, SERIES);
            break;
            
        case AGR_MACHIN1_EULER: printf("Machin euler arctan\n");
            PI_calcMachin1(calcPI, EULER);
            break;
            
        case AGR_MACHIN2_NORMAL: printf("Kikuo-takano normal arctan\n");
            PI_calcMachin2(calcPI, SERIES);
            break;
            
        case AGR_MACHIN2_EULER: printf("Kikuo-takano euler arctan\n");
            PI_calcMachin2(calcPI, EULER);
            break;
            
        case AGR_MACHIN3_NORMAL: printf("Hwang Chien-Lih normal arctan\n");
            PI_calcMachin3(calcPI, SERIES);
            break;
            
        case AGR_MACHIN3_EULER: printf("Hwang Chien-Lih euler arctan\n");
            PI_calcMachin3(calcPI, EULER);
            break;
            
        case AGR_COSINE_RECURRENCE: printf("Cosine Recurrence\n");
            PI_calcCosRecurrence(calcPI);
            break;
            
        case AGR_GAUSSLEGENDRE: printf("Gauss-Legendre\n");
            PI_calcGaussLegendre(calcPI);
            break;
            
        case AGR_CHUDNOVSKY: printf("Chudnovsky\n");
            PI_calcChudnovsky(calcPI);
            break;
    }
    end_t = clock();
    printf("Calculation Time: %lf\n\n", (double)(end_t - start_t)/CLOCKS_PER_SEC);
    
    return;
}

void normalMode(){
    ALGORITHM selectedAGR;
    UINT64 numOfDigit;
    PBF calcPI;
    
    introduceWHYPI_ToConsole();
    selectedAGR = getAlgorithmToUse();
    numOfDigit = getNumOfDigit_UnderDecimalPoint();
    
    printf("\n\n************************************\n***************RESULT***************\n************************************\n\n");
    
    calcPI = BF_create((UINT32)(numOfDigit/9) + 3);
    calculatePIandMeasureTime(calcPI, selectedAGR);
    
    
    /* File to output the calculated pi */
    FILE* calcPI_File = NULL;
    char relativePath[PATH_MAX] = "./calcPI.txt";
    char absolutePath[PATH_MAX];
    
    if((calcPI_File = fopen(relativePath, "w+")) == NULL){
        printf("ERROR OCCURED : File not generated!\n\n");
        exit(EXIT_FAILURE);
    }
    BF_printDec(calcPI_File, calcPI, numOfDigit);               //  output pi in decimal
    
    if(realpath(relativePath, absolutePath) == NULL){
        perror("ERROR: Output file path error!\n\n");
        exit(EXIT_FAILURE);
    }else
        printf("PI value was outputted in %s\n\n", absolutePath);
    

    BF_delete(calcPI);
    fclose(calcPI_File);

    return;
}


void comparePerformanceMode(){
    UINT64 numOfDigit;
    PBF calcPI;
    ALGORITHM algorithms[10] = {0,};
    int temp;
    
    
    introduceWHYPI_ToConsole();
    
    
    printf("Select Algorithms to compare.\n**\n");
    
    printf("1. Machin using normal arctan.\n");
    printf("2. Machin using euler arctan.\n");
    printf("3. kikuo-takano(machin-like) using normal arctan.\n");
    printf("4. kikuo-takano(machin-like) using euler arctan.\n");
    printf("5. Hwang Chien-Lih(machin-like) using normal arctan.\n");
    printf("6. Hwang Chien-Lih(machin-like) using euler arctan.\n");
    printf("7. Recurrence relation using cosine.\n");
    printf("8. Gauss-Legendre algorithm.\n");
    printf("9. Chudnovsky algorithm.\n\n");
    
    printf("Select algorithms: ");
    
    for(int i = 0; i<10; i++){
        temp = getchar();
        if(temp <'1' | temp > '9'){
            if(temp == '\n')
                break;
            i--;
        }
        else
            algorithms[i] = temp - '0';
    }
    
    numOfDigit = getNumOfDigit_UnderDecimalPoint();
    
    
    printf("\n\n************************************\n***************RESULT***************\n************************************\n\n");
    
    calcPI = BF_create((UINT32)(numOfDigit/9) + 3);
    for(int i = 0;i<10;i++){
        if(algorithms[i] == 0)
            break;
        calculatePIandMeasureTime(calcPI, algorithms[i]);
    }
    
    return;
}




/* holding code */

//    /* set file pointers to compare */
//    FILE* realPI_File = NULL;
//    if((realPI_File = fopen("./realPI.txt", "r")) == NULL)
//        printf("ERROR OCCURED : File not found!");

//    start_t = clock();
//    PI_calcGaussLegendre(calcPI);
//    end_t = clock();
//    printf("Time: %lf\n", (double)(end_t - start_t)/CLOCKS_PER_SEC);
//    fseek(calcPI_File, 0, SEEK_SET);
//    fseek(realPI_File, 0, SEEK_SET);
//    BF_printDec(calcPI_File, calcPI, 0);
//    fseek(calcPI_File, 0, SEEK_SET);
//    printf("Num of matching digit(under the decimal point): %lld\n\n", countMatching_NumUnderDecimalPoint(calcPI_File, realPI_File));       //  compare results

//    fclose(realPI_File);
