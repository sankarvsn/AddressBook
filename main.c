#include "contact.h"

int main()
{
    //all function calls should be inside the main 
    AddressBook addressBook;
    initialize(&addressBook);
    char ch;
    do{
    
    printf("##### Address Book :\n");
    printf("Menu: \n");
    printf("0.Exit\n1.create contact\n2.search contact\n3.edit contact\n4.delete contact\n5.list contact\n6.Save\n");
    printf("Enter the choice:\n");
    scanf(" %c",&ch);
    switch(ch)
    {
        case '0':
                ch=Exit(&addressBook);
                break;
        case '1':
                createContact(&addressBook);
                break;
        case '2':
                searchContact(&addressBook);
                break;
        case '3':
                editContact(&addressBook);
                break;
        case '4':
                deleteContact(&addressBook);
                break;
        case '5':
                listContacts(&addressBook);
                break;
        case '6':
                save(&addressBook);
                break;
        default:
                printf("Invalid Choice\n");
                break;
    }
    }while(ch!='n');
}