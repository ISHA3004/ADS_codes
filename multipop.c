#include<stdio.h>
int stack[20],top=-1,n=20;

void insertStack(int key)
{
    if(top == (n-1))
    {
        printf("Stcak overflow\n");
        return;
    }
    top++;
    stack[top] = key;
    printf("%d inserted\n",key);
}

int pop()
{
    if(top == -1)
    {
        //printf("Stack underflow\n");
        return 0;
    }
    top--;
    return 1;
}
void multipop(int npop)
{
    for(int i=1;i<=npop;i++)
    {
        if(pop() == 0)
            break;
    }
}
void printStack()
{
    if(top == -1)
    {
        printf("Empty Stack\n");
        return;
    }
    for(int i=0;i<=top;i++)
    {
        printf("%d ",stack[i]);
    }
}
void main()
{
    int n;
    do
    {
        printf("Enter 1 for insert\nEnter 2 for pop/multipop\nEnter 3 to display stack\nEnter 4 to end\n");
        scanf("%d",&n);

        switch(n)
        {
            case 1:
            {
                int key;
                printf("Enter number to be inserted\n");
                scanf("%d",&key);
                insertStack(key);
                break;
            }

            case 2:
            {
                int npop;
                printf("Enter total number of pop\n");
                scanf("%d",&npop);
                multipop(npop);
                break;
            }

            case 3:
            {
                printStack();
                break;
            }

            default:
            {
                printf("Wrong choice");
            }
        }
    }while (n != 4);
}