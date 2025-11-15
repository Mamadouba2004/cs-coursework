/*
 * Week 4: Linked Lists
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Implement a complete singly linked list with all basic operations.
 * 
 * Learning Objectives:
 * - Understand node-based data structures
 * - Implement insert, delete, search operations
 * - Practice pointer manipulation
 * - Handle edge cases (empty list, single node)
 */

#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    
    // Constructor for convenience
    Node(int val) : data(val), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;
    int size;
    
public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}
    
    // Insert at the beginning - O(1)
    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
        cout << "Inserted " << value << " at head" << endl;
    }
    
    // Insert at the end - O(n)
    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
        cout << "Inserted " << value << " at tail" << endl;
    }
    
    // Insert at specific position - O(n)
    void insertAtPosition(int value, int position) {
        if (position < 0 || position > size) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if (position == 0) {
            insertAtHead(value);
            return;
        }
        
        Node* newNode = new Node(value);
        Node* temp = head;
        
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
        cout << "Inserted " << value << " at position " << position << endl;
    }
    
    // Delete by value - O(n)
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        // If head needs to be deleted
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            cout << "Deleted " << value << endl;
            return;
        }
        
        // Search for the node to delete
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        // If found, delete it
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            cout << "Deleted " << value << endl;
        } else {
            cout << value << " not found in list" << endl;
        }
    }
    
    // Delete at position - O(n)
    void deleteAtPosition(int position) {
        if (position < 0 || position >= size) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if (position == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            cout << "Deleted node at position " << position << endl;
            return;
        }
        
        Node* temp = head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
        cout << "Deleted node at position " << position << endl;
    }
    
    // Search for a value - O(n)
    bool search(int value) {
        Node* temp = head;
        int position = 0;
        
        while (temp != nullptr) {
            if (temp->data == value) {
                cout << "Found " << value << " at position " << position << endl;
                return true;
            }
            temp = temp->next;
            position++;
        }
        
        cout << value << " not found in list" << endl;
        return false;
    }
    
    // Reverse the linked list - O(n)
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        head = prev;
        cout << "List reversed" << endl;
    }
    
    // Get the middle element - O(n) using slow/fast pointer
    void findMiddle() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        Node* slow = head;
        Node* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout << "Middle element: " << slow->data << endl;
    }
    
    // Print the list - O(n)
    void display() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node* temp = head;
        cout << "List: ";
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL" << endl;
    }
    
    // Get size
    int getSize() {
        return size;
    }
    
    // Check if empty
    bool isEmpty() {
        return head == nullptr;
    }
    
    // Destructor - clean up all nodes
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        cout << "LinkedList destroyed" << endl;
    }
};

int main() {
    LinkedList list;
    
    cout << "=== Testing Insert Operations ===" << endl;
    list.insertAtHead(3);
    list.insertAtHead(2);
    list.insertAtHead(1);
    list.display();
    
    list.insertAtTail(4);
    list.insertAtTail(5);
    list.display();
    
    list.insertAtPosition(10, 2);
    list.display();
    
    cout << "\n=== Testing Search ===" << endl;
    list.search(10);
    list.search(100);
    
    cout << "\n=== Testing Size ===" << endl;
    cout << "List size: " << list.getSize() << endl;
    
    cout << "\n=== Finding Middle ===" << endl;
    list.findMiddle();
    
    cout << "\n=== Testing Delete Operations ===" << endl;
    list.deleteByValue(10);
    list.display();
    
    list.deleteAtPosition(0);
    list.display();
    
    cout << "\n=== Testing Reverse ===" << endl;
    list.reverse();
    list.display();
    
    return 0;
}

/*
 * Time Complexity Analysis:
 * - insertAtHead(): O(1)
 * - insertAtTail(): O(n)
 * - insertAtPosition(): O(n)
 * - deleteByValue(): O(n)
 * - deleteAtPosition(): O(n)
 * - search(): O(n)
 * - reverse(): O(n)
 * - display(): O(n)
 * 
 * Space Complexity: O(1) for all operations (except the list itself)
 * 
 * Key Concepts:
 * 1. Dynamic memory allocation for nodes
 * 2. Pointer manipulation for linking nodes
 * 3. Edge case handling (empty list, single node)
 * 4. Two-pointer technique for finding middle
 * 5. Proper memory cleanup in destructor
 */
