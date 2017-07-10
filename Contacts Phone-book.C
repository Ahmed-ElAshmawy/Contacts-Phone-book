#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <string.h>


//**************************************************
//Struct Declarations
//**************************************************

struct contact
{
    char name[50];
    char phone[50];
    char address[50];
};

struct node
{
    struct contact person;
    struct node *next;
    struct node *prev;
};

struct node *head=NULL;
struct node *tail=NULL;

int changePosEdit(int pressed,int pos,int x);

//**************************************************
//Input Function from user instead of scanf
//**************************************************

void input(char name[])
{
    int i = 0, flag = 1;
    char ch;

    while(flag)
    {
        ch = getch();
        if(ch == 13)
        {
            flag = 0;
        }
        else
        {
            if(ch != 0)
            {
                name[i] = ch;
                printf("%c",name[i]);
                i++;
            }
        }

        if(i == 49)
        {
            flag = 0;
        }
    }
    name[i] = 0;
}


//**************************************************
//Display the list forward with all contacts
//**************************************************

void displayForward()
{

    struct node *ptr = head;

    printf("\n\n");

    while(ptr != NULL)
    {
	printf("\nName: %s\nPhone Number: %s\nAddress: %s\n\n",ptr->person.name,ptr->person.phone,ptr->person.address);
	cprintf("---------------------\n");
        ptr = ptr->next;
    }

    printf("\n");
}

//**************************************************
//Find the list length
//**************************************************

int length()
{
    int length=0;
    struct node *cur;
    cur=head;
    while (cur)
    {
        length++;
        cur=cur->next;
    }
    return length;
}

//**************************************************
//Create node
//**************************************************

struct node * createNode(struct contact data)
{
    struct node * ptr;
    ptr = (struct node *)malloc(sizeof(struct node));

    if(ptr)
    {
        ptr->person=data;
        ptr->prev = ptr->next = NULL;
    }

    return ptr;
}

//**************************************************
//insert node in right position to be in order
//**************************************************

void insertLast(struct contact data)
{
    struct node *ptr;
    struct node *cur;
    cur=head;
    ptr=createNode(data);
    if(ptr)
    {
        if(head )
        {
            cur=head;
            while (cur &&stricmp(cur->person.name,data.name)<0)
            {
                cur=cur->next;
            }
            if (cur==head)
            {
                cur->prev=ptr;
                ptr->next=cur;
                head=ptr;
            }
            else if (cur==NULL)
            {
                ptr->prev = tail;
                tail->next = ptr;
                tail = ptr;
            }
            else
            {
                cur->prev->next = ptr;
                ptr->prev = cur->prev;
                ptr->next = cur;
                cur->prev = ptr;
            }
        }
        else
        {
            head = tail = ptr;

	}

    }


}

//**************************************************
//Delete node after search by name
//**************************************************

void delNode(char name[50])
{
    struct node* cur;
    cur=head;
    while(stricmp(cur->person.name,name) && cur)
    {
	cur = cur->next;
    }
    if (cur==head)
    {
	head = head->next;
    }
    else
    {
	cur->prev->next = cur->next;
    }
    if (cur==tail)
    {
	tail=tail->prev;
    }
    else
    {
	cur->next->prev = cur->prev;
    }
    free(cur);
    return ;
}

//**************************************************
//Search node by name
//**************************************************

struct contact searchName(char name[50])
{
    struct node * cur;
    struct contact res;
    cur = head;

    while(stricmp(cur->person.name,name) && cur)
    {
	cur = cur->next;
    }

    if(cur)
    {
	res = cur->person;
    }
    return res;
}

//**************************************************
//Edit Node
//**************************************************


struct contact editNode(char name[50])
{
    struct node * cur;
    struct contact res;
    char n;
    char newname[50];
    char newphone[50];
    char newaddress[50];
    cur = head;

    while(stricmp(cur->person.name,name) && cur)
    {
	cur = cur->next;
    }

    if(cur)
    {
        res = cur->person;
        printf ("If you want to Edit Name press a\nIf you want to Edit Phone press b\nIf you want to Edit Address press c\n");
        n=getchar();

        switch(n)
        {
        case 'a':
            delNode(name);
            printf("Contact New Name: ");
            input(newname);
            strcpy(cur->person.name,newname);
            insertLast(cur->person);
            break;

        case 'b':
            printf("Contact New Phone: ");
            input(newphone);
            strcpy(cur->person.phone,newphone);
	    break;

	case 'c':
	    printf("Contact New Address: ");
	    input(newaddress);
	    strcpy(cur->person.address,newaddress);
	    break;

	default:
	    printf("Not valid Number");
	}
    }
    res = cur->person;

