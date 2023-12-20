#include<stdio.h>
int arr[5];

void hashKey(int key)
{
    int h1,h2,h3;
    h1 = key%2;
    h2 = key%3;
    h3 = key%5;

    arr[h1] = 1;
    arr[h2] = 1;
    arr[h3] = 1;
}
void checkKey(int key)
{
    int h1,h2,h3;
    h1 = key%2;
    h2 = key%3;
    h3 = key%5;

    if(arr[h1]==1 && arr[h2]==1 && arr[h3]==1)
    {
        printf("Key is present");
    }
    else
    {
        printf("Key not present");
    }
}
void main()
{
    int keys[] = {20,45,23,12,78};
    int i;
    int len = sizeof(keys)/sizeof(int);
    for(i=0;i<5;i++)
    {
        arr[i] = 0;
    }
    for(i=0;i<len;i++)
    {
        hashKey(keys[i]);
    }
    for(i=0;i<5;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\nCheck for key 34\n");
    checkKey(34);
}