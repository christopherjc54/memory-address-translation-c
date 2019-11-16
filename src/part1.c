#include <stdio.h>
#include <stdlib.h>
#include "data.h"

#define PHY_MEM 1024
#define VIRT_MEM 4096
#define PAGE_FRAME_BYTES 128;

int main(int argc, char* argv[]) {
    if(argc < 3 || argc > 3) {
            printf("Usage: part1 infile outfile\n");
            exit(-1);
    }

    unsigned long fileSize;
    unsigned long* memAccesses = readData(argv[1], &fileSize);

    int pageTable[32];
    void* frames[32];
    pageTable[0] = 2;
    pageTable[1] = 4;
    pageTable[2] = 1;
    pageTable[3] = 7;
    pageTable[4] = 3;
    pageTable[5] = 5;
    pageTable[6] = 6;
    unsigned long pageNumber;
    unsigned long pageOffset;
    unsigned long physicalPageNumber;

    // Traverse all address
    int i;
    for(i = 0; i < fileSize/(sizeof(unsigned long)); i++) {
        printf("logical address %d = %#010lx\n", i, memAccesses[i]);
        // [%] [pad with 0] [length of 10] [long] [unsigned hex int, lowercase]
        pageNumber = memAccesses[i] >> 7; // 128 = 2^7
        pageOffset = memAccesses[i] & 0x7F; // 0111 1111
        physicalPageNumber = (pageTable[pageNumber] << 7) | pageOffset;
        memAccesses[i] = physicalPageNumber;
        printf("%d : %lx %lx %lx\n", i, pageNumber, pageOffset, physicalPageNumber);
    }

    writeData(argv[2], memAccesses, fileSize/(sizeof(unsigned long)));

    free(memAccesses); //free dynamically allocated memory
    printf("made it to the end!\n");
    return 0;
}