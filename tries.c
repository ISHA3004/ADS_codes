#include<stdio.h>
#include<stdlib.h>
struct trienode
{
    char data;
    int flag;
    struct trienode *childnode[26];
};

struct trienode *createnode(char data)
{
    struct trienode *newnode = (struct trienode*)malloc(sizeof(struct trienode));
    newnode->data = data;
    newnode->flag = 0;
    for(int i=0;i<26;i++)
    {
        newnode->childnode[i] = NULL;
    }
    return newnode;
}

struct trienode *insertnode(struct trienode *root,char *word)
{
    struct trienode *temp = root;
    int i=0;
    while(word[i]!='\0')
    {
        int index = (int)word[i] - 'a';
        //printf("Index is %d with data %c\n",index,word[i]);
        if(temp->childnode[index] == NULL)
            temp->childnode[index] = createnode(word[i]);
        temp = temp->childnode[index];
        i++;
    }
    temp->flag = 1;
    printf("Word inserted\n");
    return root;
}

int searchword(struct trienode *root,char *word)
{
    
    struct trienode *temp = root;
    int i=0;
    while(word[i]!='\0')
    {
        int index = (int)word[i] - 'a';
        //printf("Index is %d with data %c\n",index,temp->data);
        if(temp->childnode[index] == NULL)
        {
            return 0;
        }
        temp = temp->childnode[index];
        i++;
    }
    if(temp != NULL && temp->flag == 1)
        return 1;
    return 0;
}

int hasChildren(struct trienode* curr)
{
    for (int i = 0; i < 26; i++)
    {
        if (curr->childnode[i]) {
            return 1;       // child found
        }
    }
 
    return 0;
}

void deleteword(struct trienode *root,char *word)
{
    struct trienode *temp = root;
    int i=0;
    struct trienode *stack[20];int top=-1;
    while(word[i] != '\0')
    {
        int index = (int)word[i] - 'a';
        temp = temp->childnode[index];
        top = top+1;
        i++;
        stack[top] = temp;
    }
    temp->flag = 0;
    for(int j=top;j>=0;j--)
    {
        struct trienode *temp1 = stack[j];
        int hc = hasChildren(temp1);
        if(hc==1)
        {
            break;
        }
        else
        {
            struct trienode *temp2 = stack[j-1];
            for(int k=0;k<26;k++)
            {
                printf("%d ",k);
                if(temp2->childnode[k] == temp1)
                {
                    temp2->childnode[k] = NULL;
                    free(temp1);
                    break;
                }
            }
        }
    }

}

void main()
{
    struct trienode *root = createnode('\0');
    root = insertnode(root,"isha");
    root = insertnode(root,"ishaani");
    root = insertnode(root,"kishan");
    root = insertnode(root,"idli");
    int ans = searchword(root,"ishika");
    if(ans)
        printf("Search successfull\n");
    else
        printf("Not success\n");

    deleteword(root,"idli");
    printf("Word deleted\n");
    int ans1 = searchword(root,"idli");
    if(ans1)
        printf("Search successfull\n");
    else
        printf("Not success\n");

}