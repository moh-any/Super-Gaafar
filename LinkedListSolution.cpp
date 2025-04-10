#include <iostream>
using namespace std;

// Define a Node class for the linked list
class Node {
public:
    int value;     // Value stored in the node
    Node* next;    // Pointer to the next node
};

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->value << " ";  // Print current node value
        current = current->next;        // Move to the next node
    }
    cout << endl;
}

// Function to add a node at the end of the list
void addNode(Node*& head, int newValue) {
    // Create the new node with the given value
    Node* newNode = new Node{newValue, nullptr};

    // If the list is empty, the new node becomes the head
    if (head == nullptr) {
        head = newNode;
        return;
    }

    // Otherwise, traverse to the last node
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // Append the new node at the end
    current->next = newNode;
}

// Function to delete the first node with a specific value
void deleteNode(Node*& head, int key) {
    // If the list is empty, do nothing
    if (head == nullptr) return;

    // If the node to delete is the head node
    if (head->value == key) {
        Node* temp = head;     // Store the current head
        head = head->next;     // Move head to the next node
        delete temp;           // Free memory of deleted node
        return;
    }

    // Traverse to find the node before the one we want to delete
    Node* current = head;
    while (current->next != nullptr && current->next->value != key) {
        current = current->next;
    }

    // If the node was found, delete it
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;  // Bypass the deleted node
        delete temp;                          // Free memory
    }
}

// Main function to test the implementation
int main() {
    // Create initial list: 1 -> 2 -> 3
    Node* head = new Node{1, nullptr};
    head->next = new Node{2, nullptr};
    head->next->next = new Node{3, nullptr};

    // Print original list
    cout << "Initial list: ";
    printList(head);

    // Add a new node with value 4
    addNode(head, 4);
    cout << "After adding 4: ";
    printList(head);

    // Delete the node with value 2
    deleteNode(head, 2);
    cout << "After deleting 2: ";
    printList(head);

    return 0;
}
