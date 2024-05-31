#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxlen 128

/* Structure */

struct movie; /* Define structure of movie */

struct head; /* Define structure of List Head*/

typedef struct movie MOV; /* Define Structured Type of Movie */

typedef struct head HD; /* Define Structured Type of List Head*/

/* Node and List */

HD *make_head(); /* Head initialization */

MOV *create_movie(char *movie_name, char *movie_director, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3]); /* Node Initialization*/

void add_node(HD *ph, MOV *new_node, MOV *current_node); /* Add new Node to List */

void delete_node(HD *ph, MOV *current_node); /* Delete selected Node */

void reset_to_original_data(char *filename, HD *ph, char sep); /* Reset List to Original Data */

/* Add last right now in useless, but function already written and saved in test.c */

/* Interface */

void menu(); /* Output main menu */

void print_head(); /* Output title of sheet */

void output_list(HD *head); /* Output array with MOV structure */

void clear_screen(); /* Clear the console */

/* Sort, Form and other Stuff */

void split_string(char *inputString, char **words, int *wordCount, char delimiter); /* Split string by separator */

void add_to_list(char *filename, HD *ph, char sep); /* Adding the data of file to array */

void find_id(HD *ph); /* Find by ID */

void clear_stream(FILE *input_stream); /* Clear the Buffer */

/* Main Program */

int main() {
    char sep;
    int option;
    HD *ph;

    printf("Enter the separator of structure data: ");
    scanf("%c", &sep);
    ph=make_head();
    add_to_list("struct-data-win.txt", ph,sep);

    do{
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
            output_list(ph);
            break;
        }

        case 2:{
            puts("\nYour selection is DELETE\n");
            output_list(ph);
            find_id(ph);
            getchar();
            break;
        }

        case 3:{
            puts("\nYour selection is RESET TO ORIGINAL DATA\n");
            reset_to_original_data("struct-data-win.txt",ph,sep);
            printf("Reset to original data is completed\n");
            getchar();
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
    } while (option!=0);

    return 0;
}

struct movie{
    int id; /* ID of element */
    char *name; /* Name of movie */
    char *director; /* Director of movie */
    int year; /* Year of movie release */
    int duration; /* duration of movie in minutes*/
    float kpr; /* Movie rating on KinoPoisk */
    float plr; /* Movie rating on my opinion */
    int date[3]; /* Day/Month/Year of watch the movie */
    struct movie *next; /* Link to next node */
};

struct head{
    int cnt; /* Counter of all elements that ever exist */
    struct movie *first;
    struct movie *last;
};

HD *make_head(){
    HD *ph=NULL; /* Define and init Head */
    ph=(HD*)malloc(sizeof(HD));
    ph->cnt=0;
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}

MOV *create_movie(char *movie_name, char *movie_director, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3]){
    MOV *new_movie = NULL; /* Pointer to new node */
    char *name = NULL;
    char *director = NULL;

    new_movie = (MOV*)malloc(sizeof(MOV));
    name = (char*)malloc((strlen(movie_name) + 1) * sizeof(char));
    director = (char*)malloc((strlen(movie_director) + 1) * sizeof(char));

    if (new_movie && name && director){ /* Data is not empty */
        new_movie->id = 1; /* Setting node ID to 1 */
        new_movie->name = name;
        new_movie->director = director;
        new_movie->year = movie_year;
        new_movie->duration = movie_duration;
        new_movie->kpr = movie_kpr;
        new_movie->plr = movie_plr;
        memcpy(name, movie_name, strlen(movie_name) + 1);
        memcpy(director, movie_director, strlen(movie_director) + 1);
        memcpy(new_movie->date, watch_date, sizeof(new_movie->date));
        new_movie->next = NULL;
    }

    return new_movie; /* return adres of node */
}

void add_node(HD *ph, MOV *new_node, MOV *current_node){
    int n;
    if(ph&&new_node){
        n=ph->cnt+1;
        if (current_node == NULL) { /* Add first node of list */
            ph->first = new_node;
            ph->last = new_node;
        } else{
            current_node->next=new_node;
            ph->last=new_node;
        }

        new_node->id=n;
        ph->cnt=n;
    }
}

void delete_node(HD *ph, MOV *current_node){
    MOV *q, *q1;

    q=ph->first;
    q1=ph->last;
    if(current_node==q){
        ph->first=current_node->next;
        current_node->next=NULL;
        free(current_node);
    }
    else{
        while(q!=NULL){
            if(q->next==current_node){
                if(current_node==q1) ph->last=q;
                q->next=current_node->next;
                current_node->next=NULL;
                free(current_node);
            } else q=q->next;
        }
    }
}

void reset_to_original_data(char *filename, HD *ph, char sep) {
    MOV *current = ph->first;
    MOV *temp;

    ph->cnt=0;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    ph->first = NULL;
    ph->last = NULL;

    add_to_list(filename, ph, sep);
}

void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for SHOW THE DATA");
    puts("2 - for DELETE");
    puts("3 - for RESET TO ORIGINAL DATA");
    printf("Enter the option: ");
}

void print_head(){
    printf("| %2s | %25s | %25s | %4s | %3s | %5s | %5s | %10s |\n","ID","Name","Director","Year","Dur","KPR","PLR","Watchdate");
    printf("+----+---------------------------+---------------------------+------+-----+-------+-------+------------+\n");
}

void output_list(HD *ph) {
    MOV *current;

    current = ph->first;
    print_head();

    while (current!=NULL) {
        printf("| %2d | %25s | %25s | %d | %3d | %5.1f | %5.1f | %.2d.%.2d.%d |\n", current->id, current->name, current->director, current->year, current->duration, current->kpr, current->plr, current->date[0], current->date[1], current->date[2]);
        current = current->next;
    }
}

void clear_screen(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
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

void add_to_list(char *filename, HD *ph, char sep){
    char line[maxlen], *words[9];
    int wordCount, date[3], i;
    MOV *new_movie;
    FILE *file = fopen(filename, "r");
    if (file == NULL) printf("Error opening file.\n");

    while (fgets(line, sizeof(line), file)){
        split_string(line, words, &wordCount, sep);

        if (wordCount == 9){
            char *name = words[0];
            char *director = words[1];
            int year = atoi(words[2]);
            int duration = atoi(words[3]);
            float kpr = atof(words[4]);
            float plr = atof(words[5]);
            date[0] = atoi(words[6]);
            date[1] = atoi(words[7]);
            date[2] = atoi(words[8]);

            new_movie = create_movie(name, director, year, duration, kpr, plr, date);
            add_node(ph, new_movie, ph->last);
        }
        else printf("Invalid number of attributes in line: %s\n", line);

        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }
    fclose(file);
}

void find_id(HD *ph) {
    MOV *current, *temp;
    int n, count=0,flag=1;
    printf("\nEnter the ID of the element the element before which will be deleted: ");
    scanf("%d", &n);
    current = ph->first;

    if(current->id==n){
        printf("\nError! First element of the list can't be deleted\n");
        flag=0;
    } else {
        while(current->next != NULL){
            if(n == current->next->id){
                temp = current;
                current = current->next;
                delete_node(ph,temp);
                count++;
            } else current = current->next;
        }

    }
    if(flag==1){
        if (count==0){
            printf("\nThere is no element with entered ID\n");
        } else printf("\nThe element before the entered ID element was deleted\n");
    }
}

void clear_stream(FILE *input_stream){
    if (!feof(input_stream)) {
        while (!feof(input_stream) && fgetc(input_stream) != '\n');
    }
}
