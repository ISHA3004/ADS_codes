#include<stdio.h>
#include<stdlib.h>
int arr[7],n=7;

struct node
{
    int sum,low,high,min,max;
    struct node *left;
    struct node *right;
}*root=NULL;

struct node *createnode(int low,int high)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->low = low;
    newnode->high = high;
    newnode->sum=0;
    newnode->min=0;
    newnode->max=0;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

int querySegmentTreeMax(struct node* root, int low, int high) {
    if (root == NULL || high < root->low || low > root->high) {
        return -1; 
    }
    if (low <= root->low && high >= root->high) {
        return root->max; 
    }
    
    int leftMax = querySegmentTreeMax(root->left,low,high);
    int rightMax = querySegmentTreeMax(root->right,low,high);

    if(leftMax > rightMax)
    {
        return leftMax;
    }
    else
    {
        return rightMax;
    }
}

int querySegmentTreeMin(struct node* root, int low, int high) {
    if (root == NULL || high < root->low || low > root->high) {
        return 999; 
    }
    if (low <= root->low && high >= root->high) {
        return root->min; 
    }
    
    int leftMin = querySegmentTreeMin(root->left,low,high);
    int rightMin = querySegmentTreeMin(root->right,low,high);

    if(leftMin > rightMin)
    {
        return rightMin;
    }
    else
    {
        return leftMin;
    }
}

int querySegmentTree(struct node* root, int low, int high) {
    if (root == NULL || high < root->low || low > root->high) {
        return 0; 
    }
    if (low <= root->low && high >= root->high) {
        return root->sum; 
    }
    return querySegmentTree(root->left, low, high) + querySegmentTree(root->right, low, high);
}
struct node *makeTree(int low,int high)
{
    if(low == high)
    {
        struct node *temp = createnode(low,high);
        temp->sum = arr[low];
        temp->min = arr[low];
        temp->max = arr[low]; 
        return temp;
    }

    struct node *root = createnode(low,high);
    int mid = (low+high)/2;
    root->left = makeTree(low,mid);
    root->right = makeTree(mid+1,high);

    root->sum = root->left->sum + root->right->sum;
    if(root->left->min > root->right->min)
        root->min = root->right->min;
    else
        root->min = root->left->min;

    if(root->left->max > root->right->max)
        root->max = root->left->max;
    else
        root->max = root->right->max;
}

void printTree(struct node *root)
{
    if(root != NULL)
    {
        printTree(root->left);
        printf("[%d %d] Sum is %d,Min is %d,Max is %d\n",root->low,root->high,root->sum,root->min,root->max);
        printTree(root->right);
    }
}
void main()
{
    int ele[] = {23,14,56,89,45,55,92};
    for(int i=0;i<7;i++)
    {
        arr[i] = ele[i];
    }
    root = makeTree(0,n-1);
    printTree(root);
    int sum = querySegmentTree(root,1,4);
    printf("Sum is %d\n",sum);
    int qmin = querySegmentTreeMin(root,1,4);
    printf("Min is %d\n",qmin);
    int qmax = querySegmentTreeMax(root,1,4);
    printf("Max is %d",qmax);
}