#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxlen 128

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

int compare(const char *a, const char *b);

void sort_array(MOV *ARR[], int n); /* Sort array by date of watch */

float find_year(MOV *ARR[], int i); /* Return year of movie in array under index [i] */

float find_duration(MOV *ARR[], int i); /* Return duration of movie in array under index [i] */

float find_kpr(MOV *ARR[], int i); /* Return KinoPoisk Rating of movie in array under index [i] */

float find_plr(MOV *ARR[], int i); /* Return Personal Rating of movie in array under index [i] */

void find_by(MOV *ARR[], float (*func_name)(MOV**, int), int n); /* Find by number field */

void clear_stream(FILE *input_stream); /* Clear the Buffer */

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
            puts("\nYour selection is FIND IN YEAR\n");
            getchar();
            find_by(ARR,find_year,i);
            break;
        }

        case 4:{
            puts("\nYour selection is FIND IN DURATION\n");
            getchar();
            find_by(ARR,find_duration,i);
            break;
        }
        case 5:{
            puts("\nYour selection is FIND IN KINOPOISK RATING\n");
            getchar();
            find_by(ARR,find_kpr,i);
            break;
        }
        case 6:{
            puts("\nYour selection is FIND IN PERSONAL RATING\n");
            getchar();
            find_by(ARR,find_plr,i);
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
    puts("3 - for FIND IN YEAR");
    puts("4 - for FIND IN DURATION");
    puts("5 - for FIND IN KINOPOSK RATING");
    puts("6 - for FIND IN PERSONAL RATING");
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

    if (file != NULL) {
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

int compare(const char *a, const char *b) {
    int i = 0, result=0;
    char charA, charB;
    while (a[i] && b[i] && result == 0) {
        charA = tolower(a[i]);
        charB = tolower(b[i]);
        if (charA > charB) {
            result = 1;
        } else if (charA < charB) {
            result = -1;
        }
        i++;
    }
    if (result == 0&&a[i]) {
        result = -1;
    }
    return result;
}

void sort_array(MOV *ARR[], int n){
    int i, j;
    MOV *TMP;
    for (i=0; i<n-1; i++) {
        for (j=i+1; j<n; j++) {
            if (compare(ARR[i]->director, ARR[j]->director) == -1) {
                TMP = ARR[i];
                ARR[i] = ARR[j];
                ARR[j] = TMP;
            }
        }
    }
}

float find_year(MOV *ARR[], int i) {
    return ARR[i]->year;
}

float find_duration(MOV *ARR[], int i) {
    return ARR[i]->duration;
}

float find_kpr(MOV *ARR[], int i) {
    return ARR[i]->kpr;
}

float find_plr(MOV *ARR[], int i) {
    return ARR[i]->plr;
}

void find_by(MOV *ARR[], float (*func_name)(MOV**, int), int n){
    int i, count=0;
    float average=0;
    for(i=0;i<n;i++){
        average=average+func_name(ARR,i);
    }
    average=average/n;
    printf("The average value of this field is %.1f\nHere are the elements where the value of this field does not exceed the average value\n\n",average);
    for(i=0;i<n;i++){
        if(average>=func_name(ARR,i)){
            count++;
            if(count==1) print_head();
            printf("| %25s | %25s | %d | %3d | %5.1f | %5.1f | %.2d.%.2d.%.2d |\n", ARR[i]->name, ARR[i]->director, ARR[i]->year, ARR[i]->duration, ARR[i]->kpr, ARR[i]->plr, ARR[i]->date[0], ARR[i]->date[1], ARR[i]->date[2]);
        }
    }
}

void clear_stream(FILE *input_stream){
    if (!feof(input_stream)) {
        while (!feof(input_stream) && fgetc(input_stream) != '\n');
    }
}
