#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum{maxlen=128};

/* Structure */

struct movie; /* Define Structure */

typedef struct movie MOV; /* Define Structured Type */

/* Interface */

void menu(); /* Output main menu */

void print_head(); /* Output title of sheet */

void output_array(MOV *ARR[], int n); /* Output array with MOV structure */

void clear_screen(); /* Clear the console */

/* Sort, Form and other stuff */

int count_of_lines(char *filename); /* Count of lines in file */

void split_string(char *inputString, char **words, int *wordCount, char delimiter); /* Split string by separator */

void add_to_array(MOV *ARR[], char *filename,int n, char sep); /* Adding the data of file to array */

void new_gets(char s[], int lim); /* scan string */

void add_new_data(char *filename); /* Enter new movie */

void sort_array(MOV *ARR[], int n); /* Sort array by date of watch */

char* find_name(MOV *ARR[], int i); /* return name of movie under number [i] */

char* find_director(MOV *ARR[], int i); /* return director of movie under number [i] */

void find_by(MOV *ARR[], char *(*func_name)(MOV**, int), int n); /* find by name or director */

void clear_stream(FILE *input_stream); /* Clear the Buffer */

/* Main program */

int main(){
    int option,i;
    char sep;
    MOV **ARR=NULL;
    printf("Enter the separator of structure data: ");
    scanf("%c", &sep);

    do{
        i=count_of_lines("struct-data-win.txt");
        ARR=(MOV**)malloc(i*sizeof(MOV*));
        add_to_array(ARR,"struct-data-win.txt",i,sep);
        menu();
        scanf("%i", &option);

        switch(option){
        case 0:{
            puts("\nYour selection is EXIT");
            getchar();
            break;
        }

        case 1:{
            puts("\nYour selection is SHOW THE DATA\n");
            getchar();
            output_array(ARR,i);
            break;
        }

        case 2:{
            puts("\nYour selection is ADD NEW DATA\n");
            add_new_data("struct-data-win.txt");
            getchar();
            break;
        }

        case 3:{
            puts("\nYour selection is FIND IN NAME\n");
            getchar();
            find_by(ARR,find_name,i);
            break;
        }

        case 4:{
            puts("\nYour selection is FIND IN DIRECTOR\n");
            getchar();
            find_by(ARR,find_director,i);
            break;
        }

        default:{
            puts("\nIncorrect key");
            getchar();
        }
        }
    puts("\nPress ENTER to continue");
    clear_stream(stdin);
    clear_screen();
    } while(option!=0);
    return 0;
}

/* Functions */

struct movie{
    char *name; /* Name of movie */
    char *director; /* Director of movie */
    int year; /* Year of movie release */
    int duration; /* duration of movie in minutes*/
    float kpr; /* Movie rating on KinoPoisk */
    float plr; /* Movie rating on my opinion */
    int date[3]; /* Day/Month/Year of watch the movie */
};

void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for SHOW THE DATA");
    puts("2 - for ADD NEW DATA");
    puts("3 - for FIND IN NAME");
    puts("4 - for FIND IN DIRECTOR");
    printf("Enter the option: ");
}

void print_head(){
    printf("| %25s | %25s | %4s | %3s | %5s | %5s | %10s |\n","Name","Director","Year","Dur","KPR","PLR","Watchdate");
    printf("+---------------------------+---------------------------+------+-----+-------+-------+------------+\n");
}

void output_array(MOV *ARR[], int n){
    int i;
    print_head();
    for(i=0;i<n;i++){
        printf("| %25s | %25s | %d | %3d | %5.1f | %5.1f | %.2d.%.2d.%.2d |\n", ARR[i]->name, ARR[i]->director, ARR[i]->year, ARR[i]->duration, ARR[i]->kpr, ARR[i]->plr, ARR[i]->date[0], ARR[i]->date[1], ARR[i]->date[2]);
    }
}

void clear_screen(){
#ifdef _WIN64
system("cls");
#else
system("clear");
#endif
}

int count_of_lines(char *filename) {
    char line[maxlen];
    int n=0;

    FILE *file = fopen(filename, "r");

    if (file!=NULL) {
        while((fgets(line,maxlen,file))!=NULL) n++;
        rewind(file);
    } else {
        printf("Error opening the file.\n");
    }
    return n;
}

