#include <stdio.h>
#include <stdlib.h>
#define c 10
int main(){
    int i,a,n,up,upi,lw,lwi,k,b[c],flag,df,dfi;

    printf("Enter array sorted by increase.\n");
    for(i=0; i<c;i++){
        printf("Enter element %i:", i);
        scanf("%i", &n);
        b[i]=n;
    }

    printf("\nEnter value of 'a':");
    scanf("%i", &a);

    printf("\na) ");
    i=0;
    while(b[i]<a){
        printf("%i;", b[i]);
        i++;
    }

    flag=0;
    for(k=1;flag==0;k++){
        for(i=0;i<c && flag==0;i++){
            while((a-k)==b[i] && flag==0){
                lw=b[i];
                lwi=i;
                flag=1;
            }
        }
    }

    flag=0;
    for(k=1;flag==0;k++){
        for(i=0;i<c && flag==0;i++){
            while((a+k)==b[i] && flag==0){
                up=b[i];
                upi=i;
                flag=1;
            }
        }
    }
    printf("\nb) Array(%i)=%i < %i < Array(%i)=%i",lwi,lw,a,upi,up);

    flag=0;
    while(abs(lw-a)>abs(up-a) && flag==0){
        df=up;
        dfi=upi;
        flag=1;
    }

    flag=0;
    while(abs(lw-a)<=abs(up-a) && flag==0){
        df=lw;
        dfi=lwi;
        flag=1;
    }

    printf("\nc) Array(%i)=%i\n", dfi,df);
    return 0;
}
