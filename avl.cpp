#include <iostream>
#include <string>
using namespace std;

// Node class for AVL tree
class AVLNode {
public:
    string keyword;
    string meaning;
    AVLNode *left;
    AVLNode *right;
    int height;

    // Constructor to initialize node with keyword, meaning, left and right children, and height
    AVLNode(string key, string val) : keyword(key), meaning(val), left(nullptr), right(nullptr), height(1) {}
};

// AVL tree class
class AVLTree {
public:
    AVLNode *root;

    // Constructor to initialize AVL tree with root as nullptr
    AVLTree() : root(nullptr) {}

    // Function to get maximum of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Function to get height of a node
    int getHeight(AVLNode *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Function to get balance factor of a node
    int getBalance(AVLNode *node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Function to perform right rotation
    AVLNode *rightRotate(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Function to perform left rotation
    AVLNode *leftRotate(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Function to insert a node into AVL tree
    AVLNode *insert(AVLNode *node, string key, string val) {
        if (node == nullptr)
            return new AVLNode(key, val);

        if (key < node->keyword)
            node->left = insert(node->left, key, val);
        else if (key > node->keyword)
            node->right = insert(node->right, key, val);
        else // Duplicate keys are not allowed
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->keyword)
            return rightRotate(node);

        if (balance < -1 && key > node->right->keyword)
            return leftRotate(node);

        if (balance > 1 && key > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Function to find node with minimum value in a subtree
    AVLNode *minValueNode(AVLNode *node) {
        AVLNode *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Function to delete a node from AVL tree
    AVLNode *deleteNode(AVLNode *root, string key) {
        if (root == nullptr)
            return root;

        if (key < root->keyword)
            root->left = deleteNode(root->left, key);
        else if (key > root->keyword)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                AVLNode *temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                free(temp);
            } else {
                AVLNode *temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Function to perform inorder traversal of AVL tree
    void inorder(AVLNode *root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->keyword << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    // Function to search for a keyword in AVL tree
    AVLNode *search(AVLNode *root, string key, int &comparisons) {
        while (root != nullptr) {
            comparisons++;
            if (key < root->keyword)
                root = root->left;
            else if (key > root->keyword)
                root = root->right;
            else
                return root;
        }
        return nullptr;
    }
};

// Main function
int main() {
    AVLTree tree;
    int choice;
    string key, meaning;
    int comparisons;
    AVLNode *result; // Move the declaration of 'result' outside of the switch block

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Search for a keyword\n";
        cout << "4. Display AVL tree in ascending order\n";
        cout << "5. Display AVL tree in descending order\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword to insert: ";
                cin >> key;
                cout << "Enter meaning: ";
                cin >> meaning;
                tree.root = tree.insert(tree.root, key, meaning);
                cout << "Keyword inserted successfully.\n";
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> key;
                tree.root = tree.deleteNode(tree.root, key);
                cout << "Keyword deleted successfully.\n";
                break;
            case 3:
                cout << "Enter keyword to search: ";
                cin >> key;
                comparisons = 0;
                result = tree.search(tree.root, key, comparisons); // Assign value outside of case block
                if (result)
                    cout << "Keyword found. Meaning: " << result->meaning << endl;
                else
                    cout << "Keyword not found.\n";
                cout << "Number of comparisons: " << comparisons << endl;
                break;
            case 4:
                cout << "AVL tree in ascending order:\n";
                tree.inorder(tree.root);
                break;
            case 5:
                cout << "AVL tree in descending order:\n";
                // Call function to display in descending order
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 6);

    return 0;
}