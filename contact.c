#include "contact.h"
/* Functions to set different colors for the output text */
void red () {
  printf("\033[1;31m");
}
void green()
{
    printf("\033[0;32m");
}
void yellow (){
  printf("\033[1;33m");
}

void blue ()
{
    printf("\033[0;34m ");
}

void cyan()
{
    printf("\033[0;36m ");
}
/* Function to reset text color to default */
void reset () {
  printf("\033[0m");
}
/* Function to print a line of "=" characters */
void print_equalto(){
        for(int i=0;i<(MAX_CONTACTS + 10);i++)
        {
        printf("=");
        }  
}
/* Function to print column headers for contact details*/
void print_info()
{
cyan();
printf(": %-10s: %-30s: %-30s: %-30s\n","S.No","Name","Phone No","Email ID");
reset();
}
/* Function to display a single contact's details */
void display(AddressBook *addressBook,int sno,int i)
{
        printf(": %-10d: %-30s: %-30s: %-30s\n",sno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);   
}
/* Function to check if a serial number is valid */
int checksno(int sno,int count)
{
        if (sno < 1 || sno > count) 
        {
        return 1;
        }
        return 0;
}
/* Function to initialize the serial number from an array */
int initialise_sno(int sno,int*arr)
{
        for(int i=0;i<=sno;i++)
        {
        if(sno==i)
        {
        sno=arr[i];
        break;
        }
        }
        return sno;
}
/* Fuction to Exit */
char Exit(AddressBook*addressBook)
{
        int ch;
        printf("Select Option\n1.Save\n2.Exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
                case 1:
                        save(addressBook);      // Save contacts
                        break;
                case 2:
                        green();
                        printf(">>>>>Exit Successfully<<<<<\n");
                        reset();
                        return 'n';             // Return to exit
        }
}
/* Function to save the contact list to a file */
void save(AddressBook*addressBook)
{
        FILE *fp = fopen("contacts.txt", "w");
        for (int count = 0; count <addressBook->contactCount; count++)
        {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[count].name,addressBook->contacts[count].phone,addressBook->contacts[count].email);
        }
        green();
        printf(">>>>> Contacts Saved Successfully <<<<<\n");
        reset();
        fclose(fp);                             // Close the file
}
/* Function to initialize the contact list from a file */
void initialize(AddressBook *addressBook) 
{
        addressBook->contactCount = 0;
        FILE *fp = fopen("contacts.txt", "r");  // Open file for reading 
        char temp[500];                         // Buffer for file reading
        while (fgets(temp, sizeof(temp), fp))   // Read each line from file
         {
                temp[strcspn(temp,"\n")]=0;
                char *token = strtok(temp, ",");
        if (token != NULL) {                    // get token for name 
            strcpy(addressBook->contacts[addressBook->contactCount].name, token);
        }
        token = strtok(NULL, ",");              // Get next token for phone
        if (token != NULL) {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, token);
        }
        token = strtok(NULL, ",");              // Get next token for email
        if (token != NULL) {
            strcpy(addressBook->contacts[addressBook->contactCount].email, token);
        }
        addressBook->contactCount++;            // Increment contact count
    }
        fclose(fp);                             // closing the file
}
/* Function to validate that the name contains only letters and spaces*/
int name_validation(AddressBook *addressBook,char *tempname)
{
        int res=0;
        for(int i=0;tempname[i]!='\0';i++)
        {
        if((tempname[i]>='a' && tempname[i]<='z')||(tempname[i]>='A' && tempname[i]<='Z')||(tempname[i]== ' '))
        {
                res=1;         // Valid character
        }
        else
        {
        res=0;                 // Invalid character
        break;
        }
        }
        return res;
}
/*  Function to check if the name already exists in the contact list*/
int name_compare(AddressBook *addressBook,char * tempname)
{
        int res=1;
        for(int i=0;i<addressBook->contactCount;i++)
        {
        if(strcmp(addressBook->contacts[i].name,tempname)==0)
        {
                res=0;       // Name already exists
                break;
        }
        }
        return res;
}
/* Function to validate that the phone number contains only digit*/
int phone_validation(AddressBook*addressBook,char *tempphone)
{
        int res = 1;                    
        for (int i = 0; tempphone[i]; i++) {
        if (!(tempphone[i] >= '0' && tempphone[i] <= '9')) {
            res = 0;        // Invalid character found
            break;
        }
        }
    return res;
}
/* Function to check if the phone number already exists in the contact list */
int phone_valid(AddressBook *addressBook, char *tempphone) {
    int res = 1; 
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, tempphone) == 0) {
            res = 0; // Phone number already exists
            break;
        }
    }
    return res;
}
/* Function to Create a New Contact */
void createContact(AddressBook *addressBook) 
{
        char tempname[50];
        char tempphone[20];
        char tempemail[50];
        yellow();
        printf("##### Address Book #####\n");
        printf("##### Add Contact: #####\n");
        reset();
name:
        blue();
        printf("\nEnter the name : ");          // Input name from user
        reset();
        scanf(" %[^\n]",tempname);
        int res=name_validation(addressBook,tempname);
        if(res==0)
        {
        red();
        printf("..... Please Enter Only Alphabets in Name .....\n");
        reset();
        goto name;      // If invalid, go back to name input
        }
        res=name_compare(addressBook,tempname);        
        if(res==0)
        {
        red();
        printf("..... Name is Already present .....\n");
        reset();
        goto name;       // If name already exists, re-enter
        }  
phone:
        blue();
        printf("\nEnter the ph.no: ");
        reset();
        scanf(" %[^\n]",tempphone);
        int i=0;
        res=phone_validation(addressBook,tempphone);
        if(res==0)
        {
        red();
        printf("..... Number consists of characters .....");
        reset();
        goto phone;     // If invalid, go back to phone input
        }
        i=strlen(tempphone);
        if(i<10)
        {
        red();
        printf("*****  Invalid Phone number  ***** \n");
        printf("..... Number consists of Less Digits .....\n");
        reset();
        goto phone;     // If less than 10 digits, re-enter
        }
        else if(i>10)
        {
        red();
        printf("*****  Invalid Phone number  ***** \n");
        printf("..... Number consists of More Digits .....\n");
        reset();
        goto phone;     // If more than 10 digits, re-enter
        }
        if(i==10)
        {
        res=phone_valid(addressBook,tempphone);
        if(res==0)
        {
        red();
        printf("..... Number is already present .....\n");
        reset();
        goto phone;     // If phone number already exists, re-enter
        }
        } 
email:
        blue();
        printf("\nEnter the e.mail: ");
        reset();
        scanf(" %[^\n]",tempemail);     // Input email
        if(strrchr(tempemail,'@')==NULL)
        {
        red();
        printf("*****   Invalid email format    *****\n");
        printf("..... Email doesn't consits \"@\" .....\n");
        reset();
        goto email;     // If @ not present in email, re-enter
        }
        if(strstr(tempemail,".com")==NULL)
        {
        red();
        printf("*****   Invalid email format    *****\n");
        printf("..... Email doesn't consists \".com\" .....\n");
        reset();
        goto email;     // If .com not present in email, re-enter
        }
        if(strrchr(tempemail,'@')+1*sizeof(char)==strstr(tempemail,".com"))
        {
        red();
        printf("..... Email doesn't consists any character b/w @ and .com .....\n");
        reset();
        goto email;     // If invalid email, re-enter
        }
        for(int i=0;i<addressBook->contactCount;i++)
        {
        if(strcmp(addressBook->contacts[i].email,tempemail)==0)
        {
        red();
        printf("..... Email is Already Present .....\n");
        reset();
        goto email;     // If email already exists, re-enter
        }
        }
        /* Printing the details of the new contact*/
        blue();
        printf("\nName :");
        reset();
        printf("%s",tempname);
        blue();
        printf("\nPhone :");
        reset();
        printf("%s",tempphone);
        blue();
        printf("\nEmail :");
        reset();
        printf("%s",tempemail);
        /* Storing the new contact details */
        strcpy(addressBook->contacts[addressBook->contactCount].name,tempname);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,tempphone);
        strcpy(addressBook->contacts[addressBook->contactCount].email,tempemail);
        addressBook->contactCount++;
        green();
        printf("\n>>>>> Contact added successfully <<<<<\n");
        reset();        
}
/* Function to search a contact present in the File*/
int *searchContact(AddressBook*addressBook)
{
        char ch;
        int temp,ex=1;
        int count=0;
        static int arr[10];
        arr[0]=0;       
        yellow();
        printf("##### Address Book ######\n");
        printf("##### Search Contact by: \n");
        reset();
        printf("0. Back\n");
        printf("1. Name\n");
        printf("2. Phone No\n");
        printf("3. Email ID\n");
        printf("4. Serial No:\n");
        blue();
        printf("Please Select an option :");
        reset();
        scanf(" %c",&ch);
        switch(ch){
        case '0':
        {
                green();
                printf(">>>>> Exit Successfully <<<<<\n");
                reset();
                arr[0]=1;       // Exit and return empty array
                return arr;
                break;
        }
        case '1':
        {
                blue();
                printf("\nEnter the name : ");
                reset();
                scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
                print_equalto();
                printf("\n");
                print_info();
                print_equalto();
                printf("\n");
                int sno=1;
                count=0;
                for(int i=0;i<addressBook->contactCount;i++)
                {   
                if(strstr(addressBook->contacts[i].name,addressBook->contacts[addressBook->contactCount].name)!=NULL)
                {
                count++;
                arr[sno]=i+1;
                display(addressBook,sno++,i);   // Display contact details
                }
                }
                print_equalto();
                printf("\n");
                if(!count){
                red();
                printf("..... Name Not Found .....\n");
                reset();
                arr[0]=1;
                getchar();
                }
                break;
        }
        case '2':
        {
                count=0;
                blue();
                printf("Enter the phone no :\n");
                reset();
                scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].phone);
                print_equalto();
                printf("\n");
                print_info();
                print_equalto();
                printf("\n");
                for(int i=0;i<addressBook->contactCount;i++)
                {
                if(strstr(addressBook->contacts[i].phone,addressBook->contacts[addressBook->contactCount].phone)!=NULL)
                {
                  arr[++count]=i+1;
                display(addressBook,count,i);   // Display contact details
                }
                }
                print_equalto();
                printf("\n");
                if(!count){
                red();
                printf("..... Phone Number not Found .....\n");
                reset();
                arr[0]=1;
                }
                break;
        }     
        case '3':
        {
                count=0;
                blue();
                printf("Enter the email:\n");
                reset();
                scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].email);
                print_equalto();
                printf("\n");
                yellow();
                print_info();
                reset();
                print_equalto();
                printf("\n");
               for(int i=0;i<addressBook->contactCount;i++)
               {
                if(strstr(addressBook->contacts[i].email,addressBook->contacts[addressBook->contactCount].email)!=NULL)
                {
                arr[++count]=i+1;
                display(addressBook,count,i);           // Display contact details
                }
                }
                print_equalto();
                printf("\n");
                if(!count){
                red();
                printf("..... Email not Found .....\n");
                reset();
                arr[0]=1;
                }
                break; 
        }
        case '4':
        {
                blue();
                printf("Enter the serial number : ");
                reset();
                scanf("%d",&temp);
                /* Validating the serial number*/
                if (temp < 1 || temp > addressBook->contactCount) 
                {
                red();
                printf("..... Invalid serial number! .....\n");
                reset();
                arr[0]=1;
                }
                else{
                int count=1;
                print_equalto();
                printf("\n");
                yellow();
                print_info();
                reset();
                print_equalto();
                printf("\n");
                display(addressBook,count,temp-1);      // Display contact details
                print_equalto();
                printf("\n");
                }
                break;
        }
        default :
        {
                red();
                printf("..... Invalid Choice ....\n");
                printf("..... Please Try Again .....\n");
                reset();
                break;
        }
        }
        return arr;
}
/* Function to Edit the contact details */
void editContact(AddressBook *addressBook) 
{
        int sno,res=1;
        char ch;
        char tempname[50];
        char tempphone[20];
        char tempemail[50];
        /* Searching and printing the list of contact details*/
        int *arr= searchContact(addressBook);
        /* Checking the array consists of atleast one contact details or not*/
        if(arr[0]==1)
        {
                res=0;
        }
        else
        {
        sno:
        blue();
        printf("Enter the serial no to edit contact: ");
        reset();
        scanf("%d",&sno);
        }
       if(res==1)
       {
        /* Checking user given serial number is valid or not*/
        int out=checksno(sno,addressBook->contactCount);
        if(out) 
        {
                red();
                printf("..... Invalid serial number! .....\n");
                reset();
                goto sno;
        }
       
       /* Assigning the original index value of the contact to the "sno"*/
       sno=initialise_sno(sno,arr);
        yellow();
        printf("##### Address Book #####\n");
        printf("##### Edit Contact:\n");
        reset();
        blue();
        printf("\n0. Back\n");
        /* printing the contact details of the particular contact which is to be edited*/
        printf("1. Name: ");
        reset();
        printf("%s",addressBook->contacts[sno-1].name);
        blue();
        printf("\n2. ph.no: ");
        reset();
        printf("%s",addressBook->contacts[sno-1].phone);
        blue();
        printf("\n3. e.id: ");
        reset();
        printf("%s",addressBook->contacts[sno-1].email);
        blue();
        printf("\nPlease select an option to Edit: ");
        reset();
        scanf(" %c",&ch);
        switch(ch)
        {
        case '0':
        green();
        printf(">>>>> Exit successfully <<<<<\n");
        reset();
        break;
        case '1':
                name:
                blue();
                printf("\nEnter the name : ");
                reset();
                scanf(" %[^\n]",tempname);
                /* Checking the new name consists of alphabets */
                int ret=name_validation(addressBook,tempname);
                if(ret==0)
                {
                red();
                printf("..... Please Enter Only Alphabets in Name .....\n");
                reset();
                goto name;
                }
                /* Checking the new name is already present or not*/
                res=name_compare(addressBook,tempname);
                if(res==0)
                {
                red();
                printf("..... Name is Already present .....\n");
                reset();
                goto name;
                }
                /* Copying the new name to the existed name*/
                strcpy(addressBook->contacts[sno-1].name,tempname);
                ch='0';
                green();
                printf("..... Edited the name Successfully .....\n");
                reset();
                break;
                               
        case '2':
                phone:
                blue();
                printf("\nEnter the ph.no: ");
                reset();
                scanf(" %[^\n]",tempphone);
                int i=0;
                /* Checking the new phone number consists of characters */
                res=phone_validation(addressBook,tempphone);
                if(res==0)
                {
                red();
                printf("..... Number consists of characters .....");
                reset();
                goto phone;
                }
                i=strlen(tempphone);
                /* Checking the new phone number consists of 10 digits or not*/
                if(i<10)
                {
                red();
                printf("*****  Invalid Phone number  ***** \n");
                printf("..... Number consists of Less Digits .....\n");
                reset();
                goto phone;
                }
                else if(i>10)
                {
                red();
                printf("*****  Invalid Phone number  ***** \n");
                printf("..... Number consists of More Digits .....\n");
                reset();
                goto phone;
                }
                if(i==10)
                {
                /* Checking the phone number is already exists or not*/
                res=phone_valid(addressBook,tempphone);
                if(res==0)
                {
                red();
                printf("..... Number is already present .....\n");
                reset();
                goto phone;
                }
                }
                /* Copying the new phone number to the existing phone number*/
                strcpy(addressBook->contacts[sno-1].phone,tempphone);
                ch='0';
                green();
                printf(">>>>> Edited the phone number Successfully <<<<<\n");
                reset();
                break;
        case '3':
                char *res,*out;
                email:
                blue();
                printf("\nEnter the e.mail: ");
                reset();
                scanf(" %[^\n]",tempemail);
                /* Checking the new email consits "@"*/
                if(strrchr(tempemail,'@')==NULL)
                {
                red();
                printf("*****   Invalid email format    *****\n");
                printf("..... Email doesn't consits \"@\" .....\n");
                reset();
                goto email;
                }
                /* Checking the new email consits of ".com"*/
                if(strstr(tempemail,".com")==NULL)
                {
                red();
                printf("*****   Invalid email format    *****\n");
                printf("..... Email doesn't consists \".com\" .....\n");
                reset();
                goto email;
                }
                /* Checking the new email consists of character in b/w "@" and ".com"*/
                if(strrchr(tempemail,'@')+1==strstr(tempemail,".com"))
                {
                red();
                printf("..... Email doesn't consists any character b/w @ and .com .....\n");
                reset();
                goto email;
                }
                for(int i=0;i<addressBook->contactCount;i++)
                {
                /* Checking the email is already existed or not*/
                if(strcmp(addressBook->contacts[i].email,tempemail)==0)
                {
                red();
                printf("..... Email is Already Present .....\n");
                reset();
                goto email;
                }
                }
                /* Copying the new email to the existing exixting email*/
                strcpy(addressBook->contacts[sno-1].email,tempemail);
                green();
                printf(">>>>> Edited the email Successfully <<<<<\n");
                reset();
                break;
        default:
                red();
                printf("...... Invalid choice! Please try again .....\n");
                reset();
                break;
        }
}
}
/* Function to Delete the contact*/
void deleteContact(AddressBook *addressBook) 
{
        int sno,i,res=1;
        /* searching the user given contact*/
        int *arr= searchContact(addressBook);
        if(arr[1]==0)
        {
                res=0;
        }
        else
        {
        blue();
        printf("Enter the serial no to edit contact: ");
        reset();
        scanf("%d",&sno);
        }
        if(res==1)
        {
        /* Checking the serail number is valid or not */
        int out=checksno(sno,addressBook->contactCount);
        if(out) 
        {
        red();
        printf("..... Invalid serial number! .....\n");
        reset();
        res=0;
        }
        /* Assigning the original index value to the sno*/
        sno=initialise_sno(sno,arr);
        /* Printing the contact details */
        blue();
        printf("1. Name: ");
        reset();
        printf("%s",addressBook->contacts[sno-1].name);
        blue();
        printf("\n2. ph.no: ");
        reset();
        printf("%s",addressBook->contacts[sno-1].phone);
        blue();
        printf("\n3. e.id: ");
        reset();
        printf("%s",addressBook->contacts[sno-1].email);
        if(res==1)
        {
        /* Replacing the next contact details */
        for(i=sno-1;i<addressBook->contactCount-1;i++){
        addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
        green();
        printf("\n>>>>>> Contact Deleted Successfully <<<<<\n");
        reset();
        }
        }        
}
/* Function to print all contact details that are present in the structure array*/
void listContacts(AddressBook *addressBook) 
{
        print_equalto();
        printf("\n");
        print_info();
        print_equalto();
        printf("\n");
        /* printing all contactact that are present in structure array*/
        for(int i=0;i<addressBook->contactCount;i++)
        {
        printf(": %-10d: %-30s: %-30s: %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        print_equalto();
        printf("\n");
}
