#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<stdlib.h>
typedef struct {
    
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void save(AddressBook *addressBook);
char Exit(AddressBook *addressBook);
void display(AddressBook *addressBook,int sno,int i);
void print_equalto();
int*searchContact(AddressBook*addressBook);
int checksno(int sno,int count);
int intialise_sno(int sno,int*arr);
int name_validation(AddressBook *addressBook,char * tempname);
int name_compare(AddressBook *addressBook,char * tempname);
int phone_validation(AddressBook*addressBook,char *tempphone);
int phone_valid(AddressBook*addressBook,char *tempphone);
void red();
void green();
void yellow();
void blue();
void cyan();

#endif
