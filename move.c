
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[]) {

    int fd, sz, fd1, sz1, wr;
    char* c = (char*)calloc(10000000, sizeof(char));
    char* c1 = (char*)calloc(10000000, sizeof(char));

    if(3 != argc) {
        printf("\n Usage :  \n");
        return 1;
    }
    errno = 0;
    fd = open(argv[1],O_RDONLY);
    if(-1 == fd) {
        printf("\n open() failed with error [%s]\n",strerror(errno));
        return 1;
    } 
    else {
        printf("\n Source File Open() Successful\n\n");
        /* open() succeeded, now one can do read operations on the file opened
        since we opened it in read-only mode. Also once done with processing,
        the file needs to be closed.*/
    }

    errno = 0;
    fd1 = open(argv[2],O_RDWR);
    if(-1 == fd1) {
        printf("\n open() failed with error [%s]\n",strerror(errno));
        return 1;
    } 
    else {
        printf("\n Destination File Open() Successful\n\n");
        /* open() succeeded, now one can do read operations on the file opened
        since we opened it in read-only mode. Also once done with processing,
        the file needs to be closed.*/
    }




    sz = read(fd, c, 10000000);
    printf(" %d bytes were read from Source File.\n\n", sz);
    c[sz] = '\0';
    printf("Those bytes are as follows: \n%s\n\n", c);

    errno = 0;
    if(-1 == sz) {
        printf("\n read() failed with error [%s]\n",strerror(errno));
        return 1;
    } 


    wr = write(fd1, c, sz);


    sz1 = read(fd1, c1, sz);
    printf(" %d bytes were read from Destination File.\n\n", sz1);
    c1[sz1] = '\0';
    printf("Those bytes are as follows: \n%s\n\n", c1);

    errno = 0;
    if(-1 == sz1) {
        printf("\n read() failed with error [%s]\n",strerror(errno));
        return 1;
    }


    if (close(fd) < 0) {
        perror("c1");
        exit(1);
    }

    if (close(fd1) < 0) {
        perror("c1");
        exit(1);
        }
    
    printf("\nclosed the files.\n");

return 0;
}