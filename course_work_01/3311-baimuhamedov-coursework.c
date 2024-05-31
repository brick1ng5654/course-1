#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 512
#define MAXLINE 256

/*Main function for the actual program logic*/
void Program();

/*Read the string and write it in s[]*/
void new_gets(char s[], int lim);

/*Enter the text by keyboard*/
void EnterText(int lines, char[][MAXLEN]);

/*Read text from file and write it in array*/
void ReadText(const char *filename,int lines, char text[][MAXLEN]);

/*Write text array to file*/
void WriteToFile(const char *filename, char text[MAXLINE][MAXLEN],int lines);

/*Output text array*/
void OutputText(int lines, char text[][MAXLEN]);

/*Cleaning the console depending on the OS*/
void ClearScreen();

/*Count special word in string*/
int CountOfSpecialWord(char *string, char *word);

/*Count all words in string*/
int CountOfAllWords(char *string, char *separatorstring);

/*Check if the number of special word and special number in a line is equal and, if true, add that line to the result text array.*/
int WordCondition(char text[][MAXLEN], int lines, int speccount, char specword[],char restext[][MAXLEN]);

/*Sort text array by increase word count in string*/
void SortByWordCount(char restext[][MAXLEN], int NumbArray[MAXLEN], int j, char SepString[]);

void clear_stream(FILE *input_stream);

int main(){
    int key;
    do{
        puts("Choose the options:");
        puts("0 - for EXIT program");
        puts("1 - for RUN program");
        printf("Enter the option: ");
        scanf("%d", &key);
        switch(key){
        case 0:
            {
            puts("Your selection is EXIT");
            getchar();
            }
            break;
        case 1:
            {
            puts("Your selection is RUN\n");
            Program();
            getchar();
            }
            break;
        default:
            {
                puts("Incorrect key!");
                getchar();
            }
        }
    puts("\nPress ENTER to continue");
    clear_stream(stdin);
    ClearScreen();
    } while(key!=0);
    return 0;
}

void Program(){
    int lines=0,numbers[MAXLINE],specnumber,j;
    char sep[MAXLEN], text[MAXLINE][MAXLEN], word[MAXLEN], restext[MAXLINE][MAXLEN], key[MAXLEN]="", inputfile[MAXLEN];

    /*Input data*/
    printf("Enter number of lines: ");
    scanf("%d", &lines);
    while (strcmp(key, "file") != 0 && strcmp(key, "keyboard") != 0){
        printf("\nHow would you like to enter the text? (file / keyboard): ");
        scanf("%s",key);
    }
    getchar();
    if (strcmp(key, "file") == 0){
        printf("Enter a file name like 'input.txt': ");
        scanf("%s", inputfile);
        getchar();
        ReadText(inputfile,lines,text);
        OutputText(lines,text);
    }else{
        EnterText(lines,text);
    }
    printf("Enter the string of separators: ");
    new_gets(sep,MAXLEN);
    printf("\nEnter a special word: ");
    scanf("%s", word);
    printf("\nEnter a special number: ");
    scanf("%d", &specnumber);
    /*Process*/
    j=WordCondition(text,lines,specnumber,word,restext);
    SortByWordCount(restext,numbers,j,sep);
    WriteToFile("output.txt",restext,lines);
    /*Output data*/
    printf("\nOriginal text:\n");
    OutputText(lines,text);
    printf("Result text:\n");
    OutputText(j,restext);
}

void new_gets(char s[], int lim){
    char c;
    int i=0;
    while(((c=getchar())!='\n')&&(i<lim-1))
    {
        s[i]=c;
        i++;
    }
    s[i]='\0';
}

void EnterText(int lines, char text[][MAXLEN]){
    int i;
    for(i=0;i<lines;i++){
        printf("Enter the string number %d: ",i+1);
        new_gets(text[i],MAXLEN);
    }
    printf("\n");
}

void ReadText(const char *filename,int lines, char text[][MAXLEN]){
    int i;
    FILE *file = fopen(filename, "r");
    if (file) {
        for(i=0;i<lines;i++){
            fgets(text[i], MAXLEN, file);
            text[i][strlen(text[i])-1]=0;
        }
        printf("The file was successfully opened and read. The file contains this text:\n");
        fclose(file);
    } else {
        printf("Error opening the file.\n");
    }
}

void WriteToFile(const char *filename, char text[MAXLINE][MAXLEN],int lines){
    int i;
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (i = 0; i <= lines; i++){
            fprintf(file, "%s\n", text[i]);
        }
    }else{
        puts("Error opening file\n");
    }
    fclose(file);
}

void OutputText(int lines, char text[][MAXLEN]){
    int i;
    for(i=0;i<=lines;i++){
        printf("%s\n", text[i]);
    }
}

void ClearScreen(){
#ifdef _WIN64
system("cls");
#else
system("clear");
#endif
}

int CountOfSpecialWord(char *string, char *word){
    int count=0;
    int wordLength = strlen(word);
    char *current = string;
    char *found = strstr(current, word);
    while(found){
        if(found == string || !isalpha(*(found-1))){
            if (!isalpha(*(found + wordLength))) {
                count++;
            }
        }
        current = found + 1;
        found = strstr(current, word);
    }
    return count;
}

int CountOfAllWords(char *string, char *separatorstring){
    int count=0, len=strlen(string), seplen=strlen(separatorstring),i,j;
    for(i=0;i<len-1;i++){
        for(j=0;j<seplen;j++){
            if(string[i]==separatorstring[j]){
                count++;
                while(i<len && strchr(separatorstring,string[i])){
                    i++;
                }
            }
        }
    }
    return count+1;
}

int WordCondition(char text[][MAXLEN], int lines, int speccount, char specword[],char restext[][MAXLEN]){
    int i,count, j=0;
    for(i=0;i<=lines;i++){
        count=CountOfSpecialWord(text[i],specword);
        if(count==speccount){
            strcpy(restext[j],text[i]);
            j++;
        }
    }
    return j-1;
}

void SortByWordCount(char restext[][MAXLEN], int NumbArray[MAXLEN], int j, char SepString[]){
    int i, tmpn;
    char tmpc[MAXLEN];
    for(i=0;i<=j;i++){
        NumbArray[i]=CountOfAllWords(restext[i], SepString);
    }
    for(i=0;i<j;i++){
        if (NumbArray[i]>NumbArray[i+1]){
            tmpn=NumbArray[i];
            strcpy(tmpc,restext[i]);
            NumbArray[i]=NumbArray[i+1];
            NumbArray[i+1]=tmpn;
            strcpy(restext[i],restext[i+1]);
            strcpy(restext[i+1],tmpc);
        }
    }
}

void clear_stream(FILE *input_stream){
    if (!feof(input_stream)) {
        while (!feof(input_stream) && fgetc(input_stream) != '\n');
    }
}
