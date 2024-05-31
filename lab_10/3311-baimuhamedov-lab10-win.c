#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxlen 128

/* Structure ------------------------------------------------------------------- */

struct movie;  /* Define structure of Movie */

struct movie_head; /* Define structure of Movie List Head*/

struct director;  /* Define structure of Director */

struct director_head; /* Define structure of Director List Head */

typedef struct movie MOV; /* Define Structured Type of Movie */

typedef struct movie_head MHD; /* Define Structured Type of Movie List Head*/

typedef struct director DIR; /* Define Structured Type of Director */

typedef struct director_head DHD; /* Define Structured Type of Director List Head*/

/* Node and List --------------------------------------------------------------- */

MHD *make_movie_head(); /* Movie Head Initialization */

DHD *make_director_head(); /* Director Head Initialization */

DIR *find_director(DHD *dph, int id); /* Get pointer to Node in Director List by ID */

MOV *create_movie(int id_mov, char *movie_name, int id, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3], DHD *dph); /* Movie Node Initialization */

DIR *create_director(int id, char *movie_director); /* Director  Node Initialization */

void add_movie(MHD *ph, MOV *new_node, MOV *current_node); /* Add new Movie Node to List */

void add_director(DHD *dph, DIR *new_node); /* Add new Director Node to List */

/* Interface --------------------------------------------------------------------*/

void menu(); /* Output main menu */

void print_head(int n); /* Output title of sheet (0 - for MOVIE LIST, 1 - for DIRECTOR LIST) */

void output_movie(MHD *mph, int n); /* Output list with MOV structure (n for PRINT HEAD) */

void output_director(DHD *dph, int n); /* Output list with DIR structure (n for PRINT HEAD) */

void clear_screen(); /* Clear the console */

/* Sort, Form and other Stuff */

void split_string(char *inputString, char **words, int *wordCount, char delimiter); /* Split string by separator */

void add_movie_to_list(char *filename, MHD *mph, char sep, DHD *dph); /* Adding the movie data of file to list */

void add_director_to_list(char *filename, DHD *dph, char sep); /* Adding the director data of file to list */

int swap_director(DHD *dph, DIR *current); /* Swap elements of director list */

void sort_director_list(DHD* dph, int option); /* Sort director list */

/* Main Program */

int main() {
    char sep;
    int option;
    DHD *dph;
    MHD *mph;

    printf("Enter the separator of structure data: ");
    scanf("%c", &sep);
    dph=make_director_head();
    mph=make_movie_head();
    add_director_to_list("struct-data2-win.txt",dph,sep);
    add_movie_to_list("struct-data-win.txt",mph,sep,dph);

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
            puts("\nYour selection is SHOW THE MOVIE DATA\n");
            getchar();
            output_movie(mph,0);
            break;
        }

        case 2:{
            puts("\nYour selection is SHOW THE DIRECTOR DATA\n");
            getchar();
            output_director(dph,1);
            break;
        }

        case 3:{
            puts("\nYour selection is SORT DIRECTOR LIST IN A-Z DIRECION\n");
            getchar();
            sort_director_list(dph, 0);
            break;
        }

        case 4:{
            puts("\nYour selection is SORT DIRECTOR LIST IN Z-A DIRECTION\n");
            getchar();
            sort_director_list(dph,1);
            break;
        }

        default:{
            puts("\nIncorrect key");
            getchar();
        }
        }
    puts("\nPress ENTER to continue");
    getchar();
    clear_screen();
    } while (option!=0);

    return 0;
}

/* Functions and their description ---------------------------------------------- */

struct movie{
    int id; /* ID of movie */
    char *name; /* Name of movie */
    DIR *director; /* Director of movie */
    int year; /* Year of movie release */
    int duration; /* duration of movie in minutes*/
    float kpr; /* Movie rating on KinoPoisk */
    float plr; /* Movie rating on my opinion */
    int date[3]; /* Day/Month/Year of watch the movie */
    struct movie *prev; /* Link to previous node */
    struct movie *next; /* Link to next node */
};

struct movie_head{
    struct movie *first;
    struct movie *last;
};

struct director{
    int id; /* ID of the director */
    char *name; /* Director name */
    struct director *next; /* Link to previous node */
    struct director *prev; /* Link to next node */
};

struct director_head{
    struct director *first;
    struct director *last;
};

MHD *make_movie_head(){
    MHD *ph=NULL; /* Define and init Head */
    ph=(MHD*)malloc(sizeof(MHD));
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}

DHD *make_director_head(){
    DHD *ph=NULL; /* Define and init Head */
    ph=(DHD*)malloc(sizeof(DHD));
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}

DIR *find_director(DHD *dph, int id){
    DIR *current = NULL;
    int flag=0;
    current = dph->first;

    while(current!=NULL && flag==0){
        if(current->id==id){
            flag=1;
        } else current=current->next;
    }
    return current;
}

MOV *create_movie(int id_mov, char *movie_name, int id, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3], DHD *dph){
    MOV *new_movie = NULL; /* Pointer to new node */
    DIR *movie_director = NULL; /* Pointer to director of movie */
    char *name = NULL;
    new_movie = (MOV*)malloc(sizeof(MOV));
    name = (char*)malloc((strlen(movie_name) + 1) * sizeof(char));
    movie_director = (DIR *)malloc(sizeof(DIR));

    movie_director=find_director(dph, id);

    if (new_movie && name) { /* Data is not empty */
        new_movie->id = id_mov;
        new_movie->name = name;
        new_movie->director = movie_director;
        new_movie->year = movie_year;
        new_movie->duration = movie_duration;
        new_movie->kpr = movie_kpr;
        new_movie->plr = movie_plr;
        memcpy(name, movie_name, strlen(movie_name) + 1);
        memcpy(new_movie->date, watch_date, sizeof(new_movie->date));
        new_movie->next = NULL;
        new_movie->prev = NULL;
    }

    return new_movie; /* Return adress of node */
}

