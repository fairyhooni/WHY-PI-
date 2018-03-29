//
//  File_util.c
//  WHY PI 2.0
//
//  Created by 황치훈 on 2018. 2. 22..
//  Copyright © 2018년 황치훈. All rights reserved.
//

#include "File_util.h"



void writeNumStrToFile(FILE* fp, char* str){
    //  print integer part
    do
        fputc(*str, fp);
    while(*(str++) != '.');
    
    fputc('\n', fp);
    
    long long i = 1;
    while(*str != '\0'){
        fputc(*(str++), fp);
        if(i%10 == 0){
            fputc(' ', fp);
            if(i%100 == 0)
                fputc('\n', fp);
        }
        i++;
    }
    
    fputc('\n', fp);
}


long long countMatching_NumUnderDecimalPoint(FILE* fp1, FILE* fp2){
    if((feof(fp1) | feof(fp2)))
        return 0;
    
    long long numOfMatching = 0;
    char buffer1 = 0, buffer2 = 0;
    int numFlag1 = 0, numFlag2 = 0;
    
    //  check if integer part matched
    while(~(feof(fp1) | feof(fp2))){
        buffer1 = fgetc(fp1);
        buffer2 = fgetc(fp2);
        
        if(buffer1 != buffer2)
            return 0;
        
        if(buffer1 == '.')              //  find decimal point
            break;
    }
    
    
    //  counting start
    while(!(feof(fp1) | feof(fp2))){
        if(numFlag1 == numFlag2){           //  both are num or else.
            buffer1 = fgetc(fp1);
            buffer2 = fgetc(fp2);
        }else{                              //  one is num, the other is else.
            //  then else file pointer get next character.
            if(numFlag1 == 1)
                buffer2 = fgetc(fp2);
            else
                buffer1 = fgetc(fp1);
        }
        
        //  num flag setting
        if((buffer1 >= '0') & (buffer1 <= '9'))
            numFlag1 = 1;
        else
            numFlag1 = 0;
        
        if((buffer2 >= '0') & (buffer2 <= '9'))
            numFlag2 = 1;
        else
            numFlag2 = 0;
        
        //  if both are num, then compare.
        if(numFlag1 & numFlag2){
            if(buffer1 == buffer2)
                numOfMatching++;
            else
                break;
        }
    }
    
    return numOfMatching;
}
