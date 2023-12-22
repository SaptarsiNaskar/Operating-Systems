#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/dir.h>

int search (char* file, char* dir) {
    //opens the passed dir and puts into dirPtr a pointer of type DIR named dirPtr
    DIR *dirPtr = opendir(dir);
    //dirent is part of types.h Library which contains directory info and reads the first file on the directory
    struct dirent * entry = readdir(dirPtr);
    //the loop will go on untill it finished reading all the info of the directory then the struct will point to Null
    //bool check = true; // checker boolean for message out put

    while(entry != NULL) {
        if( strlen(entry -> d_name) == strlen(file) && (strcmp(entry -> d_name, file) == 0)) {
            //printf("Found File, and exists!!");
            return 0;
        }
        entry = readdir(dirPtr);
    }

}

int main(int argc, char* argv[2]) {
    char* file = argv[1];
    char* dir = argv[2];

    if (search(file, dir) == 0) {
        printf("Found File, and exists!!");
    }
    else {
        printf("Not Found!!");
    }

}