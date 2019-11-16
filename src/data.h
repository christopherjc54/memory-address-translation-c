#ifndef _DATA_H
#define _DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

#ifdef _WIN32
#define realpath(N, R) _fullpath(R, N, _MAX_PATH)
#else
#define _MAX_PATH PATH_MAX-1
#endif

unsigned long* getData(char* fileName, unsigned long* fileSize); //legacy c file function

unsigned long* readData(char* fileName, unsigned long* fileSize);
void writeData(char* fileName, unsigned long* data, int length);

#endif