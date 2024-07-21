#include <stdio.h>
#include <stdlib.h>
 
// Definition of a node in the binary search tree
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;
 
// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
 
// Function to insert a node into the binary search tree
Node* insert(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}
 
// Function to search for a node in the binary search tree
Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}
 
// Function to find the node with the minimum value in a subtree
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}
 
// Function to delete a node from the binary search tree
Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
 
// Function to perform an in-order traversal of the tree
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
 
int main() {
    Node* root = NULL;
 
    // Inserting nodes into the binary search tree
    int values[] = {45, 15, 79, 90, 10, 55, 12, 20, 50};
    for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        root = insert(root, values[i]);
    }
 
    // Performing in-order traversal
    printf("In-order traversal of the binary search tree:\n");
    inorderTraversal(root);
    printf("\n");
 
    // Searching for a value
    int searchValue = 55;
    Node* result = search(root, searchValue);
    if (result != NULL) {
        printf("Element %d found in the tree.\n", searchValue);
    } else {
        printf("Element %d not found in the tree.\n", searchValue);
    }
 
    // Deleting a node
    int deleteValue = 15;
    root = deleteNode(root, deleteValue);
    printf("In-order traversal after deleting %d:\n", deleteValue);
    inorderTraversal(root);
    printf("\n");
 
    return 0;
}