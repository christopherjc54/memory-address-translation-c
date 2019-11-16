#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "program.h"

int main(int argc, char* argv[]) {
    if(argc < 6 || argc > 6) {
            printf("Usage: part3 BytesPerPage SizeOfVirtualMemory SizeOfPhysicalMemory SequenceFile OutputFile\n");
            exit(-1);
    }

    int pageFrameBytes = atoi(argv[1]);
    int virtualMemorySize = atoi(argv[2]);
    int physicalMemorySize = atoi(argv[3]);
    char* sequenceFile = argv[4];
    char* outputFile = argv[5];

    printf("Page/Frame Bytes: %d\n", pageFrameBytes);
    printf("Virtual Memory Size: %d\n", virtualMemorySize);
    printf("Physical Memory Size: %d\n", physicalMemorySize);
    printf("Sequence File Name: %s\n", sequenceFile);
    printf("Output File Name: %s\n\n", outputFile);

    int offsetSize = round(log(pageFrameBytes)/log(2)); // 128 = 2^7
    int numEntriesPhysical = physicalMemorySize/pageFrameBytes; //7+1 for OS frame at beginning
    int numEntriesPageTable = virtualMemorySize/pageFrameBytes; //32

    runProgram(offsetSize, numEntriesPhysical, numEntriesPageTable, sequenceFile, outputFile);

    return 0;
}