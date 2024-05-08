// Author: Sujal Bhor (21210)

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree {
private:
    TreeNode* root;

    void recursiveInorder(TreeNode* node) {
        if (node == nullptr)
            return;
        recursiveInorder(node->left);
        cout << node->data << " ";
        recursiveInorder(node->right);
    }

    void nonRecursiveInorder(TreeNode* root) {
        if (root == nullptr)
            return;

        stack<TreeNode*> s;
        TreeNode* curr = root;

        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }    

    void recursivePreorder(TreeNode* node) {
        if (node == nullptr)
            return;
        cout << node->data << " ";
        recursivePreorder(node->left);
        recursivePreorder(node->right);
    }

    void nonRecursivePreorder(TreeNode* root) {
        if (root == nullptr)
            return;

        stack<TreeNode*> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode* curr = s.top();
            s.pop();
            cout << curr->data << " ";
            if (curr->right != nullptr)
                s.push(curr->right);
            if (curr->left != nullptr)
                s.push(curr->left);
        }
    }

    void recursivePostorder(TreeNode* node) {
        if (node == nullptr)
            return;
        recursivePostorder(node->left);
        recursivePostorder(node->right);
        cout << node->data << " ";
    }

    void nonRecursivePostorder(TreeNode* root) {
        if (root == nullptr)
            return;

        stack<TreeNode*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            TreeNode* curr = s1.top();
            s1.pop();
            s2.push(curr);
            if (curr->left != nullptr)
                s1.push(curr->left);
            if (curr->right != nullptr)
                s1.push(curr->right);
        }

        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }

    void recursiveSwapLeftAndRight(TreeNode* node) {
        if (node == nullptr)
            return;
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
        recursiveSwapLeftAndRight(node->left);
        recursiveSwapLeftAndRight(node->right);
    }

    int recursiveHeight(TreeNode* node) {
        if (node == nullptr)
            return 0;
        int leftHeight = recursiveHeight(node->left);
        int rightHeight = recursiveHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int recursiveLeafNodes(TreeNode* node) {
        if (node == nullptr)
            return 0;
        if (node->left == nullptr && node->right == nullptr)
            return 1;
        return recursiveLeafNodes(node->left) + recursiveLeafNodes(node->right);
    }

    int recursiveInternalNodes(TreeNode* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr))
            return 0;
        return 1 + recursiveInternalNodes(node->left) + recursiveInternalNodes(node->right);
    }

    void recursiveEraseTree(TreeNode* node) {
        if (node == nullptr)
            return;
        recursiveEraseTree(node->left);
        recursiveEraseTree(node->right);
        delete node;
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void createTree() {
        root = createTreeHelper();
    }

    TreeNode* createTreeHelper() {
        int data;
        cout << "Enter the Data of the Node (-1 to exit current sub-tree) : ";
        cin >> data;

        if (data == -1) {
            return NULL;
        }
        TreeNode* newNode = new TreeNode(data);

        cout << "Left of the Created Node : " << newNode->data << endl;
        newNode->left = createTreeHelper();
        cout << "Right of the Created Node : " << newNode->data << endl;
        newNode->right = createTreeHelper();
        return newNode;
    }

    void inorder() {
        recursiveInorder(root);
        cout << endl;
    }

    void iterativeInorder() {
        nonRecursiveInorder(root);
        cout << endl;
    }

    void preorder() {
        recursivePreorder(root);
        cout << endl;
    }

    void iterativePreorder() {
        nonRecursivePreorder(root);
        cout << endl;
    }

    void postorder() {
        recursivePostorder(root);
        cout << endl;
    }

    void iterativePostorder() {
        nonRecursivePostorder(root);
        cout << endl;
    }

    void swapLeftAndRight() {
        recursiveSwapLeftAndRight(root);
    }

    int height() {
        return recursiveHeight(root);
    }

    int countLeafNodes() {
        return recursiveLeafNodes(root);
    }

    int countInternalNodes() {
        return recursiveInternalNodes(root);
    }

    void eraseTree() {
        recursiveEraseTree(root);
        root = nullptr;
    }

    void levelOrder() {
        if (root == nullptr)
            return;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* front = q.front();
            q.pop();
            cout << front->data << " ";
            if (front->left != nullptr)
                q.push(front->left);
            if (front->right != nullptr)
                q.push(front->right);
        }
        cout << endl;
    }
};

int main() {
    BinaryTree tree;
    int choice;

    do {
        cout << "\nBinary Tree Operations Menu:\n";
        cout << "1. Create a Binary Tree\n";
        cout << "2. Recursive Inorder Traversal\n";
        cout << "3. Recursive Preorder Traversal\n";
        cout << "4. Recursive Postorder Traversal\n";
        cout << "5. NON Recursive Inorder Traversal\n";
        cout << "6. NON Recursive Preorder Traversal\n";
        cout << "7. NON Recursive Postorder Traversal\n";
        cout << "8. Swap Left and Right\n";
        cout << "9. Height of Tree\n";
        cout << "10. Count Leaf Nodes\n";
        cout << "11. Count Internal Nodes\n";
        cout << "12. Erase Tree\n";
        cout << "13. Level Order Traversal\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tree.createTree();
                cout << "Binary Tree created.\n";
                break;
            case 2:
                cout << "Inorder Traversal: ";
                tree.inorder();
                break;
            case 3:
                cout << "Preorder Traversal: ";
                tree.preorder();
                break;
            case 4:
                cout << "Postorder Traversal: ";
                tree.postorder();
                break;
            case 5:
                cout << "Inorder Traversal: ";
                tree.iterativeInorder();
                break;
            case 6:
                cout << "Preorder Traversal: ";
                tree.iterativePreorder();
                break;
            case 7:
                cout << "Postorder Traversal: ";
                tree.iterativePostorder();
                break;
            case 8:
                tree.swapLeftAndRight();
                cout << "Left and Right nodes swapped.\n";
                break;
            case 9:
                cout << "Height of Tree: " << tree.height() << endl;
                break;
            case 10:
                cout << "Number of Leaf Nodes: " << tree.countLeafNodes() << endl;
                break;
            case 11:
                cout << "Number of Internal Nodes: " << tree.countInternalNodes() << endl;
                break;
            case 12:
                tree.eraseTree();
                cout << "Tree erased.\n";
                break;
            case 13:
                cout << "Level Order Traversal: ";
                tree.levelOrder();
                break;
            case 0:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}