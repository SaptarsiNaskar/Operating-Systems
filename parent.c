#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {

    char* file1 = "/Users/sap/Desktop/Fall 2023/CSC 332 Operating Systems Lab/HW3/child1";
    char* file2 = "/Users/sap/Desktop/Fall 2023/CSC 332 Operating Systems Lab/HW3/child2";
    //char* file3 = "/bin/date";

    //char* arg1 = "source.txt";
    //char* arg2 = "destination.txt";
    //char* arg3 = "linkedListNodes.txt";

    char* arg1 = argv[1];
    char* arg2 = argv[2];
    char* arg3 = argv[3];
    //char* arg4 = "date";




    // Checking for mac OS with 
    // __APPLE__ macro 
    #ifdef __APPLE__ 
    printf("\nHey it seems that you"
           "are working on a Mac OS.\n"); 
    char* file3 = "/bin/date";
  
    // Checking for linux OS with 
    // __linux__ macro 
    #elif __linux__ 
    printf("Hey it seems that you"
           "are working on a Linux OS.\n"); 
    char* file3 = "/usr/bin/date";
    #endif 
    printf("\n\n");
     




    pid_t pid;
    int pid1, pid2, pid3;

    for(int i = 0; i < 3; i++) {

        pid = fork();

        if(i == 0) {
            pid1 = (int)pid;
        }
        if(i == 1) {
            pid1 = (int)pid;
        }
        if(i == 2) {
            pid1 = (int)pid;
        }


        if(i == 0 && pid == 0) {
            printf("1st Child\n");

            sleep(10);

            execl(file1, file1, arg1, arg2, NULL);
            
            //printf("\n!**********\n");
            //exit(100);

        }
        if(i == 1 && pid == 0) {
            printf("2nd Child\n");
            execl(file2, file2, arg3, NULL);
            //exit(200);
        }
        if(i == 2 && pid == 0) {
            printf("3rd Child\n");
            execl(file3, file3, NULL);
            //exit(300);
        }
        
    }



    waitpid(pid1, NULL, 0);





}