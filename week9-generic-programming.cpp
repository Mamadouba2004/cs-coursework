/*
 * Week 9: Generic Programming (Templates)
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Implement generic data structures and algorithms using C++ templates.
 * 
 * Learning Objectives:
 * - Understand function templates and class templates
 * - Create type-independent code
 * - Implement generic data structures
 * - Use templates for algorithm reusability
 */

#include <iostream>
#include <string>
using namespace std;

// ==================== FUNCTION TEMPLATES ====================

// 1. Generic swap function
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 2. Generic max function
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

// 3. Generic array print function
template <typename T>
void printArray(T arr[], int size, string type) {
    cout << type << " Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 4. Generic binary search
template <typename T>
int binarySearch(T arr[], int size, T target) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

// ==================== CLASS TEMPLATES ====================

// Generic Stack implementation
template <typename T>
class Stack {
private:
    static const int MAX_SIZE = 100;
    T arr[MAX_SIZE];
    int topIndex;
    
public:
    Stack() : topIndex(-1) {}
    
    void push(T value) {
        if (isFull()) {
            cout << "Stack overflow!" << endl;
            return;
        }
        arr[++topIndex] = value;
    }
    
    T pop() {
        if (isEmpty()) {
            cout << "Stack underflow!" << endl;
            return T(); // Return default value
        }
        return arr[topIndex--];
    }
    
    T peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return T();
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
        cout << "Stack: ";
        for (int i = 0; i <= topIndex; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Generic Node for Linked List
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    
    Node(T val) : data(val), next(nullptr) {}
};

// Generic Linked List
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int listSize;
    
public:
    LinkedList() : head(nullptr), listSize(0) {}
    
    void insertAtHead(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }
    
    void insertAtTail(T value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        listSize++;
    }
    
    bool search(T value) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    
    void remove(T value) {
        if (head == nullptr) return;
        
        // If head needs to be removed
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            listSize--;
            return;
        }
        
        // Search for the node
        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            listSize--;
        }
    }
    
    void display() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        
        cout << "List: ";
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    
    int size() {
        return listSize;
    }
    
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Generic Pair class
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
    
public:
    Pair(T1 f, T2 s) : first(f), second(s) {}
    
    T1 getFirst() { return first; }
    T2 getSecond() { return second; }
    
    void setFirst(T1 f) { first = f; }
    void setSecond(T2 s) { second = s; }
    
    void display() {
        cout << "(" << first << ", " << second << ")" << endl;
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "=== FUNCTION TEMPLATES ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // 1. Generic swap
    cout << "1. Generic Swap:" << endl;
    int x = 5, y = 10;
    cout << "   Before: x = " << x << ", y = " << y << endl;
    swapValues(x, y);
    cout << "   After: x = " << x << ", y = " << y << endl;
    
    string s1 = "Hello", s2 = "World";
    cout << "   Before: s1 = " << s1 << ", s2 = " << s2 << endl;
    swapValues(s1, s2);
    cout << "   After: s1 = " << s1 << ", s2 = " << s2 << endl;
    
    // 2. Generic max
    cout << "\n2. Generic Max:" << endl;
    cout << "   Max of 5 and 10: " << getMax(5, 10) << endl;
    cout << "   Max of 3.14 and 2.71: " << getMax(3.14, 2.71) << endl;
    cout << "   Max of 'a' and 'z': " << getMax('a', 'z') << endl;
    
    // 3. Generic array print
    cout << "\n3. Generic Array Print:" << endl;
    int intArr[] = {1, 2, 3, 4, 5};
    double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    char charArr[] = {'a', 'b', 'c', 'd', 'e'};
    
    printArray(intArr, 5, "Integer");
    printArray(doubleArr, 5, "Double");
    printArray(charArr, 5, "Character");
    
    // 4. Generic binary search
    cout << "\n4. Generic Binary Search:" << endl;
    int sortedArr[] = {1, 3, 5, 7, 9, 11, 13};
    int index = binarySearch(sortedArr, 7, 7);
    cout << "   Searching for 7: Found at index " << index << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== GENERIC STACK ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Integer stack
    cout << "Integer Stack:" << endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    cout << "Popped: " << intStack.pop() << endl;
    intStack.display();
    
    // String stack
    cout << "\nString Stack:" << endl;
    Stack<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("!");
    stringStack.display();
    cout << "Popped: " << stringStack.pop() << endl;
    stringStack.display();
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== GENERIC LINKED LIST ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Integer linked list
    cout << "Integer Linked List:" << endl;
    LinkedList<int> intList;
    intList.insertAtTail(1);
    intList.insertAtTail(2);
    intList.insertAtTail(3);
    intList.insertAtHead(0);
    intList.display();
    cout << "Size: " << intList.size() << endl;
    cout << "Search for 2: " << (intList.search(2) ? "Found" : "Not found") << endl;
    
    // String linked list
    cout << "\nString Linked List:" << endl;
    LinkedList<string> stringList;
    stringList.insertAtTail("Data");
    stringList.insertAtTail("Structures");
    stringList.insertAtTail("Course");
    stringList.display();
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== GENERIC PAIR ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Different type pairs
    Pair<int, string> student(101, "John Doe");
    cout << "Student: ID = " << student.getFirst() 
         << ", Name = " << student.getSecond() << endl;
    
    Pair<string, double> product("Laptop", 999.99);
    cout << "Product: Name = " << product.getFirst() 
         << ", Price = $" << product.getSecond() << endl;
    
    Pair<double, double> coordinates(3.14, 2.71);
    cout << "Coordinates: ";
    coordinates.display();
    
    return 0;
}

/*
 * TEMPLATE BENEFITS:
 * 
 * 1. CODE REUSABILITY:
 *    - Write once, use with any type
 *    - No need to duplicate code for int, double, string, etc.
 * 
 * 2. TYPE SAFETY:
 *    - Compiler checks types at compile time
 *    - Catches type errors early
 * 
 * 3. PERFORMANCE:
 *    - No runtime overhead
 *    - Code is generated at compile time
 * 
 * 4. FLEXIBILITY:
 *    - Can work with user-defined types
 *    - Supports any type that satisfies requirements
 * 
 * TEMPLATE SYNTAX:
 * 
 * Function Template:
 * template <typename T>
 * T functionName(T parameter) { ... }
 * 
 * Class Template:
 * template <typename T>
 * class ClassName { ... };
 * 
 * Multiple Type Parameters:
 * template <typename T1, typename T2>
 * class Pair { ... };
 * 
 * REAL-WORLD USAGE:
 * 
 * C++ Standard Template Library (STL):
 * - vector<T>
 * - stack<T>
 * - queue<T>
 * - map<K, V>
 * - set<T>
 * - sort(), find(), etc.
 * 
 * These are all implemented using templates!
 * 
 * KEY CONCEPTS:
 * 
 * 1. Templates are instantiated at compile time
 * 2. Each unique type creates a separate version
 * 3. Template code must be in header files
 * 4. Compiler needs to see full template definition
 * 5. Type requirements must be satisfied (e.g., < operator for sorting)
 * 
 * LIMITATIONS:
 * 
 * 1. Longer compile times (template instantiation)
 * 2. Larger executable size (multiple instantiations)
 * 3. Complex error messages
 * 4. Debugging can be challenging
 * 
 * BEST PRACTICES:
 * 
 * 1. Use templates when type-independence is needed
 * 2. Provide clear documentation
 * 3. Test with multiple types
 * 4. Consider template constraints (C++20 concepts)
 * 5. Keep templates simple when possible
 */
