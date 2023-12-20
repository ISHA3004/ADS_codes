#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val[5];
    int count;
    struct node *childptr[5];
} *root = NULL;

struct node *createnode(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->val[0] = data;
    newnode->count = 1;
    for (int i = 0; i < 5; i++)
    {
        newnode->childptr[i] = NULL;
    }
    return newnode;
}

void insertLeafNode(int data, int pos, struct node *newnode)
{
    int j;
    for (j = newnode->count; j >= 0; j--)
    {
        if (pos == j)
            break;
        newnode->val[j] = newnode->val[j - 1];
    }
    newnode->val[pos] = data;
    newnode->count = newnode->count + 1;
}

struct node *findParent(struct node *newnode)
{
    struct node *temp = root;
    int pos = 0;
    int data = newnode->val[0];
    while (temp != NULL)
    {
        for (int i = 0; i <= temp->count; i++)
        {
            if (temp->childptr[i] == newnode)
                return temp;
        }
        for (int i = 0; i < temp->count; i++)
        {
            if (data < temp->val[i])
            {
                break;
            }
            pos++;
        }
        temp = temp->childptr[pos];
    }
}
void splitnode(int data, int pos, struct node *newnode, struct node *ncchild)
{
    int j;
    for (j = newnode->count; j >= 0; j--)
    {
        if (pos == j)
            break;
        newnode->val[j] = newnode->val[j - 1];
    }
    newnode->val[pos] = data; // 5th value inserted

    int median_val = newnode->val[2]; // finding median

    if (newnode == root)
    {
        struct node *nroot = createnode(median_val);
        nroot->childptr[0] = newnode;
        newnode->count = 2;

        struct node *newchild = createnode(newnode->val[3]);
        nroot->childptr[1] = newchild;
        newchild->val[1] = newnode->val[4];
        newchild->childptr[0] = newnode->childptr[3];
        newchild->childptr[1] = newnode->childptr[4];
        newchild->childptr[2] = ncchild;

        root = nroot;
        newnode->count = 2;
        newchild->count = 2;
    }
    else
    {
        struct node *parent = findParent(newnode);
        int i, pos = 0;
        for (i = 0; i < parent->count; i++)
        {
            if (median_val < parent->val[i])
            {
                break;
            }
            pos++;
        }

        if (parent->count < 4)
        {
            insertLeafNode(median_val, pos, parent);
            struct node *newchild = createnode(newnode->val[3]);
            newchild->val[1] = newnode->val[4];
            newchild->count = 2;

            newnode->count = 2;
            for (int i = parent->count; i >= 0; i--)
            {
                if ((pos + 1) == i)
                {
                    break;
                }
                parent->childptr[i] = parent->childptr[i - 1];
            }
            parent->childptr[pos + 1] = newchild;
        }
        else
        {
            struct node *ncchild = createnode(newnode->val[3]);
            ncchild->val[1] = newnode->val[4];
            ncchild->childptr[0] = newnode->childptr[3];
            ncchild->childptr[1] = newnode->childptr[4];
            newnode->count=2;
            ncchild->count=2;
            splitnode(median_val, pos, parent,ncchild);
        }
    }
}
void insertRec(int data, struct node *newnode)
{

    int i, pos = 0;
    for (i = 0; i < newnode->count; i++)
    {
        if (data < newnode->val[i])
        {
            break;
        }
        pos++;
    }

    // check if it is leaf node or not
    int c = 0;
    for (int j = 0; j <= newnode->count; j++)
    {
        if (newnode->childptr[j] == NULL)
            c++;
    }
    if (c == (newnode->count + 1)) // leaf node
    {
        if (newnode->count < 4)
            insertLeafNode(data, pos, newnode);
        else
        {
            splitnode(data, pos, newnode, NULL);
        }
    }
    else // not leaf node
    {
        insertRec(data, newnode->childptr[pos]);
    }
}

void insert(int data)
{
    if (root == NULL)
    {
        struct node *temp = createnode(data);
        root = temp;
        return;
    }
    insertRec(data, root);
}

void printTree(struct node *root)
{
    int i;
    if (root != NULL)
    {
        for (i = 0; i < root->count; i++)
        {
            printTree(root->childptr[i]);
            printf("%d ", root->val[i]);
        }
        printTree(root->childptr[i]);
    }
}
void main()
{
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    insert(5);
    insert(6);
    insert(7);
    insert(8);
    insert(9);
    insert(10);
    insert(11);
    insert(12);
    insert(13);
    insert(14);
    insert(15);
    insert(16);
    insert(17);

    // insert(5);
    // insert(3);
    // insert(2);
    // insert(1);
    // insert(9);
    // insert(8);
    // insert(7);
    // insert(6);
    // insert(4);

    // insert(2);
    // insert(8);
    // insert(7);
    // insert(3);
    // insert(12);
    // insert(5);
    // insert(9);
    // insert(6);
    // insert(16);
    // insert(4);

    printTree(root);
    // printf("\n");
    // printf("%d\n", root->count);
    // printf("%d\n", root->val[0]);
    // printf("%d\n", (root->childptr[0])->count);
    // printf("%d %d\n", (root->childptr[0])->val[0], (root->childptr[0])->val[1]);
    // printf("%d\n", (root->childptr[1])->count);
    // printf("%d %d\n", (root->childptr[1])->val[0], (root->childptr[1])->val[1]);
    // printf("%d ",((root->childptr[0])->childptr[0])->count);
    // printf("%d ",((root->childptr[0])->childptr[1])->count);
    // printf("%d \n",((root->childptr[0])->childptr[2])->count);
    // printf("%d %d\n",((root->childptr[0])->childptr[0])->val[0],((root->childptr[0])->childptr[0])->val[1]);
    // printf("%d %d\n",((root->childptr[0])->childptr[1])->val[0],((root->childptr[0])->childptr[1])->val[1]);
    // printf("%d %d\n",((root->childptr[0])->childptr[2])->val[0],((root->childptr[0])->childptr[2])->val[1]);
    // printf("%d ",((root->childptr[1])->childptr[0])->count);
    // printf("%d ",((root->childptr[1])->childptr[1])->count);
    // printf("%d \n",((root->childptr[1])->childptr[2])->count);
    // printf("%d %d\n",((root->childptr[1])->childptr[0])->val[0],((root->childptr[1])->childptr[0])->val[1]);
    // printf("%d %d\n",((root->childptr[1])->childptr[1])->val[0],((root->childptr[1])->childptr[1])->val[1]);
    // printf("%d %d\n",((root->childptr[1])->childptr[2])->val[0],((root->childptr[1])->childptr[2])->val[1]);
}