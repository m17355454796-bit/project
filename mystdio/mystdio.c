#include"mystdio.h"
myFile * myFopen(const char *path, const char *mode)
{
    if(path==NULL||mode==NULL)
    return NULL;
    myFile* myfile=(myFile*)malloc(sizeof(myFile));
    if(myfile==NULL)
    {
        return NULL;
    }
    int fd=-1;
    if(strcmp(mode,"w")==0)
    {
        fd=open(path,O_WRONLY|O_CREAT|O_TRUNC,0666);
    }else if(strcmp(mode,"r")==0)
    {
        fd=open(path,O_RDONLY);
    }else if(strcmp(mode,"a")==0)
    {
        fd=open(path,O_APPEND|O_CREAT|O_WRONLY,0666);
    }
    if(fd<0)
    {
        free(myfile);
        return NULL;
    }else{
        myfile->fd=fd;
        myfile->size=0;
        myfile->capacity=1024;
        myfile->mode=FULL_BUFFER;
    }
    return myfile;
}
int myFclose(myFile *fp)
{
    if(fp==NULL)
    return -1;
    myFflush(fp);
    int ret=close(fp->fd);
    free(fp);
    if(ret<0)return -1;
    return ret;
}

int myFwrite(const void *arr, size_t size, size_t nmemb, myFile* fp)
{
   if(arr==NULL||fp==NULL)
    {
        return -1;
    }
    const char*data=(const char*)arr;
    size_t total_size=size*nmemb;
    int num=0;
    while(num<total_size)
    {
        if(fp->capacity==fp->size)
        {
            if(myFflush(fp)<0)
            {
                return -1;
            }
        }
        fp->outbuffer[fp->size++]=data[num++];
    }
    return nmemb;
}

int myFflush(myFile *fp)
{
    if(fp==NULL)return -1;
    if(fp->size==0)return 0;
    int ret=write(fp->fd,fp->outbuffer,fp->size);
    if(ret<0)
    return -1;
    fp->size=0;
    return 0;
}
