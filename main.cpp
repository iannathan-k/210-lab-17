#include <iostream>
using namespace std;

// COMSC-210 | Lab 17 | Ian Kusmiantoro

const int SIZE = 7;  

struct Node {
    float value;
    Node *next;
};

void output(Node *);
void deleteNode(Node*&, int);
void insertNode(Node*&, int);
void deleteList(Node*&);
void insertAtHead(Node*&, int);
void insertAtTail(Node*&, int);
void getCurrentAndPrev(Node*, Node*&, Node*&, int);

int main() {
    Node *head = nullptr;
    int count = 0;

    // create a linked list of size SIZE with random numbers 0-99
    for (int i = 0; i < SIZE; i++) {
        int tmp_val = rand() % 100;
        insertAtHead(head, tmp_val);
    }
    output(head);

    // deleting a node
    cout << "Which node to delete? " << endl;
    output(head);
    int entry;
    cout << "Choice --> ";
    cin >> entry;

    deleteNode(head, entry);
    output(head);

    // insert a node
    Node* current = head;
    cout << "After which node to insert 10000? " << endl;
    count = 1;
    while (current) {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << "Choice --> ";
    cin >> entry;

    insertNode(head, entry);
    output(head);

    // deleting the linked list
    deleteList(head);
    output(head);

    return 0;
}

void output(Node * hd) {
    if (!hd) {
        cout << "Empty list.\n";
        return;
    }
    int count = 1;
    Node * current = hd;
    while (current) {
        cout << "[" << count++ << "] " << current->value << endl;
        current = current->next;
    }
    cout << endl;
}

void deleteNode(Node*& head, int entry) {
    Node* current = head;
    Node* prev = head;

    // traverse that many times and delete that node
    getCurrentAndPrev(head, current, prev, entry - 1);
    // at this point, delete current and reroute pointers
    if (current) {  // checks for current to be valid before deleting the node
        prev->next = current->next;
        delete current;
        current = nullptr;
    }

    // Assuming that we don't concern ourselves with deleting the head node,
    // As the current code leads to a memory leak, but the original code didn't include
    // Handling, so I'm carrying that over.
}

void insertNode(Node*& head, int entry) {
    Node* current = head;
    Node* prev = head;

    getCurrentAndPrev(head, current, prev, entry);

    //at this point, insert a node between prev and current
    Node * newnode = new Node;
    newnode->value = 10000;
    newnode->next = current;
    prev->next = newnode;
}

void deleteList(Node*& head) {
    Node* current = head;

    while (current) {
        head = current->next;
        delete current;
        current = head;
    }
    head = nullptr;
}

void insertAtHead(Node*& head, int val) {
    Node *new_node = new Node;

    // adds node at head
    if (!head) { // if this is the first node, it's the new head
        head = new_node;
        new_node->next = nullptr;
        new_node->value = val;
    } else { // its a second or subsequent node; place at the head
        new_node->next = head;
        new_node->value = val;
        head = new_node;
    }
}

void insertAtTail(Node*& head, int val) {
    Node* new_node = new Node;
    Node* current = head;

    // If its the first node, it becomes the new head
    if (!head) {
        head = new_node;
        new_node->next = nullptr;
        new_node->value = val;
    } else {
        // Traverse to the end of the linked list
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = new_node;
        new_node->next = nullptr;
        new_node->value = val;
    }
}

void getCurrentAndPrev(Node* head, Node*& current, Node*& prev, int entry) {
    // Current and prev are passed by reference so we can change them
    current = head;
    prev = head;

    for (int i = 0; i < entry; i++)
        if (i == 0)
            current = current->next;
        else {
            current = current->next;
            prev = prev->next;
        }

    // Assuming that the entry is always valid, because the original code
    // Didn't include validation checking for whether entry is within range
    // So I'm also carrying that over.
}