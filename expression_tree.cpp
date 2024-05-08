// Author: Sujal Bhor (21210)

#include <iostream>
#include <stack>
#include <cctype> // for isalnum
#include <string>

using namespace std;


class TreeNode {
public:
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char data) : data(data), left(nullptr), right(nullptr) {}
};


class ExpressionTree {
private:
    TreeNode* root;

    TreeNode* createNode(char data) {
        return new TreeNode(data);
    }

public:
    ExpressionTree() : root(nullptr) {}

    ~ExpressionTree() {
        destroyTree(root);
    }

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void buildTree(string prefix) {
        stack<TreeNode*> stk;

        for (int i = prefix.length() - 1; i >= 0; --i) {
            char ch = prefix[i];
            if(ch == ' ') {
                continue;
            }
            if (isalnum(ch)) {
                stk.push(createNode(ch));
            } else {
                TreeNode* node = createNode(ch);
                node->left = stk.top(); stk.pop();
                node->right = stk.top(); stk.pop();
                stk.push(node);
            }
        }

        root = stk.top(); stk.pop();
    }

    void postOrderTraversal() {
        if (!root) return;

        stack<TreeNode*> stk1, stk2;
        stk1.push(root);

        while (!stk1.empty()) {
            TreeNode* curr = stk1.top(); stk1.pop();
            stk2.push(curr);

            if (curr->left) stk1.push(curr->left);
            if (curr->right) stk1.push(curr->right);
        }

        while (!stk2.empty()) {
            cout << stk2.top()->data << " ";
            stk2.pop();
        }
    }

    int countOperands(TreeNode* node, int& counto) {
        if (!node) return 0;

        countOperands(node->left, counto);
        if(isalnum(node->data)) {
            cout << node->data << " ";
            counto++;
        }
        countOperands(node->right, counto);
        return counto;
    }

    int countOperators(TreeNode* node, int& counto) {
        if (!node) return 0;

        countOperators(node->left, counto);
        if(!isalnum(node->data)) {
            cout << node->data << " ";
            counto++;
        }
        countOperators(node->right, counto);
        return counto;
    }

    void displayOperandsAndOperators() {
        cout << "Operands: ";
        int counto = 0;
        int operandsCount = countOperands(root, counto);
        cout << "\nTotal operands: " << counto << endl;

        cout << "Operators: ";
        counto = 0;
        int operatorsCount = countOperators(root, counto);
        cout << "\nTotal operators: " << counto << endl;
    }
};

int main() {
    string prefix;
    cout << "Enter the prefix expression (without spaces): ";
    cin >> prefix;
    ExpressionTree tree;
    tree.buildTree(prefix);

    cout << "Non-recursive Post-order traversal: ";
    tree.postOrderTraversal();
    cout << endl;

    tree.displayOperandsAndOperators();

    return 0;
}
