#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct node {
    int key;
    struct node *left, *right;
};

struct node *newNode(int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inOrder(struct node *root) {
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d \n", root->key);
        inOrder(root->right);
    }
}

void preOrder(struct node *root) {
    if (root == NULL)
        return;

    printf("%d \n", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

struct node *insert(struct node *node, int key) {
    if (node == NULL)
        return newNode(key);
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    /* return the (unchanged) node pointer */
    return node;
}

struct node *minValueNode(struct node *node) {
    struct node *current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

void postOrder(struct node *root) {
    if (root == NULL)
        return;

    postOrder(root->left);

    postOrder(root->right);

    printf("%d \n", root->key);
}

/*------E1----------*/
struct node *ancestro(struct node *root, int n1, int n2) {
    if (root == NULL) return NULL;
    
    if (root->key > n1 && root->key > n2) return ancestro(root->left, n1, n2);

    if (root->key < n1 && root->key < n2) return ancestro(root->right, n1, n2);
    
    return root;
}

/*-----E2-------*/
int findLevel(struct node *root, int k, int level) {
    if (root == NULL) return -1;
    
    if (root->key == k) return level;

    int left = findLevel(root->left, k, level + 1);
    if (left == -1) return findLevel(root->right, k, level + 1);

    return left;
}


int findDistance(node *root, int a, int b) {
    struct node *ancestro2 = ancestro(root, a, b);
    int d1 = findLevel(ancestro2, a, 0);
    int d2 = findLevel(ancestro2, b, 0);

    return d1 + d2;
}

int main() {
    int n1 = 1, n2 = 13, n3 = 1, n4 = 7;
    struct node *root = NULL;
    
    root = insert(root, 50);
    
    insert(root, 8);
    insert(root, 3);
    insert(root, 10);
    insert(root, 1);
    insert(root, 6);
    insert(root, 14);
    insert(root, 13);
    insert(root, 4);
    insert(root, 7);

    struct node *t = ancestro(root, n1, n2);
    printf("Ancestro de %d y %d es %d \n", n1, n2, t->key);
    cout << "Distancia entre " << n3 << " y " << n4 << " es " << findDistance(root, n3, n4) << endl;

    return 0;
}