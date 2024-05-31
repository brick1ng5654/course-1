#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 128

/* !!! Need to remove pedantic mode !!! */

/* Structure ------------------------------------------------------------------------------*/

struct MACaddress{
    unsigned octet1:8;
    unsigned octet2:8;
    unsigned octet3:8;
    unsigned octet4:8;
    unsigned octet5:8;
    unsigned octet6:8;
}; /* Define structure of MAC-address */

typedef struct MACaddress MAC; /* Define structured type of MAC-address */

struct manuf; /* Define structure of manufacturer */

typedef struct manuf MNF; /* Define structured type of manufacturer */

/* Interface ------------------------------------------------------------------------------*/

void menu(); /* Output main menu */

void output_mac(MAC address); /* Output MAC-address */

void print_head(); /* Output title of sheet of manufacturers */

void output_array(MNF *ARR[], int n); /* Output array MNF type */

void clear_screen(); /* Clear the console */

/* Sort, Form and other Stuff -----------------------------------------------------------*/

void input_mac(MAC *address); /* Input MAC-address */

int count_of_lines(char *filename); /* Count of lines in file */

void split_string(char *inputString, char **words, int *wordCount, char delimiter); /* Split string by separator */

void add_to_array(MNF *ARR[], char *filename, int n, char sep); /*  Adding the data of file to array */

void change_manuf(MNF *ARR[], MAC *address, int i); /* Change manufacturer of MAC-address */

/* Main program ------------------------------------------------------------------------*/

int main(){
    int i;
    MNF **manuf = NULL;
    MAC address = {0};
    i=count_of_lines("manuf-win.txt");
    manuf=(MNF**)malloc(i*sizeof(MNF*));
    add_to_array(manuf,"manuf-win.txt",i,';');

    printf("Entering the MAC-Address\n\n");
    input_mac(&address);
    printf("\n");
    output_mac(address);
    printf("\n");
    change_manuf(manuf,&address,i);
    return 0;
}

/* Functions ---------------------------------------------------------------------------*/

struct manuf{
    char *name;
    unsigned octet1:8;
    unsigned octet2:8;
    unsigned octet3:8;
};

void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for SHOW THE MANUFACTORER INFO");
    puts("2 - for INPUT MAC-ADDRESS");
    puts("3 - for SHOW MAC-ADDRESS");
    puts("4 - for CHANGE MFG CODE IN MAC-ADDRESS");
    printf("Enter the option: ");
}

void output_mac(MAC address){
    printf("MAC-address: %02X:%02X:%02X:%02X:%02X:%02X\n", address.octet1, address.octet2, address.octet3, address.octet4, address.octet5, address.octet6);
}

void print_head(){
        printf("| %6s | %25s | %8s | %8s | %8s | %6s |\n","Number","Manufacturer Name","Octet 1","Octet 2","Octet 3","OUI");
        printf("+--------+---------------------------+----------+----------+----------+--------+\n");
}

void output_array(MNF *ARR[], int n){
    int i;
    print_head();
    for(i=0;i<n;i++){
        printf("| %6d | %25s | %8.2X | %8.2X | %8.2X | %2.2X%2.2X%2.2X |\n",i+1, ARR[i]->name, ARR[i]->octet1, ARR[i]->octet2, ARR[i]->octet3, ARR[i]->octet1, ARR[i]->octet2, ARR[i]->octet3);
    }
}

void clear_screen(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void input_mac(MAC *address){
    char input[MAXLEN], *octet[6];
    unsigned int a;
    int i, wordCount;
    printf("Enter the MAC-Address (6 Octets separated by space): ");
    fgets(input, MAXLEN, stdin); /* Read the string */
    input[strcspn(input, "\n")] = 0; /* Delete symbol of 'enter' */
    split_string(input,octet,&wordCount,' ');
    for (i=0; i<6; i++) {
        if (sscanf(octet[i], "%x", &a) != 1 || a > 255 || strlen(octet[i])>2) printf("Invalid Input. Octet%d will be written incorrectly in the MAC address.\n", i+1);

        switch (i) {
            case 0: address->octet1 = (unsigned char)a; break;
            case 1: address->octet2 = (unsigned char)a; break;
            case 2: address->octet3 = (unsigned char)a; break;
            case 3: address->octet4 = (unsigned char)a; break;
            case 4: address->octet5 = (unsigned char)a; break;
            case 5: address->octet6 = (unsigned char)a; break;
        }
    }
}

int count_of_lines(char *filename) {
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
    /* For correct work on MAC and ?LINUX? */
    for (i = 0; i < *wordCount; i++) {
        len = strlen(words[i]);
        if (words[i][len - 1] == '\r') words[i][len - 1] = '\0';
    }
}

void add_to_array(MNF *ARR[], char *filename, int n, char sep) {
    char line[MAXLEN];
    char **TMP = NULL;
    int wordCount = 0, i, j;
    unsigned int temp_octet1, temp_octet2, temp_octet3;

    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        for (i = 0; i < n; i++) {
            fgets(line, MAXLEN, file);
            TMP = (char **)malloc(MAXLEN * sizeof(char *));
            split_string(line, TMP, &wordCount, sep);
            if (TMP != NULL) {
                ARR[i] = (MNF*)malloc(sizeof(MNF));

                ARR[i]->name = (char *)malloc(strlen(TMP[0]) + 1);
                strcpy(ARR[i]->name, TMP[0]);

                sscanf(TMP[1], "%x", &temp_octet1);
                sscanf(TMP[2], "%x", &temp_octet2);
                sscanf(TMP[3], "%x", &temp_octet3);

                ARR[i]->octet1 = temp_octet1;
                ARR[i]->octet2 = temp_octet2;
                ARR[i]->octet3 = temp_octet3;
            }
            for (j = 0; j < wordCount; j++) {
                free(TMP[j]);
            }
            free(TMP);
        }
    } else {
        printf("Error opening the file.\n");
    }
    fclose(file);
}

void change_manuf(MNF *ARR[], MAC *address, int i){
    char input[MAXLEN];
    int number;
    output_array(ARR,i);
    do{
        printf("\nEnter the number of manufacturer that will replace your current manufacturer (1-%d): ",i);
        fgets(input, MAXLEN, stdin); /* Read the string */
        input[strcspn(input, "\n")] = 0; /* Delete symbol of 'enter' */
        if (sscanf(input, "%i", &number) == 1 && number < i){
            address->octet1 ^= address->octet1;
            address->octet2 ^= address->octet2;
            address->octet3 ^= address->octet3;
            printf("\nManufacturer of your MAC-address was replaced. Current ");
            address->octet1 = ARR[number-1]->octet1;
            address->octet2 = ARR[number-1]->octet2;
            address->octet3 = ARR[number-1]->octet3;
            output_mac(*address);
        } else printf("\nManufacturer with entered number does not exist. Please try again!\n");
    } while (sscanf(input, "%i", &number) != 1 || number > i);
}

