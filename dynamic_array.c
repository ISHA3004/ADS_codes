#include<stdio.h>
#include<stdlib.h>

int size=1;
int *ptr;
int c=0;

int *createArray(int nsize)
{
    int *ptr = (int *)calloc(nsize,sizeof(int));
    return ptr;
}

void insert(int key)
{
    if(c != size)
    {
        printf("Size is %d\n",size);
        ptr[c] = key;
        c++;
    }
    else
    {
        int *temp = createArray(size*2);
        size = size*2;
        printf("Size is %d\n",size);
        for(int j=0;j<(size-1);j++)
        {
            temp[j] = ptr[j];
            printf("%d ",temp[j]);
        }
        printf("\n");
        temp[c] = key;
        ptr=temp;
        c++;
    }
}
void main()
{
    int n;
    ptr = (int *)calloc(size,sizeof(int));
    int keys[] = {1,2,3,4,5,6,7,8,9,10,11};
    
    int len = sizeof(keys)/sizeof(int);
    //printf("Hello\n");
    for(int i=0;i<len;i++)
    {
        insert(keys[i]);
    }
    printf("%d\n",size);
    for(int i=0;i<size;i++)
    {
        printf("%d ",ptr[i]);
    }
    
}