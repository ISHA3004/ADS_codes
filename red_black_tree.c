#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    int colour;     //0=red 1 = black
    struct node *left;
    struct node *right;
};
struct node *root=NULL;

struct node* createnode(int data)
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->colour = 0;
    newnode->left = NULL;
    newnode->right = NULL;
 
    return newnode;
}

struct node *findParent(struct node *root,struct node *newnode)
{
    struct node *temp = root;
    if(newnode == root)
    {
        return NULL;
    }
    while(temp != NULL)
    {
        if(temp->left !=NULL && (temp->left->data == newnode->data))
        {
            return temp;
        }
        else if(temp->right !=NULL && (temp->right->data == newnode->data))
        {
            return temp;
        }
        else if(newnode->data < temp->data)
        {
            temp=temp->left;
        }
        else if(newnode->data > temp->data)
        {
            temp=temp->right;
        }
    }
}

struct node *getUncle(struct node *parent,struct node *grandparent)
{
    if(grandparent->left == parent)
        return grandparent->right;
    else if(grandparent->right == parent)
        return grandparent->left;
    else
        return NULL;
           
}

void rotations(struct node *newnode)
{
    struct node *parent = findParent(root,newnode);
    struct node *grandparent = findParent(root,parent);
    struct node *greatgrandparent = findParent(root,grandparent);
    struct node *temp;

    if(grandparent->left == parent) //L
    {
        if(parent->left == newnode)  //LL
        {
            if(greatgrandparent == NULL)
                root = parent;
            else if(greatgrandparent->left == grandparent)
                greatgrandparent->left = parent;
            else if(greatgrandparent->right == grandparent)
                greatgrandparent->right = parent;

            temp = parent->right;
            parent->right = grandparent;
            grandparent->left = temp;

            parent->colour = 1;
            grandparent->colour = 0;
        }
        else            //LR
        {
            if(greatgrandparent == NULL)
                root = newnode;
            else if(greatgrandparent->left == grandparent)
                greatgrandparent->left = newnode;
            else if(greatgrandparent->right == grandparent)
                greatgrandparent->right = newnode;

            temp = newnode->left;
            newnode->left = parent;
            parent->right = temp;

            temp = newnode->right;
            newnode->right = grandparent;
            grandparent->left = temp;

            newnode->colour = 1;
            grandparent->colour = 0;
        }
    }
    else    //R
    {
        if(parent->right == newnode) //RR
        {
            if(greatgrandparent == NULL)
                root = parent;
            else if(greatgrandparent->left == grandparent)
                greatgrandparent->left = parent;
            else if(greatgrandparent->right == grandparent)
                greatgrandparent->right = parent;

            temp = parent->left;
            parent->left = grandparent;
            grandparent->right = temp;

            parent->colour = 1;
            grandparent->colour = 0;
        }
        else
        {
            if(greatgrandparent == NULL)
                root = newnode;
            else if(greatgrandparent->left == grandparent)
                greatgrandparent->left = newnode;
            else if(greatgrandparent->right == grandparent)
                greatgrandparent->right = newnode;

            temp = newnode->right;
            newnode->right = parent;
            parent->left = temp;

            temp = newnode->left;
            newnode->left = grandparent;
            grandparent->right = temp;

            newnode->colour = 1;
            grandparent->colour = 0;
        }
    }
}
void fixInsert(struct node *newnode)
{
    struct node *parent = findParent(root,newnode);
    struct node *grandparent = findParent(root,parent);
    struct node *uncle;

    if(parent->colour == 1)
    {
        return;
    }
    else
    {
        uncle = getUncle(parent,grandparent);
        if(uncle == NULL)  //uncle is null
            rotations(newnode);
        else if(uncle->colour == 1)  //uncle is black
            rotations(newnode);
        else if(uncle->colour == 0)                   //uncle is red
        {
            parent->colour = 1;
            uncle->colour = 1;

            if(grandparent == root)
                return;

            grandparent->colour = 0;  //gp as red

            fixInsert(grandparent);
        }
    }
    
}
struct node *insertRec(struct node *root,struct node *newnode)
{
    if(root == NULL)
    {
        return newnode;
    }
    else
    {
        if(newnode->data < root->data)
            root->left = insertRec(root->left,newnode);
        else
            root->right = insertRec(root->right,newnode);
    }
    return root;
}
void insertnode(int data)
{
    struct node *temp = createnode(data);
    if(root == NULL)
    {
        temp->colour = 1;
        root=temp;
        printf("Inserted %d\n",data);
        return;
    }
    
    root = insertRec(root,temp);
    if(temp != root)
        fixInsert(temp);

    printf("Inserted %d\n",data);
}

void printTree(struct node *root)
{
    if(root != NULL)
    {
        printTree(root->left);
        if(root->colour == 0)
            printf("%d(R) ",root->data);
        else
            printf("%d(B) ",root->data);
        printTree(root->right);
    }
}
void main()
{
    insertnode(20);
    insertnode(36);
    insertnode(14);
    insertnode(30);
    insertnode(32);
    insertnode(60);
    insertnode(50);
    insertnode(80);
    insertnode(120);
    insertnode(4);
    insertnode(2);
    insertnode(140);
    
    printTree(root);
}