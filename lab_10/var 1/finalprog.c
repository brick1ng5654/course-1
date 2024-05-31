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

void delete_movie(MHD *mph, MOV *current_movie); /* Delete node from movie list */

void delete_director(DHD *dph, MHD *mph, DIR *current_director); /* Delete node from director list*/

/* Interface --------------------------------------------------------------------*/

void menu(); /* Output main menu */

void print_head(int n); /* Output title of sheet (0 - for MOVIE LIST, 1 - for DIRECTOR LIST) */

void output_movie(MHD *mph, int n); /* Output list with MOV structure (n for PRINT HEAD) */

void output_director(DHD *dph, int n, int k) ; /* Output list with DIR structure (n for PRINT HEAD) (k for DIRECTION) */

void clear_screen(); /* Clear the console */

/* Sort, Form and other Stuff */

void split_string(char *inputString, char **words, int *wordCount, char delimiter); /* Split string by separator */

void add_movie_to_list(char *filename, MHD *mph, char sep, DHD *dph); /* Adding the movie data of file to list */

void add_director_to_list(char *filename, DHD *dph, char sep); /* Adding the director data of file to list */

void output_and_delete(DHD *dph, MHD *mph, int k); /* Output and delete last element from director list */

/* Program ----------------------------------------------------------------------*/

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
            output_director(dph,1,0);
            break;
        }

        case 3:{
            puts("\nYour selection is OUTPUT DIRECTOR LIST AND DELETE LAST ONE (IN FORWARD DIRECTON)\n");
            output_and_delete(dph,mph,0);
            getchar();
            break;
        }

        case 4:{
            puts("\nYour selection is OUTPUT DIRECTOR LIST AND DELETE LAST ONE (IN BACKWARD DIRECTION)\n");
            output_and_delete(dph,mph,1);
            getchar();
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

/* Functions --------------------------------------------------------------------*/

struct movie{
    int id;
    char *name;
    DIR *director;
    int year;
    int duration;
    float kpr;
    float plr;
    int date[3];
    struct movie *prev;
    struct movie *next;
};

struct movie_head{
    struct movie *first;
    struct movie *last;
};

struct director{
    int id;
    char *name;
    struct director *next;
    struct director *prev;
};

struct director_head{
    struct director *first;
    struct director *last;
};

MHD *make_movie_head(){
    MHD *mph=NULL;
    mph=(MHD*)malloc(sizeof(MHD));
    mph->first=NULL;
    mph->last=NULL;
    return mph;
}

DHD *make_director_head(){
    DHD *dph=NULL;
    dph=(DHD*)malloc(sizeof(DHD));
    dph->first=NULL;
    dph->last=NULL;
    return dph;
}

DIR *find_director(DHD *dph, int id){
    DIR *current = NULL;
    int flag=0;
    current = dph->first;

    do{
        if(current->id==id){
            flag=1;
        } else current=current->next;
    } while (current != dph->first && flag==0);
    return current;
}

MOV *create_movie(int id_mov, char *movie_name, int id, int movie_year, int movie_duration, float movie_kpr, float movie_plr, int watch_date[3], DHD *dph){
    MOV *new_movie = NULL;
    DIR *movie_director = NULL;
    char *name = NULL;
    new_movie = (MOV*)malloc(sizeof(MOV));
    name = (char*)malloc((strlen(movie_name) + 1) * sizeof(char));
    movie_director = (DIR *)malloc(sizeof(DIR));

    movie_director=find_director(dph, id);

    if (new_movie && name) {
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

    return new_movie;
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
        if (current_node == NULL) {
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

void add_director(DHD *dph, DIR *new_node) {
    if (dph && new_node) {
        if (dph->first == NULL) { /* Add first node of list */
            dph->first = new_node;
            dph->last = new_node;
            new_node->prev = new_node;
            new_node->next = new_node;
        } else {
            new_node->prev = dph->last;
            new_node->next = dph->first;
            dph->last->next = new_node;
            dph->first->prev = new_node;
            dph->last = new_node;
        }
    }
}

void delete_movie(MHD *mph, MOV *current_movie) {
    if (current_movie == mph->first) {
        mph->first = current_movie->next;
        if (mph->first) {
            mph->first->prev = NULL;
        } else { /* If deleted node is alone in the list */
            mph->last = NULL;
        }
    } else if (current_movie == mph->last) { /* If deleted node is the last in the list */
        mph->last = current_movie->prev;
        if (mph->last) {
            mph->last->next = NULL;
        } else { /* If deleted node is alone in the list */
            mph->first = NULL;
        }
    } else { /* If deleted node not first or last of the list */
        current_movie->prev->next = current_movie->next;
        current_movie->next->prev = current_movie->prev;
    }
    current_movie->next = NULL;
    current_movie->prev = NULL;
    free(current_movie);
}

void delete_director(DHD *dph, MHD *mph, DIR *current_director) {
    MOV *current_movie = mph->first;
    MOV *next_movie = NULL;

    while (current_movie != NULL) {
        next_movie = current_movie->next;
        if (current_movie->director == current_director) {
            delete_movie(mph, current_movie);
        }
        current_movie = next_movie;
    }

    if (current_director == dph->first) {
        if (dph->first == dph->last) {  /* If list include only one element */
            dph->first = NULL;
            dph->last = NULL;
        } else {
            dph->first = current_director->next;
            dph->last->next = dph->first;
            dph->first->prev = dph->last;
        }
    } else if (current_director == dph->last) {
        dph->last = current_director->prev;
        dph->last->next = dph->first;
        dph->first->prev = dph->last;
    } else {
        current_director->prev->next = current_director->next;
        current_director->next->prev = current_director->prev;
    }

    current_director->next = NULL;
    current_director->prev = NULL;

    free(current_director);
}

void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for SHOW THE MOVIE DATA");
    puts("2 - for SHOW THE DIRECTOR DATA");
    puts("3 - for OUTPUT DIRECTOR LIST AND DELETE LAST ONE (IN FORWARD DIRECTION)");
    puts("4 - for OUTPUT DIRECTOR LIST AND DELETE LAST ONE (IN BACKWARD DIRECTION)");
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

void output_director(DHD *dph, int n, int k) {
    DIR *current, *start;
    if(k==0) current = dph->first;
    else current = dph->last;
    print_head(n);
    start = current;
    do {
        printf("| %2d | %25s |\n", current->id, current->name);
        if(k==0) current = current->next;
        else current = current->prev;
    } while (current != start);
}

void clear_screen(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}
void split_string(char *inputString, char **words, int *wordCount, char delimiter) {
    int wordIndex = 0, wordStart=0, wordLength=0, inWord=0, i, len;

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
    /* For correct work on OS_MAC */
    for (i = 0; i < *wordCount; i++) {
        len = strlen(words[i]);
        if (words[i][len - 1] == '\r') words[i][len - 1] = '\0';
    }
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

void output_and_delete(DHD *dph, MHD *mph, int k){
    output_director(dph,1,k);
    printf("\nThe last element was deleted\n");
    if(k==0) delete_director(dph,mph,dph->last);
    else delete_director(dph,mph,dph->first);
}
