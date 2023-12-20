#include<stdio.h>

int *decToBin(int *binary,int dec)
{
    int i=0,mod;
    for(int k=0;k<20;k++)
        binary[k] = -1;
    while(dec > 0)
    {
        mod = dec%2;
        binary[i] = mod;
        i++;
        dec = dec/2;
    }
    int size = i;
    int temp;
    for(int j=0;j < size/2 ;j++)
    {
        temp = binary[size-j-1];
        binary[size-j-1] = binary[j];
        binary[j] = temp;
    }
    return binary;
}
void main()
{
    int *num,arr[20],j;
    num = decToBin(arr,24);
    int i=0;
    while(num[i] != -1)
    {
        printf("%d ",num[i]);
        i++;
    }
    printf("\n");
    int len = i;
    
    int k=0;
    while(k<5)
    {
        j=len-1;
        while(j > 0)
        {
            if(num[j] == 0)
            {
                num[j] = 1;
                break;
            }
            else
            {
                num[j] = 0;
            }
            j--;
        }
        for(int c=0;c<len;c++)
        {
            printf("%d",num[c]);
        }
        printf("\n");
        k++;
    }
}