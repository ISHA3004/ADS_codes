#include<stdio.h>
#include<stdlib.h>
struct node 
{
    int data,degree;
    struct node *parent,*sibling,*child;
}*h1,*h2=NULL;

struct node *createnode(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->degree = 0;
    newnode->parent= NULL;
    newnode->sibling = NULL;
    newnode->child = NULL; 

    return newnode;
}

struct node *mergeheap(struct node *h1,struct node *h2)
{
    struct node *mergeheap = NULL;
    struct node *temp1 = h1;
    struct node *temp2 = h2;
    struct node *temp3 = mergeheap;
    while(temp1 != NULL && temp2 !=NULL)
    {
        if(temp1->degree <= temp2->degree)
        {
            if(temp3 == NULL)
            {
                mergeheap = temp1;
                temp3 = temp1;
                temp1 = temp1->sibling;
            }
            else
            {
                temp3->sibling = temp1;
                temp3 = temp3->sibling;
                temp1 = temp1->sibling;
            }
        }
        else
        {
            if(temp3 == NULL)
            {
                mergeheap = temp2;
                temp3 = temp2;
                temp2 = temp2->sibling;
            }
            else
            {
                temp3->sibling = temp2;
                temp3 = temp3->sibling;
                temp2 = temp2->sibling;
            }
        }
    }
    while(temp1 != NULL)
    {
        temp3->sibling = temp1;
        temp3 = temp3->sibling;
        temp1 = temp1->sibling;
    }
    while(temp2 != NULL)
    {
        temp3->sibling = temp2;
        temp3 = temp3->sibling;
        temp2 = temp2->sibling;
    }
    return mergeheap;
}
void makeChild(struct node *par,struct node *ch)
{
    struct node *temp = par->child;
    par->child = ch;
    ch->sibling = temp;
    par->degree = par->degree +1;
    ch->parent = par;
}
struct node *unionHeap(struct node *mergeh)
{
    struct node *prev,*curr,*next;
    prev = NULL;
    curr = mergeh;
    next = curr->sibling;
    while(next != NULL)
    {
        if((curr->degree != next->degree) || ((next->sibling != NULL) && (curr->degree == next->sibling->degree)))
        {
            prev = curr;
            curr = next;
        }
        else if(curr->data <= next->data)
        {
            curr->sibling = next->sibling;
            makeChild(curr,next);
        }
        else
        {
            if(prev == NULL)
            {
                mergeh = next;
            }
            else
            {
                prev->sibling = next;
            }
            makeChild(next,curr);
            curr = next;
        }
        next = curr->sibling;
    }
    return mergeh;
}
void printHeap(struct node *curr)
{
    if(curr == NULL)
    {
        return;
    }
    
    printf("%d ",curr->data);
    printHeap(curr->child);
    printHeap(curr->sibling);
}
void main()
{
    h1 = createnode(10);
    h1->sibling = createnode(9);
    h1->sibling->degree = 1;
    h1->sibling->child = createnode(13);
    
    h2 = createnode(23);
    h2->sibling = createnode(11);
    h2->sibling->degree = 2;
    h2->sibling->child = createnode(8);
    h2->sibling->child->degree = 1;
    h2->sibling->child->child = createnode(5);
    h2->sibling->child->sibling = createnode(3);
    
    struct node *mergeh = mergeheap(h1,h2);
    printHeap(mergeh);
    printf("\n");
    struct node *uheap = unionHeap(mergeh);
    printHeap(uheap);
    // printf("\n");
    // printf("%d\n",uheap->data);
    // printf("%d\n",uheap->child->data);
    // printf("%d\n",uheap->child->sibling->data);
    // printf("%d\n",uheap->child->sibling->sibling->data);

}