#include<stdio.h>
#include<stdlib.h>
int ph[11],*bph[11],n=11;

void hashToPrimary(int key)
{
    int h1 = (7*key+5)%n;
    ph[h1] = ph[h1] +1;
}
void hashToSecondary(int key)
{
    int h1 = (7*key+5)%n;
    int h2 = (11*key)%(ph[h1]*ph[h1]);
    int *temp = bph[h1];
    temp[h2] = key;
}
void makeSecondaryTable()
{
    for(int i=0;i<n;i++)
    {
        int *ptr = (int *)calloc(ph[i]*ph[i] , sizeof(int));
        bph[i] = ptr;
    }
}
void printSecondary()
{
    for(int i=0;i<n;i++)
    {
        printf("%d-->",ph[i]);
        int *temp1 = bph[i];
        for(int j=0;j<ph[i]*ph[i];j++)
        {
            printf("%d ",temp1[j]);
        }
        printf("\n");
    }
}
void main()
{
    int key[] = {10,22,31,37,40,52,60,70,72,75}; 
    for(int i=0;i<n;i++)
    {
        ph[i] = 0;
    }
    int keysize = sizeof(key)/sizeof(int);
    for(int i=0;i<keysize;i++)
    {
        hashToPrimary(key[i]);
    }
        
    makeSecondaryTable();

    for(int i=0;i<keysize;i++)
    {
        hashToSecondary(key[i]);
    }

    printSecondary();

}