#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define size 50
int main(){
    int n,j,val,a[size][size],mx,mn,b[size][size],row,column,diff;
    mx=INT_MIN, mn=INT_MAX,j=0;

    printf("Enter the number of columns: ");
    scanf("%d", &n);

/*Entering null row*/
    printf("\nEnter original two-dimensional array:\n");
    for(column=0;column<n;column++){
        scanf("%d",&val);
        a[0][column]=val;
        if(a[0][column]>mx){
            mx=a[0][column];
        }
        if (a[0][column]<mn){
            mn=a[0][column];
        }
    }
    if((mx-mn)>0){
        diff=(mx-mn);
    } else {
        diff=1;
    }

/*Entering other rows*/
    for(row=1;row<diff;row++){
        for(column=0;column<n;column++){
            scanf("%d",&val);
            a[row][column]=val;
        }
    }

/*Check condition*/
    for(column=0;column<n;column++){
        if (abs((a[diff-1][column]))%2==1){
            for(row=0;row<diff;row++){
                b[j][row]=a[row][column];
            }
            j++;
        }
    }
/*Output array*/
    printf("\nResult two-dimensional array:\n");
    for(row=0;row<j;row++){
        for(column=0;column<diff;column++){
            printf("%d ", b[row][column]);
        }
        printf("\n");
    }
    return 0;
}
