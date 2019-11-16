#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <stdio.h>
#include "data.h"
#include "pagetable.h"
#include "phypages.h"

void runProgram(int _offsetSize, int _numEntriesPhysical, int _numEntriesPageTable, char* _inFileName, char* _outFileName);

#endif