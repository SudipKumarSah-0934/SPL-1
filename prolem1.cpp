#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

#define MAX 4
#define MIN 2

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
void add()
{


char another='p';

fseek(fp,0,SEEK_END);
while(another=='p'||another=='p')
{

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
        cout<<"Entered value related data is not present in B-Tree\n";
        return;
    }
    else {
        if (myNode->count == 0) {
            tmp = myNode;
            myNode = myNode->link[0];
            cout<<"roll number with data is found to deleted";
             free(tmp);

        }
    }
    root = myNode;
    return;
}
void dataDelete(){

string deleteline;
string line;

ifstream fin;
fin.open("final.txt");
ofstream temp;
temp.open("temp1.txt");
cout << "Which line do you want to remove? ";
cin >> deleteline;


while (getline(fin,line))
{
    size_t found = line.find(deleteline);
  if (found!=string::npos)
    cout << "first 'needle' found at: " << found << '\n';

}

   /* if (line != deleteline)
    {
    temp << line << endl;

    }*/



/*
remove("final.txt");
rename("temp1.txt","final.txt");
cout<<"successfully deleted!!!";
*/
temp.close();
fin.close();

}

/* search val in B-Tree */
void searching(int val, int *pos,btreeNode *myNode) {
    if (!myNode) {
        return;
    }

    if (val < myNode->val[1]) {
        *pos = 0;


    }
    else {
        for (*pos = myNode->count;
            (val < myNode->val[*pos] && *pos > 1); (*pos)--);
        if (val == myNode->val[*pos]) {
            cout << "Given data is Found\n";
            return;
        }
    }
    searching(val, pos, myNode->link[*pos]);
    cout << "Given data is not Found\n";
    return;
}
int searchForData(){
    FILE *fileptr;
    int count_lines = 0;
    char chr;
    fileptr = fopen("example1.txt", "r");
   //extract character from file and store in chr
    chr = getc(fileptr);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr == '\n')
        {

            count_lines = count_lines + 1;
        }
        //take next character from file.
        chr = getc(fileptr);
    }
    fclose(fileptr); //close file.
    printf("There are %d lines in a file\n", count_lines);
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
            cout<<"Enter your roll:";
            cin >> rol;
            myfile.open ("final.txt",ios::app);
            myfile<<rol<<"\n";
            insertion(rol);
            add();
            break;
        case 2:
            cout<<"Enter the roll to delete:";
            cin >> rol;
            deletion(rol, root);
            dataDelete();
            break;
        case 3:
            cout<<"Enter the roll for search:";
            cin >> rol;
            searching(rol, &option, root);
            break;
        case 4:
            searchForData();
        }

    }

   return 0;
}

