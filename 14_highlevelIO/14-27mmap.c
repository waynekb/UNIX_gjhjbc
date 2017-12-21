#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


#define COPYINCY (1024*1024*1024)
#define FILE_MODE (S_IRUSR |S_IWUSR |S_IRGRP |S_IROTH)

int main(int argc, char *argv[])
{
    int fdin,fdout;
    void *src,*dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz =0;
    
    
    fdin=open(argv[1], O_RDONLY);
    fdout=open(argv[2], O_RDWR |O_CREAT|O_TRUNC, FILE_MODE);

    fstat(fdin,&sbuf);
    ftruncate(fdout, sbuf.st_size);

    while(fsz <sbuf.st_size)
    {
        if((sbuf.st_size - fsz) >COPYINCY)
            copysz = COPYINCY;
        else   
            copysz =sbuf.st_size -fsz;
        src = mmap(0,copysz,PROT_READ,MAP_SHARED,fdin,fsz);
        dst = mmap(0,copysz,PROT_READ | PROT_WRITE,MAP_SHARED,fdout, fsz);
        
        memcpy(dst,src,copysz);
        munmap(src,copysz);
        munmap(dst,copysz);
        fsz += copysz;
    }
    exit(0);
}
