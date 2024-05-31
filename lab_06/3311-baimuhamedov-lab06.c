#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 128

/* Define Structure */
struct ZNAK2{
    char NAME[100];
    char ZOD[50];
    int DATE[3];
};

/* Define Structured Type */
typedef struct ZNAK2 typeC;

/* Head Interface */
void PrintHead(){
    printf("| %25s | %15s | %10s |\n","Full Name","Zodiac","Birthday");
    printf("+---------------------------+-----------------+------------+\n");
}

/* Output Array */
void outputArray(typeC MASS2[], int n){
    int i;
    for(i=0;i<n;i++){
        printf("| %25s | %15s | %.2d.%.2d.%.2d |\n",MASS2[i].NAME, MASS2[i].ZOD, MASS2[i].DATE[0], MASS2[i].DATE[1], MASS2[i].DATE[2]);
    }
}

/* Split string by delimiter */
void splitString(char *inputString, char **words, int *wordCount, char delimiter) {
    int wordIndex = 0, wordStart=0, wordLength=0, inWord=0, i;

    for (i = 0; i <= strlen(inputString); i++) {
        if ((inputString[i] == delimiter || inputString[i] == '\0')&&(inWord==1)) {
            words[wordIndex] = (char *)malloc(wordLength + 1);
            strncpy(words[wordIndex], inputString + wordStart, wordLength);
            words[wordIndex][wordLength] = '\0';
            wordIndex++;
            inWord = 0;
        } else {
            if (inWord==0) {
                wordStart = i;
                wordLength = 1;
                inWord = 1;
            } else {
                wordLength++;
            }
        }
    }

    *wordCount = wordIndex;
}

/* Read File */
int countOfLines(char *filename) {
    char line[MAXLEN];
    int n=0;

    FILE *file = fopen(filename, "r");

    if (file!=NULL) {
        while((fgets(line,MAXLEN,file))!=NULL) n++;
        rewind(file);
    } else {
        printf("Error opening the file.\n");
    }
    return n;
}

/* Add to Array*/
void AddToArray(typeC MASS2[], char *filename,int n) {
    char *TMP[5], line[MAXLEN], delimiter;
    int wordCount=0, i;

    FILE *file = fopen(filename, "r");

    if (file!=NULL) {
        printf("Enter the separator symbol of structure: ");
        scanf("%c", &delimiter);

        for(i=0;i<n;i++){
            fgets(line, sizeof(line), file);
            splitString(line, TMP, &wordCount, delimiter);
            strcpy(MASS2[i].NAME, TMP[0]);
            strcpy(MASS2[i].ZOD, TMP[1]);
            MASS2[i].DATE[0] = atoi(TMP[2]);
            MASS2[i].DATE[1] = atoi(TMP[3]);
            MASS2[i].DATE[2] = atoi(TMP[4]);
        }
    } else {
        printf("Error opening the file.\n");
    }
     fclose(file);
}

/* Sort Structure by Date of Birthday */
void SortByBirthday(typeC MASS2[], int n){
    typeC temp;
    int i,j;
    for (i=0;i<n-1;i++){
        for (j=0;j<n-i-1;j++) {
            if (MASS2[j].DATE[2] > MASS2[j+1].DATE[2]) {
                temp = MASS2[j];
                MASS2[j] = MASS2[j+1];
                MASS2[j+1] = temp;
            } else if (MASS2[j].DATE[2] == MASS2[j+1].DATE[2]) {
                if (MASS2[j].DATE[1] > MASS2[j+1].DATE[1]) {
                    temp = MASS2[j];
                    MASS2[j] = MASS2[j+1];
                    MASS2[j+1] = temp;
                } else if (MASS2[j].DATE[1] == MASS2[j+1].DATE[1]) {
                    if (MASS2[j].DATE[0] > MASS2[j+1].DATE[0]) {
                        temp = MASS2[j];
                        MASS2[j] = MASS2[j+1];
                        MASS2[j+1] = temp;
                    }
                }
            }
        }
    }
}

/* Find Person with enter Zodiac */
void FindZodiac(typeC MASS2[], int n, char *zodiac){
    int i,count=0;
    printf("\n");
    for (i=0;i<n;i++){
        if(strcmp(MASS2[i].ZOD,zodiac)==0){
            count++;
            if(count==1){
                PrintHead();
            }
            printf("| %25s | %15s | %.2d.%.2d.%.2d |\n",MASS2[i].NAME, MASS2[i].ZOD, MASS2[i].DATE[0], MASS2[i].DATE[1], MASS2[i].DATE[2]);
        }
    }
    if(count==0){
        printf("No person with %s Zodiac\n",zodiac);
    }
}

/*---------------------------------------------------*/

int main(){
    typeC *MASS2=NULL;
    int i;
    char zodiac[50];

    i=countOfLines("input.txt");
    MASS2=(typeC*)malloc(i*sizeof(typeC));
    AddToArray(MASS2,"input.txt",i);

    SortByBirthday(MASS2,i);
    printf("\nArray sorted by birthday:\n\n");
    PrintHead();
    outputArray(MASS2, i);

    printf("\nEnter the Zodiac: ");
    scanf("%s",zodiac);
    FindZodiac(MASS2,i,zodiac);

    return 0;
}