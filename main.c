//
// Created by Cem Yeniceri on 30/10/16.
//

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAXSIZE 100
struct entry{
    char firstName[MAXSIZE];
    char lastname[MAXSIZE];
    char number[MAXSIZE];
    struct entry *next;
};

typedef struct entry Entry;
typedef Entry *Entryptr;

void insert_something();
void insert(Entryptr);
void print_it_out();
void delete_something();
void search_something();
void printOneEntry(Entryptr);

Entryptr head = NULL;

int main()
{
    int choice;
    while(choice != 5)
    {

        printf("What would you like to do?\n");
        printf("1 - Insert something in the phonebook?\n");
        printf("2 - delete something from the phonebook?\n");
        printf("3 - Print out one of the contacts?\n");
        printf("4 - Return the element selected?\n");
        printf("5 - Nothing at all\n");
        printf("Enter 1 through 5: ");
        scanf("%d", &choice);


        switch(choice){
            case 1:
                insert_something();
                print_it_out();
                break;
            case 2:
                delete_something();
                break;
            case 3:
                print_it_out();
                break;
            case 4:
                search_something();
                break;
            default:
                printf("\nThank you for using the phonebook\n");
                return 0;
        }
    }
    return 0;
}


void insert_something()
{
/*
	this function creates a new entry by taking the name,surname and telephone number from the end user
	Then, it uses a new function insert() to add this new entry to the list
*/

    Entryptr newEntry = malloc(sizeof(Entryptr));

    char name[100], surname[100], gsm[100];

    printf("Enter name : \n");
    scanf("%s", name);

    printf("Enter surname : \n");
    scanf("%s", surname);

    printf("Enter gsm : \n");
    scanf("%s", gsm);

    strcpy(newEntry->firstName, name) ;
    strcpy(newEntry->lastname, surname);
    strcpy(newEntry->number, gsm);

    insert(newEntry);
}

void insert(Entryptr newnodeptr)
{
    /*
     * This function adds the given entry to the list.
     * It adds the entry by respecting the order of lastname. For example, there is celik, gunaydın and orman in the list ordered and new entry's surname
     * is konak, then the new order should be celik, gunaydın, konak and orman. Konak should be placed between gunaydın and orman.
     * You can use strcmp() function to check the string order.
     * Do not forget to create the list with the first entry.
     */

    if(head == NULL){
        head = newnodeptr;
    }else{
        Entryptr previous = head;
        Entryptr current = head->next;
        while (current != NULL && strcmp(newnodeptr->lastname, current->lastname) > 0)
        {
            previous = current;
            current = current->next;
        }
        previous->next = newnodeptr;
        newnodeptr->next = current;
    }
}

void print_it_out()
{
    /*
     * This function prints all the entry of the list to the screen
     * You should print lastname, firstname and number all together with one space inbetween
     */
    if(head == NULL){
        printf("List is empty..");
    }else{
        Entryptr temp = head;
        while (temp != NULL){
            printOneEntry(temp);
            temp = temp->next;
        }
    }
}

void printOneEntry(Entryptr nodeptr)
{
    /*
     * This function prints all the entry of the list to the screen
     * You should print lastname, firstname and number all together with one space inbetween
     */

    printf("%s %s %s \n", nodeptr->lastname, nodeptr->firstName, nodeptr->number);
}

void delete_something()
{
    /*
     * This function asks to the end user the lastname to be deleted and then finds the entry with this
     * lastname and removes this entry from the list.
     * Do not forget, you can have more than one entry with the same lastname. you should remove all of them from  the list
     */

    char surname[100];

    printf("Enter surname to delete: \n");
    scanf("%s", surname);

    Entryptr previous = head;
    Entryptr current = head->next;
    while (current != NULL && strcmp(surname, current->lastname) != 0)
    {
        previous = current;
        current = current->next;
    }
    if (current != head && current != NULL)
    {
        previous->next = current->next;
        free(current);
    }
}

void search_something()
{
    /*
     * This function asks from the end user the lastname to be found.
     * Then, it finds the first name and phonenumber of the entries with the given lastname and prints the result on the screen
     */

    char surname[100];
    int isFound = 0;

    printf("Enter surname to found: \n");
    scanf("%s", surname);

    Entryptr temp = head;
    while(temp != NULL){
        if(strcmp(temp->lastname, surname) == 0){
            isFound = 1;
            printOneEntry(temp);
            break;
        }
        temp = temp->next;
    }

    if(isFound == 0)
        printf("Given last name not found in the list");
}