    return res;
}



//**************************************************
//Edit Node by phone
//**************************************************


struct contact editNodeByPhone(char phone[50])
{
    struct node * cur;
    struct contact res;
    char n;
    char newname[50];
    char newphone[50];
    char newaddress[50];
    cur = head;

    while(stricmp(cur->person.phone,phone) && cur)
    {
	cur = cur->next;
    }

    if(cur)
    {
        res = cur->person;
        printf ("If you want to Edit Name press a\nIf you want to Edit Phone press b\nIf you want to Edit Address press c\n");
        n=getchar();

        switch(n)
        {
        case 'a':
            delNode(cur->person.name);
            printf("Contact New Name: ");
            input(newname);
            strcpy(cur->person.name,newname);
            insertLast(cur->person);
            break;

        case 'b':
            printf("Contact New Phone: ");
            input(newphone);
            strcpy(cur->person.phone,newphone);
	    break;

	case 'c':
	    printf("Contact New Address: ");
	    input(newaddress);
	    strcpy(cur->person.address,newaddress);
	    break;

	default:
	    printf("Not valid Number");
	}
    }
    res = cur->person;

    return res;
}



//**************************************************
//Search node by name and print all contacts that have the same name
//**************************************************

char * searchNamemany(char name[50],int x)
{
    struct node * cur;
    struct contact res;
    struct contact con;
    struct contact per;
    int i=0, pressed,pos=2;
    char *temp[10];
    cur = head;
    for (i=0; i<x; i++)
    {
	while(stricmp(cur->person.name,name) && cur)
	{
	    cur = cur->next;
	}

	if(cur)
	{
	    res = cur->person;

	    printf("\n%d Contact Name: %s",i+1,res.name);
	    printf("  Contact Phone: %s",res.phone);
	    printf("  Contact Address: %s",res.address);
	    strcpy(temp[i+1],res.phone);
            cur = cur->next;
        }
        //	printf("\n");
    }
    /* EDIT MENU */
    do
    {

        pressed = getch();

        if(pressed == 0)
            // Extended Key
        {
            pressed = getch();
            pos = changePosEdit(pressed,pos,x);
            gotoxy(1,pos);

        }
    }
    while(pressed!=13);
    //send name to edit function
    //clrscr();
//printf("pos= %d phone=%s",pos,temp[pos-1]);
//getch();
    return temp[pos-1];


    //*****************end of edit menu*************************************

}

//**************************************************
//Search Number of Occurrence of node by name
//**************************************************

int searchnumber(char name[50])
{
    struct node * cur;
    int i=0;
    cur = head;
    while (cur != NULL)
    {
	if (stricmp(cur->person.name,name)==0 )
	    i++;
	cur = cur->next;
    }
    return i;
}

//**************************************************
//Search Number of Occurrence of node by phone
//**************************************************

int searchnumberphone(char phone[50])
{
    struct node * cur;
    int i=0;
    cur = head;

    while (cur != NULL)
    {
	if (stricmp(cur->person.phone,phone)==0 )
	    i++;
	cur = cur->next;
    }
    return i;
}


//**************************************************
//Search node by phone
//**************************************************

struct contact searchPhones(char phone[50])
{
    struct node * cur;
    struct contact res;
    cur = head;

    while(stricmp(cur->person.phone,phone) && cur)
    {
	cur = cur->next;
    }

    if(cur)
    {
	res = cur->person;
    }

    return res;
}


//**************************************************
//free All nodes in list
//**************************************************

void freeList()
{
    struct node * ptr;
    struct node * temp;

    ptr = head;

    while(ptr)
    {
	temp = ptr;
	ptr = ptr->next;
	free(temp);
    }
    head = tail = NULL;
}

//**************************************************
//Fill the person contact data
//**************************************************

struct contact fill()
{
    struct contact per;
    int i,x=1,fg=1;
    char str[50];

    printf("Please Enter Person Name : ");
    input(per.name);
    printf("\n");

