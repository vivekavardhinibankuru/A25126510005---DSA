#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node *root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    // duplicate values are ignored
    return root;
}

void inorder(struct Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int search(struct Node *root, int value) {
    if (root == NULL) return 0;
    if (root->data == value) return 1;
    if (value < root->data) return search(root->left, value);
    return search(root->right, value);
}

int main() {
    struct Node *root = NULL;
    int n, value, key, choice;

    printf("Enter number of values to insert: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nInorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    printf("\nEnter a value to search for: ");
    scanf("%d", &key);

    if (search(root, key)) {
        printf("%d exists in the BST\n", key);
    } else {
        printf("%d does not exist in the BST\n", key);
    }

    return 0;
}




<img width="450" height="335" alt="Image" src="https://github.com/user-attachments/assets/c87c61aa-e35e-4905-a426-c874c412ee6d" />

<img width="412" height="306" alt="Image" src="https://github.com/user-attachments/assets/a3285e97-b3a8-49ab-98f7-9be58971113c" />
