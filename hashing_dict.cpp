// Author: Sujal Bhor (21210)

#include <bits/stdc++.h>
using namespace std; 

class Node {
public:
    int key;
    string value;
    Node *next = nullptr;
    Node(int k, string v) : key(k), value(v), next(nullptr) {}
};

class Dictionary {
private:
    Node **table;
    int tableSize;

    int hash(int key) {
        return (3 * key + 5) % tableSize;
    }

    void insertLL(Node *headNode, int key, string value) {
        Node *currentNode = headNode;
        while (currentNode->next != nullptr)
            currentNode = currentNode->next;
        Node *newNode = new Node(key, value);
        currentNode->next = newNode;
    }

    Node *findLL(Node *headNode, int key) {
        Node *currentNode = headNode;
        while (currentNode != nullptr) {
            if (currentNode->key == key) {
                return currentNode;
            }
            currentNode = currentNode->next;
        }
        return nullptr;
    }

    void printLL(Node *headNode) {
        Node *currentNode = headNode;
        while (currentNode != nullptr) {
            cout << "(" << currentNode->key << ", " << currentNode->value << ") ->";
            currentNode = currentNode->next;
        }
    }

    void deleteLL(int index, Node *headNode, int key) {
        if (headNode == NULL)
            cout << "No such record exists to be deleted!" << endl;
        else if (headNode->key == key) {
            Node *nextNode = headNode->next;
            delete table[index];
            table[index] = nextNode;
            cout << "Deleted." << endl;
        } 
        else {
            Node *currentNode = headNode;
            Node *prevNode = NULL;
            while (currentNode != nullptr) {
                if (currentNode->key == key)
                    break;
                prevNode = currentNode;
                currentNode = currentNode->next;
            }

            if (currentNode != nullptr) {
                prevNode->next = currentNode->next;
                delete currentNode;
            } else
                cout << "No such element" << endl;
        }
    }

public:
    Dictionary(int n) : tableSize(n) {
        table = new Node *[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    void insert(int key, string value) {
        int hashAddress = hash(key);
        if (table[hashAddress] == nullptr) {
            table[hashAddress] = new Node(key, value);
        } else {
            insertLL(table[hashAddress], key, value);
        }
    }

    void display() {
        for (int i = 0; i < tableSize; i++) {
            cout << "|-------|\n|   " << i << "   | -> ";
            printLL(table[i]);
            cout << endl;
        }
        cout << "|_______|";
        cout << endl << endl;
    }

    void search(int key) {
        int hashAddress = hash(key);
        Node *foundNode = findLL(table[hashAddress], key);
        if (foundNode == nullptr)
            cout << "No record found" << endl;
        else {
            cout << "\nKey: " << key << endl;
            cout << "Value: " << foundNode->value << endl;
        }
    }

    void del(int key) {
        int hashAddress = hash(key);
        deleteLL(hashAddress, table[hashAddress], key);
    }
};

int main() {
    Dictionary dict(10);

    while (true) {
        cout << "1. Insert key:value pair" << endl;
        cout << "2. Search for value with key" << endl;
        cout << "3. Delete the key:value pair" << endl;
        cout << "4. Display the dictionary" << endl;
        cout << "Enter your choice (any other input to exit): ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int key;
            string value;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter corresponding value: ";
            cin >> value;
            dict.insert(key, value);
        } else if (choice == 2) {
            int key;
            cout << "Enter key: ";
            cin >> key;
            dict.search(key);
        } else if (choice == 3) {
            int key;
            cout << "Enter key: ";
            cin >> key;
            dict.del(key);
        } else if (choice == 4) {
            dict.display();
        } else
            break;
    }

    return 0;
}
