#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#define FILEMODE S_IRWXU | S_IRGRP | S_IROTH
#define MAX 150

int main(int argc,char *argv[])
{
    int fd, ret;
    size_t len_file, len;
    struct stat st;
    char *address;
    char buf[MAX];

    if (argc < 2)
    {
        printf("Usage a.out <filename>\n");
        return EXIT_FAILURE;
    }

    if ((fd = open(argv[1],O_RDWR | O_CREAT, FILEMODE)) < 0)
    {
        perror("Error in file opening");
        return EXIT_FAILURE;
    }

    if ((ret = fstat(fd,&st)) < 0)
    {
        perror("Error in fstat");
        return EXIT_FAILURE;
    }

    len_file = st.st_size;

    /*len_file having the total length of the file(fd).*/

    if ((address = mmap(NULL,len_file,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)) == MAP_FAILED)
    {
        perror("Error in mmap");
        return EXIT_FAILURE;
    }

    while ((fgets(buf,MAX,stdin)) != NULL)
    {
        len = len_file;
        len_file += strlen(buf);
        if (ftruncate(fd, len_file) != 0)
        {
            perror("Error extending file");
            return EXIT_FAILURE;
        }
        if ((address = mremap(address, len, len_file, MREMAP_MAYMOVE)) == MAP_FAILED)
        {
            perror("Error extending mapping");
            return EXIT_FAILURE;
        }
        memcpy(address+len, buf, len_file - len);
        printf( "Val:%s\n",address ) ; //Checking purpose
    }
    if((msync(address,len,MS_SYNC)) < 0)
        perror("Error in msync");

    if (munmap(address,len) == -1)
        perror("Error in munmap");

    if (close(fd))
        perror("Error in close");

    return 0;
}