    while(x)
    {
	printf("Please Enter Person Phone Number : ");
	input(str);
	for(i=0; i<strlen(str); i++)
	{
	    if(str[i] >= 48 && str[i] <= 57|| str[i]==43) //is a digit
	    {
		fg=1;
	    }
	    else
	    {
		textattr(0x60);
                cprintf("\ninvalid number.Try again\n");
                printf("\n");
                textattr(0x03);
                fg=0;
                break;
            }

        }
        if(fg==0)
            x=1;
        else
        {
            strcpy(per.phone,str);
            x=0;
        }
    }

    printf("\n");
    printf("Please Enter The Person Address : ");
    input(per.address);
    printf("\n");


    return per;
}



//**************************************************
//save to File
//**************************************************

void saveToFile()
{
    FILE *fp;
    struct node *cur;
    fp=fopen("phone.txt","w");

    cur=head;
    if(cur==NULL)
    {
        printf("EMPTY LIST :( \n");
        return;
    }
    for(cur=head; (cur); cur=cur->next)

        fprintf(fp,"%s,%s,%s;\n",cur->person.name,cur->person.phone,cur->person.address);

    fclose(fp);

}

//**************************************************
//load from File
//**************************************************

void loadFile()
{
    FILE *fp;
    struct contact data;
    fp=fopen("phone.txt","r");

    if(fp==NULL)
    {
        printf("can't read file :( ");
    }

    while(EOF !=fscanf(fp,"%[^,],%[^,],%[^;]; \n", data.name,data.phone,data.address))
    {
        insertLast(data);
    }

    fclose(fp);
}

//-----------------------------------------------------------------------------------------------------//
// Highlight Function //
//-----------------------------------------------------------------------------------------------------//

void highlight(int pos)
{
    textattr(0x05);

    gotoxy(1,pos+9);
    switch (pos)
    {
    case 1:
	cprintf("1.ADD NEW CONTACT");
	break;

    case 2:
	cprintf("2.DELETE CONTACT");
	break;

    case 3:
	cprintf("3.SEARCH FOR CONTACT BY NAME");
	break;

    case 4:
	cprintf("4.SEARCH FOR CONTACT BY PHONE");
	break;

    case 5:
	cprintf("5.EDIT CONTACTS");
	break;

    case 6:
	cprintf("6.DISPLAY CONTACTS AND NUMBER OF CONTACTS");
	break;

    case 7:
	cprintf("7.SAVE ALL RESORDS TO FILE");
	break;

    case 8:
	cprintf("8.READ ALL RECORDS FROM FILE");
	break;
    case 9:
	 cprintf("9.DELETE ALL CONTACTS");
	 break;

    case 10:
	cprintf("10.EXIT");
	break;
    }
    textattr(0x03);
}
//-----------------------------------------------------------------------------------------------------//
// Change Position Function for Edit  //
//-----------------------------------------------------------------------------------------------------//
int changePosEdit(int pressed,int pos,int num_of_names)
{
    if(pressed == 80)		// Arrow Down
    {
	pos++;
	if(pos > num_of_names+1)
	{
	    pos = 2;
	}
    }

    if(pressed == 72)		// Arrow Up
    {
	pos--;
	if(pos < 2)
	{
	    pos = num_of_names+1;
	}
    }

    return pos;
}

//-----------------------------------------------------------------------------------------------------//
// Change Position Function //
//-----------------------------------------------------------------------------------------------------//

int changePos(int pressed,int posi)
{
    if(pressed == 80)		// Arrow Down
    {
	posi++;
	if(posi > 10)
	{
	    posi = 1;
	}
    }

    if(pressed == 72)		// Arrow Up
    {
	posi--;
	if(posi < 1)
	{
	    posi = 10;
	}
    }

    if(pressed == 79) 		// End
    {
	posi = 10;
    }

    if(pressed == 71)		// Home
    {
	posi = 1;
    }

    return posi;
}

//-----------------------------------------------------------------------------------------------------//
// Freezing Screen Function Function //
//-----------------------------------------------------------------------------------------------------//

void freezeScreen()
{
    getch();
}


