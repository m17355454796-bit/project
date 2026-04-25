#include"mystdio.h"
#include <stdio.h>
#include <string.h>
int main()
{   myFile* fp = myFopen("big.txt", "w");
    if(fp == NULL)
    {
        perror("myFopen");
        return 1;
    }

    char arr[3000];

    for(int i = 0; i < 3000; i++)
    {
        arr[i] = 'A';
    }

    myFwrite(arr, sizeof(char), 3000, fp);
    myFclose(fp);

    return 0;
}