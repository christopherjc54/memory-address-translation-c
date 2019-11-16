#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "program.h"

#define PHY_MEM 1024
#define VIRT_MEM 4096
#define PAGE_FRAME_BYTES 128

int main(int argc, char* argv[]) {
    if(argc < 3 || argc > 3) {
            printf("Usage: part2 BytesPerPage SizeOfVirtualMemory SizeOfPhysicalMemory SequenceFile OutputFile\n");
            exit(-1);
    }

    int offsetSize = round(log(PAGE_FRAME_BYTES)/log(2));
    int numEntriesPhysical = PHY_MEM/PAGE_FRAME_BYTES; //7+1 for OS frame at beginning
    int numEntriesPageTable = VIRT_MEM/PAGE_FRAME_BYTES; //32

    runProgram(offsetSize, numEntriesPhysical, numEntriesPageTable, argv[1], argv[2]);

    return 0;
}