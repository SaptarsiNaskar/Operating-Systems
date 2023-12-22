#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[]) {

char* filepath = argv[1];
int returnval, read, write, execute;

// Check file existence
returnval = access (filepath, F_OK);

if (returnval == 0) {
    printf ("\n %s exists\n", filepath);

    returnval = access (filepath, R_OK);
    if (returnval == 0) {
        printf ("\n %s has Read access \n", filepath);
    }
    else {
        if (errno == EACCES) {
            printf ("\n %s does not have Read access \n", filepath);
        }
        else if (errno == ENOENT) {
            printf ("\n %s is not accessible \n", filepath);
        }
    }

    returnval = access (filepath, W_OK);
    if (returnval == 0) {
        printf ("\n %s has Write access \n", filepath);
    }
    else {
        if (errno == EACCES) {
            printf ("\n %s does not have Write access \n", filepath);
        }
        else if (errno == ENOENT) {
            printf ("\n %s is not accessible \n", filepath);
        }
    }
}
else {
    if (errno == ENOENT) {
    printf ("\n %s does not exist\n", filepath);
}

else if (errno == EACCES) {
    printf ("\n %s is not accessible\n", filepath); return 0;
}
}

// Check read access ... // Check write access ... return 0;
//Read Aceess
}