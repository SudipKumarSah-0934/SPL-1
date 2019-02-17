#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define Student struct Stud
void add(FILE * fp);
void displayList(FILE * fp);
void searchRecord(FILE *fp);
void printChar(char ch,int n);
void printHead();


struct Stud
{
    char name[1000];
    char session[1000];
    int roll;
    char address[1000];
    int mobileNo[1000];
    char dateOfBirth[1000];//dd-mm-yyyy
    char parentsName[1000];
    char registrationNo[1000];

};


int main()
{
 FILE * fp;
 Student s;
int option;
char another;

if((fp=fopen("studentInfo.txt","rb+"))==NULL)
{
    if((fp=fopen("studentInfo.txt","wb+"))==NULL)
       {
           printf("can't open file");
           return 0;
       }
}

printHead();
printf("\n\t\tpress any key to Enter");
_getch();//reads the character without echoing it

while(1)
{
    printHead();
    printf("\n\t");
    printChar('-',64);

    printf("\n\n\t\t\t1. ADD Student");
    printf("\n\n\t\t\t2. DISPLAY Student LIST");
    printf("\n\n\t\t\t3. Search Record");
    printf("\n\n\t\t\t0. EXIT");

    printf("\n\n\t\tEnter Your Option :--> ");
    scanf("%d",&option);

    switch(option)
    {
        case 0: return 1;
                break;
        case 1: add(fp);
                break;
        case 2: displayList(fp);
                break;
        case 3: searchRecord(fp);
                break;
        default: printf("\n\t\tYou Pressed wrong key");
                  printf("\n\t\tProgram terminated");
                  getch();
                  exit(0);

    }
}
return 1;

}

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void printHead()
{ system("cls");

printf("\n\n\t");
printf("######################################");
printf("[IIT] [STUDENT] [INFORMATION] [SYSTEM]");
printf("##################################");
printf("\n");
}


void add(FILE * fp)
{
printHead();

char another='y';
Student s;

fseek(fp,0,SEEK_END);
while(another=='y'||another=='Y')
{
                                                //fgets takes an extra \n character as input
    printf("\n\n\t\tEnter Full Name of Student\t:");
    fflush(stdin);
    fgets(s.name,1000,stdin);
    s.name[strlen(s.name)]='\0';

      printf("\n\n\t\tEnter Session\t:");
    fflush(stdin);
    fgets(s.session,1000,stdin);
    s.session[strlen(s.session)-1]='\0';

      printf("\n\n\t\tEnter Roll number \t:");
    scanf("%d",&s.roll);

      printf("\n\n\t\tEnter Address\t:");
    fflush(stdin);
    fgets(s.address,1000,stdin);
    s.name[strlen(s.name)-1]='\0';

      printf("\n\n\t\tEnter MobileNumber\t:");
    fflush(stdin);
    fgets(s.mobileNo,1000,stdin);
    s.mobileNo[strlen(s.mobileNo)-1]='\0';

      printf("\n\n\t\tEnter Date Of Birth(dd-mm-yyyy)\t:");
    fflush(stdin);
    fgets(s.dateOfBirth,1000,stdin);
    s.dateOfBirth[strlen(s.dateOfBirth)-1]='\0';

      printf("\n\n\t\tEnter parent's Name\t:");
    fflush(stdin);
    fgets(s.parentsName,1000,stdin);
    s.parentsName[strlen(s.parentsName)-1]='\0';

      printf("\n\n\t\tEnter registration Number\t:");
    fflush(stdin);
    fgets(s.registrationNo,1000,stdin);
    s.registrationNo[strlen(s.registrationNo)-1]='\0';


    fwrite(&s,sizeof(s),1,fp);

    printf("\n\n\t\tWant to enter another student info (Y/N)\t:");
    fflush(stdin);
    another=getchar();
}
}


void displayList(FILE * fp)
{   printHead();
    Student s;
    int i=0, siz=sizeof(s);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        i++;
        printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tSession : %s",s.session);
        printf("\n\t\tNAME : %d",s.roll);
        printf("\n\n\t\tAddress : %s",s.address);
        printf("\n\t\tMobileNumber : %s",s.mobileNo);
        printf("\n\n\t\tDateOfBirth(dd-mm-yyy) : %s",s.dateOfBirth);
        printf("\n\t\tParentsName : %s",s.parentsName);
        printf("\n\n\t\tRegistrationNumber : %s\n\n",s.registrationNo);


 printf("****************************************************");
    }

      printf("\n\n\n\t");
    printf("\n\n\t");
     printf("total no. of students:%d\n\n\n\n",i);
    system("pause");

}

void searchRecord(FILE *fp)
{printHead();

int tempRoll,flag,siz,i;
Student s;
char another='y';

siz=sizeof(s);

while(another=='y'||another=='Y')
{
printf("\n\n\tEnter Roll Number of Student to search the record : ");
scanf("%d",&tempRoll);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.roll==tempRoll)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
    printf("\n\t\tFullName : %s",s.name);
        printf("\n\n\t\tSession : %s",s.session);
        printf("\n\t\tRollNumber : %d",s.roll);
        printf("\n\n\t\tAddress : %s",s.address);
        printf("\n\t\tMobileNumber : %s",s.mobileNo);
        printf("\n\n\t\tDateOfBirth(dd-mm-yyy) : %s",s.dateOfBirth);
        printf("\n\t\tParent'sName : %s",s.parentsName);
        printf("\n\n\t\tRegistrationNumber : %s",s.registrationNo);




}
else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
printf("\n\n\t\tWant to enter another search (Y/N)");
fflush(stdin);
another=getchar();
}
}


