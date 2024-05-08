// Author: Sujal Bhor (21210)

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class Node {
public:
    string name;
    Node* next;
    Node* down;

    Node(string n = "") {
        name = n;
        next = nullptr;
        down = nullptr;
    }
};

class Graph {
    Node* head = nullptr;

    void add(string NodeA, string NodeB) {
        // If adjacency list is empty
        if (head == nullptr) {
            Node* node1 = new Node(NodeA);
            Node* node2 = new Node(NodeB);
            head = node1;
            node1->next = node2;
        }

        else {
            Node* currentNode = head;
            Node* prevNode = nullptr;
            bool found = false;
            while (currentNode != nullptr) {

                // If NodeA is found
                if (currentNode->name == NodeA) {
                    found = true;
                    Node* currentListNode = currentNode;
                    while (currentListNode->next != nullptr)
                        currentListNode = currentListNode->next;
                    Node* newNode = new Node(NodeB);
                    currentListNode->next = newNode;
                    break;
                }
                prevNode = currentNode;
                currentNode = currentNode->down;

            }

            // If NodeA is not found
            if (!found) {
                Node* newNode1 = new Node(NodeA);
                Node* newNode2 = new Node(NodeB);
                prevNode->down = newNode1;
                newNode1->next = newNode2;
            }
        }
    }

public:
    void addNode(string NodeA, string NodeB) {
        add(NodeA, NodeB);
        add(NodeB, NodeA);
    }

    void print() {
        Node* currentArrayNode = head->down;
        while (currentArrayNode != nullptr) {
            Node* currentListNode = currentArrayNode;
            while (currentListNode != nullptr) {
                cout << currentListNode->name << " -> ";
                currentListNode = currentListNode->next;
            }
            cout << endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void printDegrees() {
        Node* currentArrayNode = head;
        while (currentArrayNode != nullptr) {
            // Calculate out-degree
            int degree = 0;
            Node* currentListNode = currentArrayNode->next;
            while (currentListNode != nullptr) {
                degree++;
                currentListNode = currentListNode->next;
            }

            cout << currentArrayNode->name << ": Degree = " << degree << endl;
            currentArrayNode = currentArrayNode->down;
        }
    }

    void BFS(string node) {
        queue<string> Queue;
        vector<string> visited;
        Queue.push(node);
        visited.push_back(node);
        while (true) {

            if (!Queue.empty()) {
                node = Queue.front();
                Queue.pop();
                cout << node << " ";
            }
            else {
                cout << endl;
                break; //exit condition when queue is empty
            }

            Node* currentNode = head;
            bool found = false;
            while (currentNode != nullptr) {
                if (currentNode->name == node) {
                    found = true;
                    Node* currentListNode = currentNode->next;
                    while (currentListNode != nullptr) {
                        if (find(visited.begin(), visited.end(), currentListNode->name) == visited.end()) {
                            visited.push_back(currentListNode->name);
                            Queue.push(currentListNode->name);
                        }
                        currentListNode = currentListNode->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }
            if (!found) {
                cout << "Given node not in the graph" << endl;
                return;
            }
        }
    }

    void DFS(string node) {
        stack<string> Stack;
        vector<string> visited;
        Stack.push(node);
        visited.push_back(node);
        while (true) {
            if (!Stack.empty()) {
                node = Stack.top();
                Stack.pop();
                cout << node << " ";
            }
            else {
                cout << endl;
                break;
            }

            Node* currentNode = head;
            bool found = false;
            while (currentNode != nullptr) {
                if (currentNode->name == node) {
                    found = true;
                    Node* currentListNode = currentNode->next;
                    while (currentListNode != nullptr) {
                        if (find(visited.begin(), visited.end(), currentListNode->name) == visited.end()) {
                            Stack.push(currentListNode->name);
                            visited.push_back(currentListNode->name);
                        }
                        currentListNode = currentListNode->next;
                    }
                    break;
                }
                currentNode = currentNode->down;
            }
            if (!found) {
                cout << "Given node doesn't exist in the graph" << endl;
                return;
            }
        }
    }
};

int main() {
    Graph g;
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "Menu:\n";
        cout << "1. Add Edge\n";
        cout << "2. Print Graph\n";
        cout << "3. Calculate Degrees\n";
        cout << "4. Perform BFS\n";
        cout << "5. Perform DFS\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string NodeA, NodeB;
            cout << "Enter nodes to connect (space separated): ";
            cin >> NodeA >> NodeB;
            g.addNode(NodeA, NodeB);
            cout << "Edge added between " << NodeA << " and " << NodeB << endl;
            break;
        }
        case 2:
            cout << "Graph:\n";
            g.print();
            break;
        case 3:
            cout << "Degrees of each node:\n";
            g.printDegrees();
            break;
        case 4: {
            string startNode;
            cout << "Enter starting node for BFS: ";
            cin >> startNode;
            cout << "BFS traversal starting from node " << startNode << ":\n";
            g.BFS(startNode);
            break;
        }
        case 5: {
            string startNode;
            cout << "Enter starting node for DFS: ";
            cin >> startNode;
            cout << "DFS traversal starting from node " << startNode << ":\n";
            g.DFS(startNode);
            break;
        }
        case 6:
            exitMenu = true;
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
