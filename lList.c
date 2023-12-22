#include<stdlib.h>
#include<stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

void insertAtTheBeginning(int data) {
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    
    newNode->data = data;
    
    newNode->next = head;
    newNode->prev = NULL;

    if(head != NULL) {
        head->prev = newNode;
    }

    head = newNode;
}
void insertAtTheEnd(int data) {
    struct node *temp = head;
    if(temp != NULL) {
        while(temp->next != NULL) {
            temp = temp->next;
    }

        struct node *newNode;
        newNode = malloc(sizeof(struct node));
    
        newNode->data = data;
    
        newNode->next = NULL;

        temp->next = newNode;
        newNode->prev = temp;
    }
    else {
        insertAtTheBeginning(data);
    }
    
    

}

void insertAfter(int data, int previousData) {
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    struct node *temp = head;

    while(temp != NULL && temp->data != previousData) {
        temp = temp->next;
    }
    //For Entering at the beggining and in middle
    if(temp->next != NULL && temp != NULL) {
        newNode->next = temp->next;
        temp->next->prev = newNode;
        newNode->prev = temp;
        temp->next = newNode;
    }
    //For Entering at the end
    else if(temp->next == NULL && temp != NULL) {
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void deleteNode(int data) {
    struct node *temp = head;

    while(temp != NULL && temp->data != data) {
        temp = temp->next;
    }

    if(temp->next != NULL && temp->prev != NULL) {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }

    else if(temp->prev == NULL) {
        head = temp->next;
        temp->next->prev = NULL;
        free(temp);
    }
    else if(temp->next == NULL) {
        temp->prev->next = NULL;
        free(temp);
    }

}

void printList() {
    struct node *temp = head;

    while(temp != NULL) {
        printf("%d ",temp->data);
        temp = temp->next;
    }
}




int main(int argc, char* argv[]) {

   
   int fd, sz, wr;
   int userPref, userData, after;
   char* c = (char*)calloc(10000000, sizeof(char));
   //char str[1000];

    //Opend Data file
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
    

    
    //Read from data file tp create initial Linked List
    sz = read(fd, c, 10000000);
    printf(" %d bytes were read from Source File.\n\n", sz);
    c[sz] = '\0';
    //count = sz;
    printf(" Those bytes are as follows: \n %s\n", c);

    errno = 0;
    if(-1 == sz) {
        printf("\n read() failed with error [%s]\n",strerror(errno));
        return 1;
    }

   //Populate Linked List
    const char* stri = &c[0];
    int j = strlen(stri);
    char str[j];
    strcpy(str, stri);
    wr = 0;
    for(int i = 0; i < strlen(str); i++) {
        wr++;
        if(str[i] == ' ') {
            for(int j = 0; j < wr; j++) {
                str[j] = ' ';
            }
        }
        else if(str[i + 1] == ' ' || str[i + 1] == NULL) {
            insertAtTheEnd(atoi(str));
        }
    }

    
    
    

    
    //User Interface
    userPref = 10;

    printf("\n  The Linked List from the file is:\n");
    printList();
    printf("\n to insert a new node press 1, to insert a new node after a given node press 2, to delete a node press 3, to exit press 0.\n");

    while(userPref != 0) {

        scanf("%d", &userPref);

        switch(userPref) {
            case 1 :
            printf("\n Enter the number to be inserted at the beginning\n");
            scanf("%d", &userData);
            insertAtTheBeginning(userData);
            printf("\n Updated Linked List: \n");
            printList();
            printf("\n to insert a new node press 1, to insert a new node after a given node press 2, to delete a node press 3, to exit press 0.\n");

            break;

            case 2 :
            printf("\n Enter the number to be inserted\n");
            scanf("%d", &userData);
            printf("\n Enter the number for which the data will be enterned after\n");
            scanf("%d", &after);
            insertAfter(userData, after);
            printf("\n Updated Linked List: \n");
            printList();
            printf("\n to insert a new node press 1, to insert a new node after a given node press 2, to delete a node press 3, to exit press 0.\n");

            break;

            case 3 :
            printf("\n Enter the number to be deleted\n");
            scanf("%d", &userData);
            deleteNode(userData);
            printf("\n Updated Linked List: \n");
            printList();
            printf("\n to insert a new node press 1, to insert a new node after a given node press 2, to delete a node press 3, to exit press 0.\n");

            break;

            case 0:
            printf("\n Exiting Interface\n");
            
            break;

            default:
            printf("\n Wrong Input\n");
        }
        

    }
    




    //Closed Data file
    if (close(fd) < 0) {
        perror("c1");
        exit(1);
    }
    printf("\n closed the files.\n");


}