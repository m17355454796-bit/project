#pragma once
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#define NO_BUFFER 0
#define LINE_BUFFER 1
#define FULL_BUFFER 2
typedef struct{
    int fd;
    int mode;
    char outbuffer[1024];
    unsigned int size;
    unsigned int capacity;
}myFile;
myFile* myFopen(const char* path, const char* mode);
int myFclose(myFile* fp);
int myFwrite(const void* arr, size_t size, size_t nmemb, myFile* fp);
int myFflush(myFile* fp);