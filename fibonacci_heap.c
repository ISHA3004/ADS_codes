#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    int degree;  //number of childern
    struct node *parent,*child,*prev,*next;
};
struct node *createnode(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->degree = 0;
    newnode->parent = newnode->child = newnode->prev = newnode->next = NULL;

    return newnode;
}

struct node *mergeFibHeap(struct node *r1,struct node *r2)
{
    struct node *temp1,*temp2;
    temp1 = r1;
    temp2 = r2;

    struct node *temp3=r1->prev,*temp4=r2->prev;
    r1->prev->next = r2;
    temp4 = r1->prev;
    temp3 = r2->prev;
    r2->prev->next = r1;

    if(temp1->data > temp2->data)
        return temp2;
    else
        return temp1;
    
}
void printFibHeap(struct node *fmin)
{
    struct node *ptr = fmin;
    printf("%d ",ptr->data);
    ptr = ptr->next;
    while(ptr != fmin)
    {
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
}
void main()
{
    struct node *min1 = createnode(17);
    min1->next = createnode(23);
    min1->prev = createnode(24);
    min1->next->child = createnode(30);
    min1->prev->child = createnode(46);
    min1->prev->child->parent = min1->prev;
    min1->next->child->parent = min1->next;
    min1->next->next = min1->prev;
    min1->prev->prev = min1->next;
    min1->next->prev = min1;
    min1->prev->next = min1;

    //printf("\n%d",min1->next->data);
    struct node *min2 = createnode(3);
    min2->next = createnode(21);
    min2->prev = createnode(7);
    min2->next->child = createnode(35);
    min2->prev->child = createnode(10);
    min2->prev->child->parent = min2->prev;
    min2->next->child->parent = min2->next;
    min2->next->next = min2->prev;
    min2->prev->prev = min2->next;
    min2->next->prev = min2;
    min2->prev->next = min2;

    printf("hello\n");
    struct node *mfheap = mergeFibHeap(min1,min2);
    printf("Min element is %d\n",mfheap->data);
    printFibHeap(mfheap);
    //printf("\n%d",mfheap->prev->prev->prev->prev->data);
}