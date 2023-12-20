#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data, degree;
    struct Node *child, *sibling, *parent;
};

struct Node* newNode(int key)
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

struct Node* mergeBinomialTrees(struct Node *b1, struct Node *b2)
{
    if (b1->data > b2->data)
    {
        struct Node *temp = b1;
        b1 = b2;
        b2 = temp;
    }
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

struct Node* unionBionomialHeap(struct Node *h1, struct Node *h2)
{
    struct Node *new_heap = NULL;
    struct Node **last_ptr = &new_heap;
    while (h1 != NULL && h2 != NULL)
    {
        if (h1->degree <= h2->degree)
        {
            *last_ptr = h1;
            h1 = h1->sibling;
        }
        else
        {
            *last_ptr = h2;
            h2 = h2->sibling;
        }
        last_ptr = &((*last_ptr)->sibling);
    }
    if (h1 != NULL)
    {
        *last_ptr = h1;
    }
    else
    {
        *last_ptr = h2;
    }
    return new_heap;
}

struct Node* adjust(struct Node *heap)
{
    if (heap == NULL || heap->sibling == NULL)
    {
        return heap;
    }
    struct Node *prev = NULL;
    struct Node *curr = heap;
    struct Node *next = curr->sibling;
    while (next != NULL)
    {
        if (curr->degree != next->degree || (next->sibling != NULL && next->sibling->degree == curr->degree))
        {
            prev = curr;
            curr = next;
        }
        else if (curr->data <= next->data)
        {
            curr->sibling = next->sibling;
            mergeBinomialTrees(curr, next);
        }
        else
        {
            if (prev == NULL)
            {
                heap = next;
            }
            else
            {
                prev->sibling = next;
            }
            mergeBinomialTrees(next, curr);
            curr = next;
        }
        next = curr->sibling;
    }
    return heap;
}

struct Node* insert(struct Node *heap, int key)
{
    struct Node *temp = newNode(key);
    return unionBionomialHeap(heap, temp);
}

// struct Node* findMin(struct Node *heap)
// {
//     struct Node *min_node = heap;
//     struct Node *curr = heap;
//     while (curr != NULL)
//     {
//         if (curr->data < min_node->data)
//         {
//             min_node = curr;
//         }
//         curr = curr->sibling;
//     }
//     return min_node;
// }

// struct Node* removeMin(struct Node *heap)
// {
//     struct Node *min_node = findMin(heap);
//     struct Node *prev = NULL;
//     struct Node *curr = heap;
//     while (curr != min_node)
//     {
//         prev = curr;
//         curr = curr->sibling;
//     }
//     if (prev == NULL)
//     {
//         heap = curr->sibling;
//     }
//     else
//     {
//         prev->sibling = curr->sibling;
//     }
//     struct Node *child = curr->child;
//     while (child != NULL)
//     {
//         struct Node *next = child->sibling;
//         child->parent = NULL;
//         child->sibling = NULL;
//         heap = unionBionomialHeap(heap, child);
//         child = next;
//     }
//     free(curr);
//     heap = adjust(heap);
//     return heap;
// }

void printHeap(struct Node *heap)
{
    struct Node *curr = heap;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        printHeap(curr->child);
        curr = curr->sibling;
    }
}

int main()
{
    struct Node *heap = NULL;
    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 30);
    heap = insert(heap, 40);
    heap = insert(heap, 50);
    printf("Heap: ");
    printHeap(heap);
    printf("\n");
    //heap = removeMin(heap);
    // printf("Heap after removing minimum element: ");
    // printHeap(heap);
    printf("\n");
    return 0;
}