void split_string(char *inputString, char **words, int *wordCount, char delimiter) {
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

void add_to_array(MOV *ARR[], char *filename, int n, char sep){
    char line[maxlen];
    char **TMP = NULL;
    int wordCount = 0, i;

    FILE *file = fopen(filename, "r");

    if (ARR != NULL) {
        TMP = (char **)malloc(maxlen * sizeof(char *));
        for (i = 0; i < n; i++) {
            fgets(line, maxlen, file);
            split_string(line, TMP, &wordCount, sep);
            if (TMP != NULL) {
                ARR[i] = (MOV*)malloc(sizeof(MOV));
                ARR[i]->name = TMP[0];
                ARR[i]->director = TMP[1];
                ARR[i]->year = atoi(TMP[2]);
                ARR[i]->duration = atoi(TMP[3]);
                ARR[i]->kpr = atof(TMP[4]);
                ARR[i]->plr = atof(TMP[5]);
                ARR[i]->date[0] = atoi(TMP[6]);
                ARR[i]->date[1] = atoi(TMP[7]);
                ARR[i]->date[2] = atoi(TMP[8]);
            }
        }
    } else printf("Error opening the file.\n");
    fclose(file);
    for (i = 0; i < wordCount; i++) free(TMP[i]);
    free(TMP);
    sort_array(ARR,n);
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

void add_new_data(char *filename){
    char name[maxlen],director[maxlen];
    int year,duration, d,m,y;
    float kpr, plr;
    FILE *file = fopen(filename, "a");

    printf("Enter the name of movie: ");
    getchar();
    new_gets(name,maxlen);
    printf("\nEnter the director of movie: ");
    new_gets(director,maxlen);
    printf("\nEnter the year of movie release: ");
    scanf("%d", &year);
    printf("\nEnter the duration of movie: ");
    scanf("%d", &duration);
    printf("\nEnter the KinoPoisk Rating: ");
    scanf("%f", &kpr);
    printf("\nEnter your Rating: ");
    scanf("%f", &plr);
    printf("\nEnter the date of watch: ");
    scanf("%d %d %d",&d,&m,&y);

    fprintf(file, "%s;%s;%d;%d;%.1f;%.1f;%2d;%2d;%d\n", name, director, year, duration, kpr, plr, d, m, y);

    fclose(file);
}

void sort_array(MOV *ARR[], int n) {
    MOV *temp;
    int i, j;
    for (i=0; i<n-1; i++) {
        for (j=0; j<n-i-1; j++) {
            if (ARR[j]->date[2] < ARR[j + 1]->date[2]) {
                temp = ARR[j];
                ARR[j] = ARR[j + 1];
                ARR[j + 1] = temp;
            } else if (ARR[j]->date[2] == ARR[j + 1]->date[2]) {
                if (ARR[j]->date[1] < ARR[j + 1]->date[1]) {
                    temp = ARR[j];
                    ARR[j] = ARR[j + 1];
                    ARR[j + 1] = temp;
                } else if (ARR[j]->date[1] == ARR[j + 1]->date[1]) {
                    if (ARR[j]->date[0] < ARR[j + 1]->date[0]) {
                        temp = ARR[j];
                        ARR[j] = ARR[j + 1];
                        ARR[j + 1] = temp;
                    }
                }
            }
        }
    }
}

char* find_name(MOV *ARR[], int i) {
    return ARR[i]->name;
}

char* find_director(MOV *ARR[], int i) {
    return ARR[i]->director;
}

void find_by(MOV *ARR[], char *(*func_name)(MOV**, int), int n){
    int i, result, count=0;
    char substring[maxlen];
    printf("Enter the substring: ");
    new_gets(substring,maxlen);
    for(i=0;i<n;i++){
        result=strncasecmp(substring,func_name(ARR,i),strlen(substring));
        if(result==0){
            count++;
            if(count==1) print_head();
            printf("| %25s | %25s | %d | %d | %5.1f | %5.1f | %.2d.%.2d.%.2d |\n", ARR[i]->name, ARR[i]->director, ARR[i]->year, ARR[i]->duration, ARR[i]->kpr, ARR[i]->plr, ARR[i]->date[0], ARR[i]->date[1], ARR[i]->date[2]);
        }
    }
    if(count==0) printf("\nThere is no name that begins with the entered substring\n");
}

void clear_stream(FILE *input_stream){
    if (!feof(input_stream)) {
        while (!feof(input_stream) && fgetc(input_stream) != '\n');
    }
}