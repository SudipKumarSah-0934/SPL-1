#include <stdio.h>
#define arrSize 100
int myStrlen(char *str){
    int length = 0;
    for (int i=0; str[i] != 0; i++){
        length++;
    }
    return(length);
}



int myStrRev(char *input){
    char temp[arrSize];
    int begin, end, count = 0;
    while (input[count] != '\0')
      count++;
      end = count - 1;
      for (begin = 0; begin < count; begin++) {
        temp[begin] = input[end];
        end--;
    }
    temp[begin] = '\0';
    printf("Reversed string:\"%s\"\n\n", temp);
    return 0;
}



void myConcat(char *inputStr,char *inputStr1){
    int i,j;
    i=0;
    while(inputStr[i]!='\0'){
             i++;
    }
    j=0;
        while(inputStr1[j]!='\0'){
            inputStr[i]=inputStr1[j];
            j++;
            i++;
        }
        inputStr[i] = '\0';
        printf("concatenated string:\"%s\"\n",inputStr);

}



int myStrCmp(char *inputStr,char *inputStr1){
    int i=0;
    while(1)
    {
        if(inputStr[i]>inputStr1[i])
            return 1;
        else if(inputStr[i]<inputStr1[i])
            return -1;
        else if(inputStr[i]==0&&inputStr1[i]==0)
            return 0;
        i++;
    }
}



int main(void){
    char inputStr[arrSize],inputStr1[arrSize],inputStr2[arrSize],inputStr3[arrSize];
    int strlen;
    printf("Enter first string\n");
    gets(inputStr);
    strlen = myStrlen(inputStr);
    printf("Length of string %s:%d\n\n",inputStr,strlen);

    myStrRev(inputStr);

    printf("enter string to concat\n");
    gets(inputStr1);
    myConcat(inputStr,inputStr1);

    printf("enter string1 to compare\n");
    gets(inputStr2);
    printf("enter string2 to compare\n");
    gets(inputStr3);
    int res = myStrCmp(inputStr2,inputStr3);
    if(res<0)
       printf("%s is less than %s",inputStr2,inputStr3);
    else if(res==0)
    printf("%s are equal to %s",inputStr2,inputStr3);
    else
       printf("%s is greater than %s",inputStr2,inputStr3);


    return 0;

}
