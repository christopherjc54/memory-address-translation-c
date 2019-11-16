#ifndef _FRAME_H
#define _FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct frameEntryStruct frameEntryStruct;
struct frameEntryStruct {
    unsigned long frameNumber;
    bool valid;
    int timeSinceLastUse;
    frameEntryStruct* next;
};

typedef struct {
    int numEntries;
    frameEntryStruct* firstEntry;
    frameEntryStruct* lastEntry;
} frameStruct;

frameStruct* initFrameTable(int numEntries);
void addEntry(frameStruct* frameTable, int frameNumber);
frameEntryStruct* getLRU(frameStruct* frameTable, frameEntryStruct* exception);
frameEntryStruct* getFrame(frameStruct* frameTable, int index);
frameEntryStruct* findFrame(frameStruct* frameTable, unsigned long frameNumber, frameEntryStruct* exception);
int getIndexOfFrameNumber(frameStruct* frameTable, unsigned long frameNumber);
int getIndexByPointer(frameStruct* frameTable, frameEntryStruct* pointer);
void addOneTimeToAll(frameStruct* frameTable, frameEntryStruct* exceptionReset);
void freeTable(frameStruct* frameTable);
void printTable(frameStruct* frameTable, char* tableName);

#endif