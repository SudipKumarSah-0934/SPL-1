#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX 4
#define MIN 2
#define INF 256

struct btreeNode {
    int val[MAX + 1], count;
    btreeNode *link[MAX + 1];
};

btreeNode *root;
struct Info
{
    string name;
    string Gender;
    string session;
    string address;
    string mobileNo;
    string email_Id;
    string dateOfBirth;//dd-mm-yyyy
    string father_name;
    string mother_name;
    string registrationNo;

} s;
FILE * fp;
 ofstream myfile;


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

void add()
{
char another='p';

fseek(fp,0,SEEK_END);
while(another=='p'||another=='p')
{

 SetColor(85);
  cout<<"*****************************************************\n\n\n";
  cout<<"enter your full name\t:";
  cin>>s.name;
  cout<<"enter your Gender\t:";
  cin>>s.Gender;
  cout<<"enter  Session\t:";
  cin>>s.session;
  cout<<"enter your present address\t:";
  cin>>s.address;
  cout<<"enter your mobile number\t:";
  cin>>s.mobileNo;
  cout<<"enter your email_ID\t:";
  cin>>s.email_Id;
  cout<<"enter your date of birth\t:";
  cin>>s.dateOfBirth;
  cout<<"enter your father's name\t:";
  cin>>s.father_name;
  cout<<"enter your mother's name\t:";
  cin>>s.mother_name;
  cout<<"enter your registration number\t:";
  cin>>s.registrationNo;
  myfile <<s.name<<"\n";
  myfile <<s.Gender<<"\n";
  myfile <<s.session<<"\n";
  myfile <<s.address<<"\n";
  myfile <<s.mobileNo<<"\n";
  myfile <<s.email_Id<<"\n";
  myfile <<s.dateOfBirth<<"\n";
  myfile <<s.father_name<<"\n";
  myfile<<s.mother_name<<"\n";
  myfile <<s.registrationNo<<"\n";
  myfile.close();                                       //fgets takes an extra \n character as input

    printf("\n\n\t\twant to perform next operation type n or N\t:");
    fflush(stdin);

    another=getchar();
}
}
/* creating new node */
btreeNode * createNode(int val, btreeNode *child) {
    btreeNode *newNode = new btreeNode;
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

/* Places the value in appropriate position */
void addValToNode(int val, int pos, btreeNode *node, btreeNode *child) {
    int j = node->count;
    while (j > pos) {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

/* split the node */
void splitNode(int val, int *parentVal, int pos, btreeNode *node,btreeNode *child, btreeNode **newNode) {
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = new btreeNode;
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN) {
        addValToNode(val, pos, node, child);
    }
    else {
        addValToNode(val, pos - median, *newNode, child);
    }
    *parentVal = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

/* sets the value val in the node */
int setValueInNode(int val, int *parentVal,btreeNode *node, btreeNode **child) {

    int pos;
    if (!node) {
        *parentVal = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1]) {
        pos = 0;
    }
    else {
        for (pos = node->count;
            (val < node->val[pos] && pos > 1); pos--);
        if (val == node->val[pos]) {
            cout<<"Duplicates not allowed\n";
            return 0;
        }
    }
    if (setValueInNode(val, parentVal, node->link[pos], child)) {
        if (node->count < MAX) {
            addValToNode(*parentVal, pos, node, *child);
        }
        else {
            splitNode(*parentVal, parentVal, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

/* insert val in B-Tree */
void insertion(int val) {
    int flag, i;
    btreeNode *child;

    flag = setValueInNode(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);

}

/* copy successor for the value to be deleted */
void copySuccessor(btreeNode *myNode, int pos) {
    btreeNode *dummy;
    dummy = myNode->link[pos];

    for (; dummy->link[0] != NULL;)
        dummy = dummy->link[0];
    myNode->val[pos] = dummy->val[1];

}

/* removes the value from the given node and rearrange values */
void removeVal(btreeNode *myNode, int pos) {
    int i = pos + 1;
    while (i <= myNode->count) {
        myNode->val[i - 1] = myNode->val[i];
        myNode->link[i - 1] = myNode->link[i];
        i++;
    }
    myNode->count--;
}

/* shifts value from parent to right child */
void doRightShift(btreeNode *myNode, int pos) {
    btreeNode *x = myNode->link[pos];
    int j = x->count;

    while (j > 0) {
        x->val[j + 1] = x->val[j];
        x->link[j + 1] = x->link[j];
    }
    x->val[1] = myNode->val[pos];
    x->link[1] = x->link[0];
    x->count++;

    x = myNode->link[pos - 1];
    myNode->val[pos] = x->val[x->count];
    myNode->link[pos] = x->link[x->count];
    x->count--;
    return;
}

/* shifts value from parent to left child */
void doLeftShift(btreeNode *myNode, int pos) {
    int j = 1;
    btreeNode *x = myNode->link[pos - 1];

    x->count++;
    x->val[x->count] = myNode->val[pos];
    x->link[x->count] = myNode->link[pos]->link[0];

    x = myNode->link[pos];
    myNode->val[pos] = x->val[1];
    x->link[0] = x->link[1];
    x->count--;

    while (j <= x->count) {
        x->val[j] = x->val[j + 1];
        x->link[j] = x->link[j + 1];
        j++;
    }
    return;
}

/* merge nodes */
void mergeNodes(btreeNode *myNode, int pos) {
    int j = 1;
    btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];

    x2->count++;
    x2->val[x2->count] = myNode->val[pos];
    x2->link[x2->count] = myNode->link[0];

    while (j <= x1->count) {
        x2->count++;
        x2->val[x2->count] = x1->val[j];
        x2->link[x2->count] = x1->link[j];
        j++;
    }

    j = pos;
    while (j < myNode->count) {
        myNode->val[j] = myNode->val[j + 1];
        myNode->link[j] = myNode->link[j + 1];
        j++;
    }
    myNode->count--;
    free(x1);
}

/* adjusts the given node */
void adjustNode(btreeNode *myNode, int pos) {
    if (!pos) {
        if (myNode->link[1]->count > MIN) {
            doLeftShift(myNode, 1);
        }
        else {
            mergeNodes(myNode, 1);
        }
    }
    else {
        if (myNode->count != pos) {
            if (myNode->link[pos - 1]->count > MIN) {
                doRightShift(myNode, pos);
            }
            else {
                if (myNode->link[pos + 1]->count > MIN) {
                    doLeftShift(myNode, pos + 1);
                }
                else {
                    mergeNodes(myNode, pos);
                }
            }
        }
        else {
            if (myNode->link[pos - 1]->count > MIN)
                doRightShift(myNode, pos);
            else
                mergeNodes(myNode, pos);
        }
    }
}

/* delete val from the node */
int delValFromNode(int val,btreeNode *myNode) {
    int pos, flag = 0;
    if (myNode) {
        if (val < myNode->val[1]) {
            pos = 0;
            flag = 0;
        }
        else {
            for (pos = myNode->count;
                (val < myNode->val[pos] && pos > 1); pos--);
            if (val == myNode->val[pos]) {
                flag = 1;
            }
            else {
                flag = 0;
            }
        }
        if (flag) {
            if (myNode->link[pos - 1]) {
                copySuccessor(myNode, pos);
                flag = delValFromNode(myNode->val[pos], myNode->link[pos]);
                if (flag == 0) {
                    cout<<"Given data is not present in B-Tree\n";
                }
            }
            else {
                removeVal(myNode, pos);
            }
        }
        else {
            flag = delValFromNode(val, myNode->link[pos]);
        }
        if (myNode->link[pos]) {
            if (myNode->link[pos]->count < MIN)
                adjustNode(myNode, pos);
        }
    }
    return flag;
}

/* delete val from B-tree */
void deletion(int val,btreeNode *myNode) {
    btreeNode *tmp;
    if (!delValFromNode(val, myNode)) {
        cout<<"Entered value related data is not present in B-Tree\n\n";
        return;
    }
    else {
        if (myNode->count == 0) {
            tmp = myNode;
            myNode = myNode->link[0];
            cout<<"roll number with data is found to deleted from tree\n\n";
             free(tmp);

        }
    }
    root = myNode;
    return;
}
void dataDelete(){

string line;
FILE *fp;
   string str2,str3;
  fstream f("program.txt", fstream::in );
  string s;
  getline( f, s, '\0');
  cout<<"enter string";
  cin>>str2>>str3;

 std::size_t found = s.find(str2);
  std::size_t found1 = s.find(str3);
  if (found!=std::string::npos)
    std::cout << "entered roll number related data is found from index "<<found<<"to"<<found1<<'\n';
  f.close();

   fp = fopen("program.txt", "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

  string studentData = string(&s[found], &s[found1]);


   fclose(fp);
            ifstream file;
            ofstream outfile;
            file.open("final.txt");
            outfile.open("newM.txt");
            while(getline(file,line))
            {
                if(line!=studentData)
                    outfile<<line<<endl;
            }
            outfile.close();
            file.close();
            remove("final.txt");
            rename("newM.txt","final.txt");

}

/* search val in B-Tree */
void searching(int val, int *pos,btreeNode *myNode) {
    if (!myNode) {
        return;
    }

    if (val < myNode->val[1]) {
        *pos = 0;
         cout << "Given data is not Found\n";


    }
    else {
        for (*pos = myNode->count;
            (val < myNode->val[*pos] && *pos > 1); (*pos)--);
        if (val == myNode->val[*pos]) {
            cout << "Given data is Found and added to file\n";
            return;
        }
    }
    searching(val, pos, myNode->link[*pos]);

    return;
}
int searchForData(){
   FILE *fp;
   string str2,str3;
  fstream f("program.txt", fstream::in );
  string s;
  getline( f, s, '\0');
  cout<<"enter string";
  cin>>str2>>str3;

 std::size_t found = s.find(str2);
  std::size_t found1 = s.find(str3);
  if (found!=std::string::npos)
    std::cout << "entered roll number related data is found from index "<<found<<"to"<<found1<<'\n';
  f.close();

   fp = fopen("program.txt", "r"); // read mode

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

  string sp = string(&s[found], &s[found1]);
  cout<<sp<<"\n\n";

   fclose(fp);
   return 0;
}

int main() {


    int rol, option;
    while (true) {

        cout<<"1. Insertion\t2. Deletion\n";
        cout<<"3. Searching\t";
        cout<<"4. Exit\nEnter your choice: ";
        cin >> option;
        cout << endl;
        switch (option) {
        case 1:
             SetColor(5);
            cout<<"Enter your roll:";
            cin >> rol;
            myfile.open ("program.txt",ios::app);
            myfile<<rol<<"\n";
            insertion(rol);
            add();
            break;
        case 2:
            SetColor(2);
            cout<<"Enter the roll to delete:";
            cin >> rol;
            deletion(rol, root);
            dataDelete();
            break;
        case 3:
            SetColor(6);
            cout<<"Enter the roll for search:";
            cin >> rol;
            searching(rol, &option, root);
            searchForData();
            break;
        case 4:
            SetColor(4);
           cout<<"\n\n\nProgram terminated";
           exit(0);
        }

    }

   return 0;
}
