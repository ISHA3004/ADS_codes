#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 4

typedef struct Node {
    int keys[2 * ORDER - 1];
    int num_keys;
    struct Node* child[2 * ORDER];
    int is_leaf;
} Node;

Node* create_node() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->num_keys = 0;
    new_node->is_leaf = 1;
    return new_node;
}

void split_child(Node* parent, int index, Node* child) {
    Node* new_child = create_node();
    new_child->is_leaf = child->is_leaf;
    new_child->num_keys = ORDER - 1;

    for (int i = 0; i < ORDER - 1; i++) {
        new_child->keys[i] = child->keys[i + ORDER];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < ORDER; i++) {
            new_child->child[i] = child->child[i + ORDER];
        }
    }

    child->num_keys = ORDER - 1;

    for (int i = parent->num_keys; i > index; i--) {
        parent->child[i + 1] = parent->child[i];
    }

    parent->child[index + 1] = new_child;

    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[ORDER - 1];
    parent->num_keys++;
}

void insert_non_full(Node* node, int key) {
    int i = node->num_keys - 1;
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->child[i]->num_keys == 2 * ORDER - 1) {
            split_child(node, i, node->child[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insert_non_full(node->child[i], key);
    }
}

void insert(Node** root, int key) {
    if ((*root)->num_keys == 2 * ORDER - 1) {
        Node* new_root = create_node();
        new_root->is_leaf = 0;
        new_root->child[0] = *root;
        split_child(new_root, 0, *root);
        insert_non_full(new_root, key);
        *root = new_root;
    } else {
        insert_non_full(*root, key);
    }
}

int search(Node* node, int key) {
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    if (i < node->num_keys && key == node->keys[i]) {
        return 1;
    } else if (node->is_leaf) {
        return 0;
    } else {
        return search(node->child[i], key);
    }
}

void print_tree(Node* node, int level) {
    printf("Level %d, num_keys %d: ", level, node->num_keys);
    for (int i = 0; i < node->num_keys; i++) {
        printf("%d ", node->keys[i]);
    }
    printf("\n");
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            print_tree(node->child[i], level + 1);
        }
    }
}

int main() {
    Node* root = create_node();
    // int keys[] = { 5, 3, 2, 1, 9, 8, 7, 6, 4 };
    // int num_keys = sizeof(keys) / sizeof(keys[0]);
    int num_keys;
    
    printf("Enter number of keys\n");
    scanf("%d",&num_keys);
    int keys[num_keys];
    printf("Enter keys\n");
    for (int i = 0; i < num_keys; i++) 
    {
        scanf("%d",&keys[i]);
    }
    for (int i = 0; i < num_keys; i++) 
    {
        insert(&root, keys[i]);
    }

    print_tree(root, 0);

    for (int i = 0; i < num_keys; i++) {
        if (search(root, keys[i])) {
            printf("Key %d found.\n", keys[i]);
        } else {
            printf("Key %d not found.\n", keys[i]);
        }
    }

    return 0;
}