DIR *create_director(int id, char *movie_director){
    DIR *new_director = NULL; /* Pointer to new node */
    char *director = NULL;

    new_director = (DIR*)malloc(sizeof(DIR));
    director = (char*)malloc((strlen(movie_director) + 1) * sizeof(char));

    if (new_director && director){ /* Data is not empty */
        new_director->id = id;
        new_director->name = director;
        memcpy(director, movie_director, strlen(movie_director) + 1);
        new_director->prev = NULL;
        new_director->next = NULL;
        director[strlen(movie_director)] = '\0';
    }
    return new_director; /* return adress of node */
}

void add_movie(MHD *ph, MOV *new_node, MOV *current_node){
    if (ph && new_node) {
        if (current_node == NULL) { /* Add first node of list */
            ph->first = new_node;
            ph->last = new_node;
            new_node->prev = NULL;
            new_node->next = NULL;
        } else {
            current_node->next = new_node;
            new_node->prev = current_node;
            new_node->next = NULL;
            ph->last = new_node;
        }
    }
}

void add_director(DHD *dph, DIR *new_node){
    if (dph && new_node) {
        if (dph->first == NULL) { /* Add first node of list */
            dph->first = new_node;
            new_node->prev = new_node;
            new_node->next = new_node;
        } else {
            new_node->prev = dph->first->prev;
            new_node->next = dph->first;
            dph->first->prev->next = new_node;
            dph->first->prev = new_node;
        }
    }
}

void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for SHOW THE MOVIE DATA");
    puts("2 - for SHOW THE DIRECTOR DATA");
    puts("3 - for SORT DIRECTOR LIST IN A-Z DIRECION");
    puts("4 - for SORT DIRECTOR LIST IN Z-A DIRECTION");
    printf("Enter the option: ");
}

void print_head(int n){
    if(n==0){
        printf("| %2s | %25s | %25s | %4s | %3s | %5s | %5s | %10s |\n","ID","Name","Director","Year","Dur","KPR","PLR","Watchdate");
        printf("+----+---------------------------+---------------------------+------+-----+-------+-------+------------+\n");
    } else {
        printf("| %2s | %25s |\n","ID","Director");
        printf("+----+---------------------------+\n");
    }
}

void output_movie(MHD *mph, int n) {
    MOV *current;
    current = mph->first;
    print_head(n);
    while (current!=NULL) {
        if(current->director!=NULL){
            printf("| %2d | %25s | %25s | %d | %3d | %5.1f | %5.1f | %.2d.%.2d.%d |\n", current->id, current->name, current->director->name, current->year, current->duration, current->kpr, current->plr, current->date[0], current->date[1], current->date[2]);
            current = current->next;
        }
    }
}

void output_director(DHD *dph, int n) {
    DIR *current=dph->first;
    print_head(n);

    do {
        printf("| %2d | %25s |\n", current->id, current->name);
        current = current->next;
    } while (current != dph->first);
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

void add_movie_to_list(char *filename, MHD *mph, char sep, DHD *dph){
    char line[maxlen], *words[10];
    int wordCount, date[3], i;
    MOV *new_movie;
    FILE *file = fopen(filename, "r");
    if (file == NULL) printf("Error opening file.\n");

    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        split_string(line, words, &wordCount, sep);

        if (wordCount == 10){
            int id_mov = atoi(words[0]);
            char *name = words[1];
            int id = atoi(words[2]);
            int year = atoi(words[3]);
            int duration = atoi(words[4]);
            float kpr = atof(words[5]);
            float plr = atof(words[6]);
            date[0] = atoi(words[7]);
            date[1] = atoi(words[8]);
            date[2] = atoi(words[9]);

            new_movie = create_movie(id_mov, name, id, year, duration, kpr, plr, date, dph);
            add_movie(mph, new_movie, mph->last);
        }
        else printf("Invalid number of attributes in line: %s\n", line);

        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }
    fclose(file);
}

void add_director_to_list(char *filename, DHD *dph, char sep){
    char line[maxlen], *words[2];
    int wordCount, i;
    DIR *new_director;
    FILE *file = fopen(filename, "r");
    if (file == NULL) printf("Error opening file.\n");

    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        split_string(line, words, &wordCount, sep);

        if (wordCount == 2){
            int id = atoi(words[0]);
            char *name = words[1];

            new_director = create_director(id, name);
            add_director(dph, new_director);
        }
        else printf("Invalid number of attributes in line: %s\n", line);

        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }
    fclose(file);
}

int swap_director(DHD *dph, DIR *current){
    DIR *temp=current->next;

    current->prev->next = temp;
    temp->next->prev = current;
    current->next = temp->next;
    temp->prev = current->prev;
    temp->next = current;
    current->prev = temp;

    if (dph->first == current) { /* If current was first element of head -> change head pointer to changed element */
        dph->first = temp;
    }
    return 1;
}

void sort_director_list(DHD *dph, int direction) {
    int swapped;
    DIR *current = NULL;

    if (dph == NULL){
        printf("The list is empty");
    } else {
        do {
            swapped = 0;
            current = dph->first;

            while (current->next != dph->first) {
                if (direction==0 && strcmp(current->name, current->next->name) > 0){
                    swapped = swap_director(dph,current);
                } else if (direction==1 && strcmp(current->name, current->next->name) < 0) {
                    swapped = swap_director(dph,current);
                } else {
                    current = current->next;
                }
            }
        } while (swapped == 1);
    }
    printf("The director list was sorted\n");
}
