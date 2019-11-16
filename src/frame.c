#include "frame.h"

frameStruct* initFrameTable(int numEntries) {
    frameStruct* frameTable = (frameStruct*) malloc(sizeof(frameStruct));
    frameTable->numEntries = 0;
    frameTable->firstEntry = NULL;
    frameTable->lastEntry = NULL;
    
    int i;
    bool firstRun = true;
    frameEntryStruct* tmp;
    for(i=0; i < numEntries && numEntries != 0; i++) {
        tmp = (frameEntryStruct*) malloc(sizeof(frameEntryStruct));
        tmp->frameNumber = 0;
        tmp->next = NULL;
        tmp->timeSinceLastUse = 0;
        tmp->valid = false;
        
        if(firstRun) {
            frameTable->firstEntry = tmp;
            firstRun = false;
        } else {
            frameTable->lastEntry->next = tmp;
        }
        frameTable->lastEntry = tmp;
        frameTable->numEntries++;
    }

    return frameTable;
}

void addEntry(frameStruct* frameTable, int frameNumber) {
    frameEntryStruct* entry = (frameEntryStruct*) malloc(sizeof(frameEntryStruct));
    entry->frameNumber = frameNumber;
    entry->next = NULL;
    entry->timeSinceLastUse = 0;
    entry->valid = true;
    
    if(frameTable->firstEntry == NULL) frameTable->firstEntry = entry;
    if(frameTable->lastEntry != NULL) frameTable->lastEntry->next = entry;
    frameTable->lastEntry = entry;
    frameTable->numEntries++;
}

frameEntryStruct* getLRU(frameStruct* frameTable, frameEntryStruct* exception) {
    if(frameTable->numEntries == 0) {
        printf("error: no entries in frameTable\n");
        return NULL;
    }
    int i;
    int numLRU = 0;
    frameEntryStruct* LRU = frameTable->firstEntry;
    frameEntryStruct* current = frameTable->firstEntry;
    for(i=0; i < frameTable->numEntries; i++) {
        if(current->timeSinceLastUse == 0 && current->valid == false && current != exception) break;
        if(current->timeSinceLastUse > numLRU && current != exception) {
            LRU = current;
            numLRU = current->timeSinceLastUse;
        }
        current = current->next;
    }
    if(LRU == frameTable->firstEntry && exception == frameTable->firstEntry) {
        if(frameTable->firstEntry->next == NULL) {
            printf("error: only entry that matched was also exception (no LRU found)\n");
            return NULL;
        } else {
            return frameTable->firstEntry->next;
        }
    }
    return LRU;
}

frameEntryStruct* getFrame(frameStruct* frameTable, int index) {
    if(frameTable->numEntries == 0) {
        printf("warning: no entries in frameTable\n");
        return NULL;
    }
    if(frameTable->numEntries < index + 1) {
        printf("error: index out of bounds\n");
        return NULL;
    }
    int i;
    frameEntryStruct* current = frameTable->firstEntry;
    for(i=0; i < index; i++) {
        current = current->next;
    }
    return current;
}

frameEntryStruct* findFrame(frameStruct* frameTable, unsigned long frameNumber, frameEntryStruct* exception) {
    if(frameTable->numEntries == 0) {
        printf("warning: no entries in frameTable\n");
        return NULL;
    }
    int i;
    frameEntryStruct* current = frameTable->firstEntry;
    for(i=0; i < frameTable->numEntries; i++) {
        if(current->frameNumber == frameNumber && current->valid == true && current != exception) return current;
        current = current->next;
    }
    printf("warning: frameNumber not found in frameTable\n");
    return NULL;
}

int getIndexOfFrameNumber(frameStruct* frameTable, unsigned long frameNumber) {
    if(frameTable->numEntries == 0) {
        printf("warning: no entries in frameTable\n");
        return -1;
    }
    int i;
    frameEntryStruct* current = frameTable->firstEntry;
    for(i=0; i < frameTable->numEntries; i++) {
        if(current->frameNumber == frameNumber && current->valid == true) return i;
        current = current->next;
    }
    printf("warning: index of frameNumber not found\n");
    return -1;
}

int getIndexByPointer(frameStruct* frameTable, frameEntryStruct* pointer) {
    if(frameTable->numEntries == 0) {
        printf("warning: no entries in frameTable\n");
        return -1;
    }
    frameEntryStruct* current = frameTable->firstEntry;
    int i = 0;
    while(current != NULL) {
        if(current == pointer) return i;
        current = current->next;
        i++;
    }
    printf("error: pointer not found in frameTable\n");
    return -1;
}

void addOneTimeToAll(frameStruct* frameTable, frameEntryStruct* exceptionReset) {
    if(frameTable->numEntries == 0) {
        printf("warning: no entries in frameTable\n");
        return;
    }
    int i;
    frameEntryStruct* current = frameTable->firstEntry;
    for(i=0; i < frameTable->numEntries; i++) {
        if(current != exceptionReset) current->timeSinceLastUse++;
        else current->timeSinceLastUse = 0;
        current = current->next;
    }
}

void freeTable(frameStruct* frameTable) {
    if(frameTable->numEntries != 0) {
        int i;
        frameEntryStruct* current = frameTable->firstEntry;
        frameEntryStruct* tmp;
        for(i=0; i < frameTable->numEntries; i++) {
            tmp = current;
            current = current->next;
            free(tmp);
        }
    }
    free(frameTable);
}

void printTable(frameStruct* frameTable, char* tableName) {
    if(frameTable->numEntries == 0) {
        printf("warning: no entries in frameTable\n");
        return;
    }
    printf("%s->numEntries = %d\n", (tableName == NULL ? "frameTable" : tableName), frameTable->numEntries);
    int i;
    frameEntryStruct* current = frameTable->firstEntry;
    for(i=0; i < frameTable->numEntries; i++) {
        printf("frame: %2d frameNumber: %2d timeSinceLastUse: %2d valid: %s\n", i, current->frameNumber, current->timeSinceLastUse, (current->valid ? "true" : "false"));
        current = current->next;
    }
}