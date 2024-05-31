#include <stdio.h>
#include <string.h>
#define MAXLEN 80
/*Function of input string*/
void new_gets(char s[], int lim)
{
    char c;
    int i=0;
    while(((c=getchar())!='\n')&&(i<lim-1)){
        s[i]=c;
        i++;
    }
    s[i]='\0';
}

/*Main program*/
int main(){
    char ostring[MAXLEN], sep[MAXLEN];
    int len, sepc, flag=0, nword=0, i, j, reslen=0;

    /*Input original string and separator string*/
    printf("Enter the string:\n");
    new_gets(ostring,MAXLEN);
    printf("\nEnter the string of separators:\n");
    new_gets(sep,MAXLEN);

    /*Counting*/
    len=strlen(ostring);
    sepc=strlen(sep);
    for(i=len-1;i>=0;i--){
        for(j=0;(j<sepc)&&(nword==0);j++){
            if(ostring[i]==sep[j]){
                flag=flag+1;
                nword=1;
            }
        }
        if ((flag == 1)&&((ostring[i] >= 65 && ostring[i] <= 90) || (ostring[i] >= 97 && ostring[i] <= 122))){
            reslen++;
            nword=0;
        }
    }

    /*Output*/
    printf("\nNumber of letters in penultimate word: %d", reslen);
    return 0;
}
