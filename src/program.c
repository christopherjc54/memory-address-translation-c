#include "program.h"

void runProgram(int _offsetSize, int _numEntriesPhysical, int _numEntriesPageTable, char* _inFileName, char* _outFileName) {
    int i;
    int pageFaults = 0;
    int missingPhyMemEntryCount = 0;

    //get input data
    unsigned long fileSize;
    unsigned long* memAccesses = readData(_inFileName, &fileSize);

    //setup physical memory
    phyMemStruct* phyMemTable = initFrameTable(_numEntriesPhysical); //7+1 for OS frame at beginning
    getFrame(phyMemTable, 0)->valid = false; //redundant, but needs to be false
    printTable(phyMemTable, "phyMemTable");
    printf("\n");

    //setup page table
    pageTableStruct* pageTable = initFrameTable(_numEntriesPageTable); //32

    //setup alternative page table for part1sequence
    /*pageTableStruct* pageTable = initFrameTable(0);
    addEntry(pageTable, 2);
    addEntry(pageTable, 4);
    addEntry(pageTable, 1);
    addEntry(pageTable, 7);
    addEntry(pageTable, 3);
    addEntry(pageTable, 5);
    addEntry(pageTable, 6);*/

    unsigned long pageNumber;
    unsigned long pageOffset;
    unsigned long physicalPageNumber;

    for(i = 0; i < fileSize/(sizeof(unsigned long)) /*&& i < 20*/; i++) {
        // printf("logical address %d = %#010lx\n", i, memAccesses[i]);
        // [%] [pad with 0] [length of 10] [long] [unsigned hex int, lowercase]
        if(memAccesses[i] != 0) { //WARNING: adding this changes MD5
            //separate page number and offset from input data
            pageNumber = memAccesses[i] >> _offsetSize; // 128 = 2^7
            pageOffset = memAccesses[i] & (0xFFFFFFFFFFFFFFFF >> 64 - _offsetSize); // 0111 1111
            printf("data %#010lx : pagenumber %d pageoffset %#lx\n", memAccesses[i], pageNumber, pageOffset);
            
            //get pageTableEntry
            pageTableEntryStruct* pageTableEntry = getFrame(pageTable, (int) pageNumber);
            printf("PTE: pageTable[%2d] is valid (%s)\n", getIndexByPointer(pageTable, pageTableEntry), (pageTableEntry->valid ? "true" : "false"));
            if(pageTableEntry == NULL || pageTableEntry->valid == false) { //page fault occured
                pageFaults++;
                pageTableEntry->frameNumber = (unsigned long) getIndexOfFrameNumber(phyMemTable, pageNumber);
                if(pageTableEntry->frameNumber == -1) { //if frame isn't in memory, replace physical memory using LRU
                    printf("couldn't find frameNumber %d in phyMemTable\n", pageNumber);
                    missingPhyMemEntryCount++;
                    //add misssing physical frame to pagetable => phyMemTable[indexOfLRU] = pageNumber
                    phyMemEntryStruct* phyMemEntry = getLRU(phyMemTable, getFrame(phyMemTable, 0));
                    phyMemEntry->frameNumber = pageNumber; 
                    phyMemEntry->valid = true;
                    //set new frameNumber in page table
                    unsigned long indexOfLRU = (unsigned long) getIndexByPointer(phyMemTable, phyMemEntry);
                    pageTableEntry->frameNumber = indexOfLRU;
                    printf("pageNumber %d is now at LRU'd phyMemTable[%d]\n", pageNumber, indexOfLRU);
                }
                pageTableEntry->valid = true;
                //invalidate exisitng PTE to same frame number (phyMem index)
                pageTableEntryStruct* invalidPTE = findFrame(pageTable, pageTableEntry->frameNumber, pageTableEntry);
                if(invalidPTE != NULL) {
                    invalidPTE->frameNumber = 0;
                    invalidPTE->valid = false;
                }
            }
            //update LRU values
            addOneTimeToAll(pageTable, NULL);
            pageTableEntry->timeSinceLastUse = 0;
            addOneTimeToAll(phyMemTable, getFrame(phyMemTable, 0));
            getFrame(phyMemTable, pageTableEntry->frameNumber)->timeSinceLastUse = 0;
            
            //do actual virtual to physical address conversion
            physicalPageNumber = (pageTableEntry->frameNumber << _offsetSize) | pageOffset;
            memAccesses[i] = physicalPageNumber;
            printf("%d : %#010lx %#010lx %#010lx\n", i+1, pageTableEntry->frameNumber, pageOffset, physicalPageNumber);
            //print tables (useful for debugging and seeing what's physically going on), set to "false" for easier to read console output
            if(true) {
                printf("\n");
                printTable(pageTable, "pageTable");
                printf("\n");
                printTable(phyMemTable, "phyMemTable");
            }
            printf("\n");
        }
    }

    writeData(_outFileName, memAccesses, fileSize/(sizeof(unsigned long)));
    free(memAccesses); //free dynamically allocated memory
    freeTable(pageTable);
    freeTable(phyMemTable);
    printf("Page faults: %d\n", pageFaults);
    printf("Physical memory replacements: %d\n", missingPhyMemEntryCount);
    printf("Number of entries in file: %d if on Linux, %d if on Windows\n", i, i/2);
    printf("MADE IT TO THE END WITHOUT CRASHING :D\n");
}