int main()
{
    int flag = 1,pos = 1;
    int pressed;
    int x,n;
    char delname[50];
    char searchName[50];
    char searchPhone[50];
    char newname[50];
    char newphone[50];
    char newaddress[50];
    struct contact per;
    struct contact con;
    char * array[50];
    textattr(0x03);

    loadFile();
    clrscr();
    printf("Data Loaded Successfully (Y)");
    freezeScreen();


    do
    {
	clrscr();

	printf("\n\t     _____  _                      ____              _    \n");
	printf(" \t    |  __ \\| |                    |  _ \\            | |   \n");
	printf(" \t    | |__) | |__   ___  _ __   ___| |_) | ___   ___ | | __\n");
	printf(" \t    |  ___/| '_ \\ / _ \\| '_ \\ / _ \\  _ < / _ \\ / _ \\| |/ /\n");
	printf(" \t    | |    | | | | (_) | | | |  __/ |_) | (_) | (_) |   <\n");
	printf(" \t    |_|    |_| |_|\\___/|_| |_|\\___|____/ \\___/ \\___/|_|\\_\\\n\n");

	gotoxy(1,10);
	printf("1.ADD NEW CONTACT\n");
	printf("2.DELETE CONTACT\n");
	printf("3.SEARCH FOR CONTACT BY NAME\n");
	printf("4.SEARCH FOR CONTACT BY PHONE\n");
	printf("5.EDIT CONTACT\n");
	printf("6.DISPLAY CONTACTS AND NUMBER OF CONTACTS\n");
	printf("7.SAVE ALL RECORDS TO FILE\n");
	printf("8.READ ALL RECORDS FROM FILE\n");
	printf("9.DELETE ALL CONTACTS\n");
	printf("10.EXIT\n");

	highlight(pos);

	pressed = getch();

	if(pressed == 0)						// Extended Key
	{
	    pressed = getch();
	    pos = changePos(pressed,pos);
	}
	else									// Normal Key
	{
	    if(pressed == 13)					// Pressed Enter
	    {

		clrscr();

		switch (pos)
		{
		case 1:		// Add Node

		    insertLast(fill());

		    freezeScreen();

		    break;

		case 2:		// Delete Node

		    printf("Please Enter The Contact Name you want to delete: ");

		    input(delname);
		    delNode(delname);
		    displayForward();

		    freezeScreen();

		    break;

		case 3:		// Search Node By Name

		    clrscr();

		    printf("Please Enter The Contact Name You Want To Search For: ");
		    input(searchName);
		    printf("\n");
		    x=searchnumber(searchName);
		    if (x==0)
		    {
			printf("Contact Does not Exist");
		    }
		    else
		    {
			searchNamemany(searchName, x);
		    }

		    freezeScreen();

		    break;

		case 4:		// Search Node By Phone

		    clrscr();

		    printf("Please Enter The Contact Phone That You Want To Search For: ");
		    input(searchPhone);
		    x=searchnumberphone(searchPhone);
		    if (x==0)
		    {
			printf("Contact Does not Exist");
		    }
		    else
		    {
			per = searchPhones(searchPhone);
			printf("Contact Name: %s\n",per.name);
			printf("Contact Phone: %s\n",per.phone);
			printf("Contact Address: %s\n",per.address);

		    }

		    freezeScreen();

		    break;

		case 5:		// Edit Node

		    clrscr();

		    printf("Please Enter The Contact Name You Want To Edit: ");
		    input(searchName);

		    x=searchnumber(searchName);
		    if (x==0)
		    {
			printf("Contact Does not Exist");
		    }
		    else
		    {

			strcpy(array,searchNamemany(searchName, x));
		    }
		    clrscr();
		   // printf("array= %s\n",array);
		    con = searchPhones(array);

                    per=editNodeByPhone(con.phone);
		    printf("\nContact New Name: %s\n",per.name);
		    printf("Contact New Phone: %s\n",per.phone);
		    printf("Contact New Address: %s",per.address);

		    freezeScreen();


		    break;

		case 6:
		    printf("phone Book Contains %d Contact\n",length());
		    printf("******************************************\n");
		    displayForward();
		    freezeScreen();
		    break;

                case 7:
                    saveToFile();
                    clrscr();
                    printf("Data Saved Successfully (Y)");
                    freezeScreen();
                    break;


                case 8:
                    loadFile();
                    clrscr();
                    printf("Data Loaded Successfully (Y)");
                    freezeScreen();
		    break;

		case 9:            //DELETE ALL
		     freeList();
		     clrscr();
		     printf("All Contacts Deleted Successfully\n");
		     freezeScreen();
		     break;


		case 10:		// Exit

                    //freeList();
                    flag = 0;

                    break;
                }
            }
            else if(pressed == 27)				// Pressed Exit
            {

                //freeList();
                flag = 0;

            }
        }


    }
    while(flag);

    return 0;
}

