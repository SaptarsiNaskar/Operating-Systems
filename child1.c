#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    int fd1, fd2, sz1, sz2, wr, size;


    
    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDWR);

    size = lseek(fd1, 0, SEEK_END);
    fd1 = open(argv[1], O_RDONLY);

    //printf("%d\n", size);

    char* c1 = (char*)calloc(6, sizeof(char));
    char* c2 = (char*)calloc(6, sizeof(char));

    sz1 = read(fd1 , c1, sizeof(c1));
    printf(" %d bytes were read from the source file!\n", sz1);
    c1[sz1] = '\0';
    printf("those bytes are as follows: %s\n\n", c1);


    wr = write(fd2, c1, sizeof(c1));


    printf("Copied content to destination file\n");




    close(fd1);
    close(fd2);



exit(100);
}