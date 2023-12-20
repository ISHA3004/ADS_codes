#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data,npl;
    struct node *left,*right;
}*root=NULL;

struct node *createnode(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->npl = 0;
    newnode->left = newnode->right = NULL;

    return newnode;
}

struct node *mergeHeap(struct node *h1,struct node *h2)
{
    if(h1 == NULL)
        return h2;
    if(h2 == NULL)
        return h1;
    
    if(h1->data > h2->data)
    {
        struct node *temp = h1;
        h1 = h2;
        h2 = temp;
    }
    h1->right = mergeHeap(h1->right,h2);
    if(h1->right->npl > h1->left->npl)
    {
        struct node *temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }
    h1->npl = h1->right->npl + 1;
    return h1;
}
int assignNPL(struct node *lhroot)
{
    if(lhroot == NULL)
    {
        return 0;
    }

    int temp1 = 1 + assignNPL(lhroot->left);
    int temp2 = 1 + assignNPL(lhroot->right);
    //printf("%d %d %d\n",lhroot->data,temp1,temp2);
    if(temp1 > temp2)
        lhroot->npl = temp2;
    else
        lhroot->npl = temp1;

    return lhroot->npl;
}

void printHeap(struct node *curr)
{
    if(curr != NULL)
    {
        printHeap(curr->left);
        printf("%d[%d] ",curr->data,curr->npl);
        printHeap(curr->right);
    }
}
void main()
{
    struct node *lh1 = createnode(3);
    lh1->left = createnode(10);
    lh1->left->left = createnode(21);
    lh1->left->right = createnode(14);
    lh1->left->right->left = createnode(23);
    lh1->right = createnode(8);
    lh1->right->left = createnode(17);
    lh1->right->left->left = createnode(26);

    struct node *lh2 = createnode(6);
    lh2->left = createnode(12);
    lh2->left->left = createnode(18);
    lh2->left->right = createnode(24);
    lh2->left->right->left = createnode(33);
    lh2->right = createnode(7);
    lh2->right->left = createnode(37);
    lh2->right->right = createnode(19);

    assignNPL(lh1);
    assignNPL(lh2);

    printHeap(lh1);
    printf("\n");
    printHeap(lh2);
    printf("\n");
    struct node *mheap = mergeHeap(lh1,lh2);
    printHeap(mheap);
}