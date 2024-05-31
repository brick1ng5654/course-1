#include <stdio.h>
#include <stdlib.h>
#define size 25

void output(int ar[][size], int nr, int nc){
    int column,row;
    for(row=0;row<nr;row++){
        for(column=0;column<nc;column++){
            printf("%d ",ar[row][column]);
        }
        printf("\n");
    }

}

int make_column(int ar[][size],int res[size][size],int nr,int nc,int j){
    int column,row,flag;

    /*Deleting odd rows*/
    for(row=0;row<nr;row++){
        flag=1;
        for(column=1;column<nc;column++){
            if (((ar[row][column])%2)==((ar[row][column-1])%2)){
                flag=0;
            }
        }
        if (flag==1){
            for(column=0;column<nc;column++){
                res[nc-1-column][j]=ar[row][column];
            }
            j++;
        }
    }
    return j;
}


int main(){
    int ar[size][size], column, row, val, nr, nc, res[size][size],j=0;
    printf("Enter the number of Rows and Columns: ");
    scanf("%d %d", &nr, &nc);
    printf("\nEnter array:\n");
    for(row=0; row<nr;row++){
        for(column=0;column<nc;column++){
            scanf("%d", &val);
            ar[row][column]=val;
        }
    }
    printf("\nOriginal array:\n");
    output(ar,nc,nr);
    j=make_column(ar,res,nr,nc,j);
    printf("\nResult array:\n");
    output(res,nc,j);
    return 0;
}
