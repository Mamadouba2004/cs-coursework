/*
 * Week 3: Pointers and Resource Management
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Demonstrate pointer operations, dynamic memory allocation,
 * and proper resource management techniques.
 * 
 * Learning Objectives:
 * - Understand pointer basics and dereferencing
 * - Practice dynamic memory allocation
 * - Implement pointer-based functions
 * - Avoid memory leaks and dangling pointers
 */

#include <iostream>
using namespace std;

// Function to demonstrate pass by value vs pass by pointer
void modifyByValue(int x) {
    x = x * 2;
    cout << "Inside modifyByValue: x = " << x << endl;
}

void modifyByPointer(int* x) {
    *x = *x * 2;
    cout << "Inside modifyByPointer: *x = " << *x << endl;
}

// Function to swap two values using pointers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to dynamically allocate and initialize an array
int* createArray(int size, int initialValue) {
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = initialValue + i;
    }
    return arr;
}

// Function to print array using pointer arithmetic
void printArray(int* arr, int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << *(arr + i) << " ";  // Pointer arithmetic
    }
    cout << endl;
}

// Function to find max element using pointers
int* findMax(int* arr, int size) {
    int* maxPtr = arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *maxPtr) {
            maxPtr = arr + i;
        }
    }
    return maxPtr;
}

// Demonstrate pointer to pointer
void allocate2DArray(int*** arr, int rows, int cols) {
    *arr = new int*[rows];
    for (int i = 0; i < rows; i++) {
        (*arr)[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            (*arr)[i][j] = i * cols + j;
        }
    }
}

void deallocate2DArray(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() {
    cout << "=== Part 1: Pass by Value vs Pass by Pointer ===" << endl;
    int num = 10;
    cout << "Original value: " << num << endl;
    modifyByValue(num);
    cout << "After modifyByValue: " << num << endl;
    modifyByPointer(&num);
    cout << "After modifyByPointer: " << num << endl;
    
    cout << "\n=== Part 2: Pointer Swap ===" << endl;
    int x = 5, y = 10;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(&x, &y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    
    cout << "\n=== Part 3: Dynamic Array Allocation ===" << endl;
    int size = 5;
    int* dynamicArray = createArray(size, 10);
    printArray(dynamicArray, size);
    
    cout << "\n=== Part 4: Finding Max with Pointers ===" << endl;
    int* maxElement = findMax(dynamicArray, size);
    cout << "Max element: " << *maxElement << endl;
    cout << "Max element position: " << (maxElement - dynamicArray) << endl;
    
    cout << "\n=== Part 5: 2D Array with Pointers ===" << endl;
    int** matrix = nullptr;
    int rows = 3, cols = 4;
    allocate2DArray(&matrix, rows, cols);
    
    cout << "Matrix:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    
    // Clean up memory
    delete[] dynamicArray;
    deallocate2DArray(matrix, rows);
    
    cout << "\n=== Memory cleaned up successfully ===" << endl;
    
    return 0;
}

/*
 * Expected Output:
 * === Part 1: Pass by Value vs Pass by Pointer ===
 * Original value: 10
 * Inside modifyByValue: x = 20
 * After modifyByValue: 10
 * Inside modifyByPointer: *x = 20
 * After modifyByPointer: 20
 * 
 * === Part 2: Pointer Swap ===
 * Before swap: x = 5, y = 10
 * After swap: x = 10, y = 5
 * 
 * === Part 3: Dynamic Array Allocation ===
 * Array: 10 11 12 13 14 
 * 
 * === Part 4: Finding Max with Pointers ===
 * Max element: 14
 * Max element position: 4
 * 
 * === Part 5: 2D Array with Pointers ===
 * Matrix:
 * 0    1    2    3
 * 4    5    6    7
 * 8    9    10   11
 * 
 * === Memory cleaned up successfully ===
 * 
 * Key Concepts:
 * 1. Pointers allow modification of original variables
 * 2. Dynamic memory requires manual management
 * 3. Pointer arithmetic enables array traversal
 * 4. Always deallocate dynamically allocated memory
 * 5. Pointer to pointer for multi-dimensional structures
 */
