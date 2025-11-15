/*
 * Week 2: C++ Class Constructors and Destructors
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Implement a class demonstrating proper use of constructors,
 * copy constructors, and destructors with dynamic memory management.
 * 
 * Learning Objectives:
 * - Understand constructor initialization
 * - Implement copy constructors
 * - Practice proper resource cleanup with destructors
 * - Handle dynamic memory allocation safely
 */

#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    char* name;
    int* grades;
    int numGrades;
    
public:
    // Default Constructor
    Student() {
        name = new char[50];
        strcpy(name, "Unknown");
        grades = nullptr;
        numGrades = 0;
        cout << "Default constructor called" << endl;
    }
    
    // Parameterized Constructor
    Student(const char* studentName, int* studentGrades, int count) {
        // Allocate and copy name
        name = new char[strlen(studentName) + 1];
        strcpy(name, studentName);
        
        // Allocate and copy grades
        numGrades = count;
        grades = new int[numGrades];
        for (int i = 0; i < numGrades; i++) {
            grades[i] = studentGrades[i];
        }
        
        cout << "Parameterized constructor called for " << name << endl;
    }
    
    // Copy Constructor (Deep Copy)
    Student(const Student& other) {
        // Deep copy name
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        
        // Deep copy grades
        numGrades = other.numGrades;
        grades = new int[numGrades];
        for (int i = 0; i < numGrades; i++) {
            grades[i] = other.grades[i];
        }
        
        cout << "Copy constructor called for " << name << endl;
    }
    
    // Destructor
    ~Student() {
        cout << "Destructor called for " << name << endl;
        delete[] name;
        delete[] grades;
    }
    
    // Display student information
    void display() {
        cout << "\nStudent: " << name << endl;
        cout << "Grades: ";
        for (int i = 0; i < numGrades; i++) {
            cout << grades[i] << " ";
        }
        cout << endl;
    }
    
    // Calculate average grade
    double getAverage() {
        if (numGrades == 0) return 0.0;
        
        int sum = 0;
        for (int i = 0; i < numGrades; i++) {
            sum += grades[i];
        }
        return static_cast<double>(sum) / numGrades;
    }
};

int main() {
    // Test default constructor
    Student s1;
    s1.display();
    
    cout << "\n" << string(50, '-') << "\n" << endl;
    
    // Test parameterized constructor
    int grades[] = {85, 90, 78, 92, 88};
    Student s2("John Doe", grades, 5);
    s2.display();
    cout << "Average: " << s2.getAverage() << endl;
    
    cout << "\n" << string(50, '-') << "\n" << endl;
    
    // Test copy constructor
    Student s3 = s2;  // This calls copy constructor
    s3.display();
    cout << "Average: " << s3.getAverage() << endl;
    
    cout << "\n" << string(50, '-') << "\n" << endl;
    
    return 0;
}

/*
 * Expected Output:
 * Default constructor called
 * Student: Unknown
 * Grades: 
 * 
 * --------------------------------------------------
 * 
 * Parameterized constructor called for John Doe
 * Student: John Doe
 * Grades: 85 90 78 92 88 
 * Average: 86.6
 * 
 * --------------------------------------------------
 * 
 * Copy constructor called for John Doe
 * Student: John Doe
 * Grades: 85 90 78 92 88 
 * Average: 86.6
 * 
 * --------------------------------------------------
 * 
 * Destructor called for John Doe
 * Destructor called for John Doe
 * Destructor called for Unknown
 * 
 * Key Concepts Demonstrated:
 * 1. Multiple constructor types
 * 2. Deep copy to avoid shallow copy issues
 * 3. Proper memory management with new/delete
 * 4. Destructor cleanup in reverse order of creation
 */
