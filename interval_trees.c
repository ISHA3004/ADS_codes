#include<stdio.h>
#include<stdlib.h>
 
struct node
{
    int low;
    int high;
    int max;
    struct node *left;
    struct node *right;
}*root = NULL;
 
struct node *createnode(int low,int high)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->low = low;
    newnode->high = high;
    newnode->max = high;
    newnode->left = NULL;
    newnode->right = NULL;
 
    return newnode;
}
 
struct node *insertRec(struct node * newnode,int low,int high)
{
    if(newnode == NULL)
    {
        struct node *temp = createnode(low,high);
        return temp;
    }
    else if(low < newnode->low)
    {
        newnode->left = insertRec(newnode->left,low,high);
    }
    else
    {
        newnode->right = insertRec(newnode->right,low,high);
    }
    return newnode;
}
 
void assignMax(struct node *root)
{
    if(root != NULL)
    {
        assignMax(root->left);
        assignMax(root->right);
 
        if(root->left == NULL && root->right == NULL)
            root->max = root->max;
        else if((root->left == NULL && root->right != NULL) && (root->right->max > root->max))
            root->max = root->right->max;
        else if((root->left == NULL && root->right != NULL) && (root->right->max < root->max))
            root->max = root->max;
        else if((root->left != NULL && root->right == NULL) && (root->left->max > root->max))
            root->max = root->left->max;
        else if((root->left != NULL && root->right == NULL) && (root->left->max < root->max))
            root->max = root->max;
        else
        {
            if(root->left->max > root->max)
            {
                if(root->left->max > root->right->max)
                    root->max = root->left->max;
                else
                    root->max = root->right->max;
            }
            else if((root->right->max > root->max))
            {
                if(root->right->max > root->left->max)
                    root->max = root->right->max;
                else
                    root->max = root->left->max;
            }
            else
                root->max = root->max;
        }
    }
}
 
struct node *isOverlapping(struct node *newnode,int low,int high)
{
    if(newnode == NULL)
        return NULL;                           //no overlap
    else if(newnode->low <= high && low <= newnode->high)
        return newnode;                          //overlap ho raha
    else
    {
        if(low > newnode->max)
            isOverlapping(newnode->right,low,high);
        else
            isOverlapping(newnode->left,low,high);
    }
}
void insertInterval(int low,int high)
{
    if(root==NULL)
    {
        struct node *temp = createnode(low,high);
        root = temp;
        return;
    }
    root = insertRec(root,low,high);
    assignMax(root);
}
 
void printTree(struct node *root)
{
    if(root != NULL)
    {
        printTree(root->left);
        printf("[%d %d]max(%d)  ",root->low,root->high,root->max);
        printTree(root->right);
    }
}
void main()
{
    insertInterval(15,20);
    insertInterval(10,30);
    insertInterval(17,19);
    insertInterval(5,20);
    insertInterval(12,15);
    insertInterval(30,40);
 
    printTree(root);
 
    struct node *temp = isOverlapping(root,6,7);
    if(temp == NULL)
        printf("\nNot overlapping\n");
    else
        printf("\noverlapping with [%d %d]",temp->low,temp->high);

    struct node *temp1 = isOverlapping(root,2,4);
    if(temp1 == NULL)
        printf("\nNot overlapping\n");
    else
        printf("\noverlapping with [%d %d]",temp->low,temp->high);
 
}