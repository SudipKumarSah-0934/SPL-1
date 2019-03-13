#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#define Student struct Stud
struct Stud
{
    char name[1000];
    char Gender[1000];
    char session[1000];
    int roll;
    char address[1000];
    int mobileNo[1000];
    char email_Id[1000];
    char dateOfBirth[1000];//dd-mm-yyyy
    char father_name[1000];
    char mother_name[1000];
    char registrationNo[1000];

};
FILE * fp;
 Student s;
int option;
char another;

void SetColor(int ForgC)//colour varies from 0 to 256
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void SetBackground(int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void printHead()
{ system("cls");//to run another program by passing a command line


printf("\t\t\t\t\t[IIT] [STUDENT] [INFORMATION] [SYSTEM]\n\n\n");
}

void add(FILE * fp)
{
printHead();

char another='y';
Student s;

fseek(fp,0,SEEK_END);
while(another=='y'||another=='Y')
{
         SetColor(85);                                       //fgets takes an extra \n character as input
    printf("\n\n\tEnter Full Name of Student\t:");
    fflush(stdin);
    fgets(s.name,1000,stdin);
    s.name[strlen(s.name)]='\0';

     printf("\n\n\tEnter Gender\t:");
    fflush(stdin);
    fgets(s.Gender,1000,stdin);
    s.Gender[strlen(s.Gender)]='\0';

      printf("\n\n\tEnter Session\t:");
    fflush(stdin);
    fgets(s.session,1000,stdin);
    s.session[strlen(s.session)-1]='\0';

      printf("\n\n\tEnter Roll number \t:");
    scanf("%d",&s.roll);

      printf("\n\n\tEnter Address\t:");
    fflush(stdin);
    fgets(s.address,1000,stdin);
    s.address[strlen(s.address)-1]='\0';

      printf("\n\n\tEnter MobileNumber\t:");
    fflush(stdin);
    fgets(s.mobileNo,1000,stdin);
    s.mobileNo[strlen(s.mobileNo)-1]='\0';

     printf("\n\n\tEnter Email ID\t:");
    fflush(stdin);
    fgets(s.email_Id,1000,stdin);
    s.email_Id[strlen(s.email_Id)-1]='\0';

    printf("\n\n\tEnter Date Of Birth(dd-mm-yyyy)\t:");
    fflush(stdin);
    fgets(s.dateOfBirth,1000,stdin);
    s.dateOfBirth[strlen(s.dateOfBirth)-1]='\0';

      printf("\n\n\tEnter father's Name\t:");
    fflush(stdin);
    fgets(s.father_name,1000,stdin);
    s.father_name[strlen(s.father_name)-1]='\0';
     printf("\n\n\tEnter mother's Name\t:");
    fflush(stdin);
    fgets(s. mother_name,1000,stdin);
    s. mother_name[strlen(s. mother_name)-1]='\0';

      printf("\n\n\tEnter registration Number\t:");
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
        SetColor(244);
        printf("\n\t\tFullName : %s",s.name);
        printf("\n\t\tGender : %s",s.Gender);
        printf("\n\t\tSession : %s",s.session);
        printf("\n\t\tRollNumber : %d",s.roll);
        printf("\n\t\tAddress : %s",s.address);
        printf("\n\t\tMobileNumber : %s",s.mobileNo);
        printf("\n\t\tEmail_Id : %s",s.email_Id);
        printf("\n\t\tDateOfBirth(dd-mm-yyy) : %s",s.dateOfBirth);
        printf("\n\t\tFather's Name : %s",s.father_name);
        printf("\n\t\tMother's Name : %s",s.mother_name);
        printf("\n\t\tRegistrationNumber : %s\n\n",s.registrationNo);


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
        SetColor(68);
    printf("\n\t\tFullName : %s",s.name);
        printf("\n\t\tGender : %s",s.Gender);
        printf("\n\t\tSession : %s",s.session);
        printf("\n\t\tRollNumber : %d",s.roll);
        printf("\n\t\tAddress : %s",s.address);
        printf("\n\t\tMobileNumber : %s",s.mobileNo);
        printf("\n\t\tEmail_Id : %s",s.email_Id);
        printf("\n\t\tDateOfBirth(dd-mm-yyy) : %s",s.dateOfBirth);
        printf("\n\t\tFather's Name : %s",s.father_name);
        printf("\n\t\tMother's Name : %s",s.mother_name);
        printf("\n\t\tRegistrationNumber : %s\n\n",s.registrationNo);




}
else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
printf("\n\n\t\tWant to enter another search (Y/N)");
fflush(stdin);
another=getchar();
}
}


int main()
{

if((fp=fopen("newstudentInfo.txt","rb+"))==NULL)
{
    if((fp=fopen("newstudentInfo.txt","wb+"))==NULL)
       {
           printf("can't open file");
           SetColor(34);
           printf("can't open file");
           return 0;
       }
}
SetBackground(10);
SetColor(16);
printHead();
printf("\n\t\tpress any key to Enter");
_getch();//reads the character without echoing it

while(1)
{
    printHead();
    printf("\n\t");
    printf("******************************************");
    SetColor(52);
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




