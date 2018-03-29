//
//  File_util.h
//  WHY PI 2.0
//
//  Created by 황치훈 on 2018. 2. 22..
//  Copyright © 2018년 황치훈. All rights reserved.
//

#ifndef File_util_h
#define File_util_h

#include <stdio.h>
#include <stdlib.h>

void writeNumStrToFile(FILE* fp, char* str);                    

long long countMatching_NumUnderDecimalPoint(FILE* fp1, FILE* fp2);



#endif /* File_util_h */
