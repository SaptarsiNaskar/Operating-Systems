
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[]) {

    int fd, sz, fd1, sz1, wr, count, b;
    count = 0;
    b = 0;
    char* c = (char*)calloc(10000000, sizeof(char));
    char* c1 = (char*)calloc(10000000, sizeof(char));
    //char* c2 = (char*)calloc(100, sizeof(char));
    /*
    if(3 != argc) {
        printf("\n Usage :  \n");
        return 1;
    }
    */
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

    /*
    int b = 0;
    while(b < 10) {
        sz = read(fd, c, 1);
        if(c != ' ' && c != '\n') {
            if(c == '1') {
                c = 'A';
            }
            strcat(c1, c);

            write(fd1, c1, sizeof(c1));
        }

        if(strlen(c1) == 100) {
            strcat(c1, "zyz");
            write(fd1, c1, sizeof(c1));
            c1 = " ";
            }

        b++;
    }
    */

   sz = read(fd, c, 10000000);
   printf(" %d bytes were read from Source File.\n\n", sz);
    c[sz] = '\0';
    count = sz;
    printf("Those bytes are as follows: \n%s\n\n\n", c);

    errno = 0;
    if(-1 == sz) {
        printf("\n read() failed with error [%s]\n",strerror(errno));
        return 1;
    }

    
    //wr = write(fd1, c, 10000000);

    //printf("\n %d \n", count);

    printf("bytes in Destination files are as follows:\n\n");


    for (int i = 0; i < count; i ++ ) {
        if (c[i] != ' '  && c[i] != '\n') {
            if (c[i] == '1') {
                char* n = (char*)calloc(1, sizeof(char));
                n[0] = 'A';
                printf("A");
                wr = write(fd1, n, 1);
                b++;
            }
            else {
                char* m = (char*)calloc(1, sizeof(char));
                m[0] = c[i];
                printf("%c", c[i]);
                wr = write(fd1, m, 1);
                b++;
            }
        }
        else {
            //wr = write(fd1, c[i], 1);
        }
        /*
        for(int j = 1; j < (count / 100) + 1; j++) {
            if( j == count/100) {
                char* o = (char*)calloc(3, sizeof(char));
                o = "XYZ";
                wr = write(fd1, o, 3);
            }
            else {
                //7
            }
        }
        */
       if (b == 100) {
            char* o = (char*)calloc(3, sizeof(char));
            o = "XYZ";
            printf("XYZ");
            wr = write(fd1, o, 3);
            b = 0;
       }


    }

    printf("\n");
    

    

    /*
    sz1 = read(fd1, c1, 10000000);
    printf(" %d bytes were read from Destination File.\n\n", sz1);
    c1[sz1] = '\0';
    printf("Those bytes are as follows: \n%s\n\n", c1);

    errno = 0;
    if(-1 == sz1) {
        printf("\n read() failed with error [%s]\n",strerror(errno));
        return 1;
    }
    */


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