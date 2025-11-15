/*
 * Week 6: Stacks and Queues
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Implement Stack and Queue data structures and demonstrate
 * their applications with real-world examples.
 * 
 * Learning Objectives:
 * - Understand LIFO (Stack) and FIFO (Queue) principles
 * - Implement both using arrays and linked lists
 * - Apply stacks and queues to solve problems
 */

#include <iostream>
#include <string>
using namespace std;

// ==================== STACK IMPLEMENTATION ====================

class Stack {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int topIndex;
    
public:
    Stack() : topIndex(-1) {}
    
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++topIndex] = value;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return arr[topIndex--];
    }
    
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return arr[topIndex];
    }
    
    bool isEmpty() {
        return topIndex == -1;
    }
    
    bool isFull() {
        return topIndex == MAX_SIZE - 1;
    }
    
    int size() {
        return topIndex + 1;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// ==================== QUEUE IMPLEMENTATION ====================

class Queue {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int frontIndex;
    int rearIndex;
    int count;
    
public:
    Queue() : frontIndex(0), rearIndex(-1), count(0) {}
    
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % MAX_SIZE;
        arr[rearIndex] = value;
        count++;
    }
    
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int value = arr[frontIndex];
        frontIndex = (frontIndex + 1) % MAX_SIZE;
        count--;
        return value;
    }
    
    int front() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return arr[frontIndex];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == MAX_SIZE;
    }
    
    int size() {
        return count;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue (front to rear): ";
        for (int i = 0; i < count; i++) {
            cout << arr[(frontIndex + i) % MAX_SIZE] << " ";
        }
        cout << endl;
    }
};

// ==================== APPLICATIONS ====================

// Application 1: Check if parentheses are balanced
bool isBalanced(string expression) {
    Stack s;
    
    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.isEmpty()) return false;
            
            char top = s.pop();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return s.isEmpty();
}

// Application 2: Reverse a string using stack
string reverseString(string str) {
    Stack s;
    
    // Push all characters to stack
    for (char ch : str) {
        s.push(ch);
    }
    
    // Pop all characters to get reversed string
    string reversed = "";
    while (!s.isEmpty()) {
        reversed += (char)s.pop();
    }
    
    return reversed;
}

// Application 3: Simulate a print queue
void simulatePrintQueue() {
    Queue printQueue;
    
    cout << "\n=== Print Queue Simulation ===" << endl;
    
    // Add print jobs
    cout << "Adding print jobs..." << endl;
    printQueue.enqueue(101);  // Job ID 101
    printQueue.enqueue(102);
    printQueue.enqueue(103);
    printQueue.display();
    
    // Process print jobs
    cout << "\nProcessing jobs..." << endl;
    while (!printQueue.isEmpty()) {
        int jobId = printQueue.dequeue();
        cout << "Printing job #" << jobId << endl;
    }
}

int main() {
    // Test Stack
    cout << "=== STACK OPERATIONS ===" << endl;
    Stack stack;
    
    cout << "Pushing: 10, 20, 30, 40, 50" << endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    stack.display();
    
    cout << "\nPeek: " << stack.peek() << endl;
    cout << "Size: " << stack.size() << endl;
    
    cout << "\nPopping elements:" << endl;
    while (!stack.isEmpty()) {
        cout << "Popped: " << stack.pop() << endl;
    }
    
    // Test Queue
    cout << "\n\n=== QUEUE OPERATIONS ===" << endl;
    Queue queue;
    
    cout << "Enqueuing: 1, 2, 3, 4, 5" << endl;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.display();
    
    cout << "\nFront: " << queue.front() << endl;
    cout << "Size: " << queue.size() << endl;
    
    cout << "\nDequeuing 2 elements:" << endl;
    cout << "Dequeued: " << queue.dequeue() << endl;
    cout << "Dequeued: " << queue.dequeue() << endl;
    queue.display();
    
    // Test Applications
    cout << "\n\n=== APPLICATION 1: Balanced Parentheses ===" << endl;
    string expr1 = "{[()]}";
    string expr2 = "{[(])}";
    cout << expr1 << " is " << (isBalanced(expr1) ? "balanced" : "not balanced") << endl;
    cout << expr2 << " is " << (isBalanced(expr2) ? "balanced" : "not balanced") << endl;
    
    cout << "\n=== APPLICATION 2: String Reversal ===" << endl;
    string original = "Hello World";
    string reversed = reverseString(original);
    cout << "Original: " << original << endl;
    cout << "Reversed: " << reversed << endl;
    
    // Application 3
    simulatePrintQueue();
    
    return 0;
}

/*
 * Expected Output Summary:
 * 
 * Stack demonstrates LIFO (Last In, First Out):
 * - Push: 10, 20, 30, 40, 50
 * - Pop order: 50, 40, 30, 20, 10
 * 
 * Queue demonstrates FIFO (First In, First Out):
 * - Enqueue: 1, 2, 3, 4, 5
 * - Dequeue order: 1, 2, 3, 4, 5
 * 
 * Real-world Applications:
 * 1. Stack: Parentheses matching (compilers, text editors)
 * 2. Stack: String reversal (undo operations)
 * 3. Queue: Print job scheduling (printer spooler)
 * 
 * Time Complexity:
 * - Stack: push/pop/peek - O(1)
 * - Queue: enqueue/dequeue/front - O(1)
 * 
 * Space Complexity: O(n) where n is the number of elements
 * 
 * Key Concepts:
 * 1. Stack uses top pointer for access
 * 2. Queue uses circular array for efficiency
 * 3. Both have O(1) operations for their main functions
 * 4. Stacks used for depth-first operations
 * 5. Queues used for breadth-first operations
 */
