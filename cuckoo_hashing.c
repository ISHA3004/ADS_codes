#include<stdio.h>
int arr1[3],arr2[5];

int hash1(int val)
{
    return val%3;
}
int hash2(int val)
{
    return val%5;
}
void place_key(int key)
{
    int k_curr = key;
    int c=1;

    // while(c != 5)
    // {
    //     int hash_1 = hash1(k_curr);  
    //     int temp = arr1[hash_1];       
    //     if(arr1[hash_1] == -1)
    //     {
    //         arr1[hash_1] = k_curr;
    //         return;
    //     }
    //     else
    //     {
    //         int hash_2 = hash2(arr1[hash_1]);   
    //         if(arr2[hash_2] == -1)
    //         {
    //             arr1[hash_1] = k_curr;  
    //             arr2[hash_2] = temp;     
    //             return;
    //         }
    //         else
    //         {
    //             k_curr = temp;
    //             c++;
    //         }
    //     }
    // }
    // if(c==5)
    //     printf("%d not placed\n",key);

    int ttc = 1;
    while(c!=5)
    {
        if(ttc == 1)
        {
            int h1 = hash1(k_curr);
            int temp = arr1[h1];
            if(arr1[h1] == -1)
            {
                arr1[h1] = k_curr;
                return;
            }
            arr1[h1] = k_curr;
            k_curr = temp;
            ttc = 2;
            c++;
        }
        else
        {
            int h2 = hash2(k_curr);
            int temp = arr2[h2];
            if(arr2[h2] == -1)
            {
                arr2[h2] = k_curr;
                return;
            }
            arr2[h2] = k_curr;
            k_curr = temp;
            ttc = 1;
            c++;
        }
    }
}
void main()
{
    //int keys[] = {20,12,34,68,45,16,32};   
    int keys[] = {42,17,8,35,23,50,11,31,19,7};
    //int keys[] = {16,44,34,20,13};
    int klen = sizeof(keys)/sizeof(int);
    int hash_val;

    for(int i=0;i<5;i++)
    {
        arr1[i] = -1;
        arr2[i] = -1;
    }
    for(int i=0;i<klen;i++)
    {
        place_key(keys[i]);
    }
    printf("Table 1\n");
    for(int i=0;i<3;i++)
    {
        printf("%d ",arr1[i]);
    }
    printf("\nTable 2\n");
    for(int i=0;i<5;i++)
    {
        printf("%d ",arr2[i]);
    }
}