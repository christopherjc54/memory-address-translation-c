#include "data.h"

//legacy c file function
unsigned long* getData(char* fileName, unsigned long* fileSize) {
    int fd_in;
    struct stat st;
    unsigned long* memAccesses;

    stat(fileName, &st);
    *fileSize = st.st_size;
    //allocate space for all addresses
    memAccesses = (unsigned long*) malloc((size_t) *fileSize);
    //use open and read
    fd_in = open(fileName, O_RDONLY);
    if(fd_in == -1) {
        fprintf(stderr, "fd is invalid, with error %d\n", strerror(errno));
        exit(-1);
    }
    //read all bytes from file at once without checking errors!!!
    read(fd_in, memAccesses, (int) *fileSize);
    close(fd_in);

    return memAccesses;
}

unsigned long* readData(char* fileName, unsigned long* fileSize) {
    char realPath[_MAX_PATH];
    if(realpath(fileName, realPath) == NULL) {
        printf("error: couldn't convert \"%s\" to a real path\n", fileName);
        exit(-1);
    }

    struct stat st;
    unsigned long* memAccesses;

    stat(realPath, &st);
    *fileSize = st.st_size;
    //allocate space for all addresses
    memAccesses = (unsigned long*) malloc((size_t) *fileSize);
    //use open and read
    FILE* inFile = fopen(realPath, "rb");
    if(!inFile) {
        printf("error: couldn't open %s\n", fileName);
        exit(-1);
    }
    fread(memAccesses, sizeof(*memAccesses), *fileSize/sizeof(*memAccesses), inFile);
    fclose(inFile);

    return memAccesses;
}

void writeData(char* fileName, unsigned long* data, int length) {
    //doesn't work on non-existing files :(
    /*char realPath[_MAX_PATH];
    if(realpath(fileName, realPath) == NULL) {
        printf("error: couldn't convert \"%s\" to a real path\n", fileName);
        exit(-1);
    }*/
    
    FILE* outFile = fopen(fileName, "wb");
    if(!outFile) {
        printf("error: couldn't open %s\n", fileName);
        exit(-1);
    }
    fwrite(data, sizeof(*data), length, outFile);
    fclose(outFile);
}