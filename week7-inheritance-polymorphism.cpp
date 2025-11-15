/*
 * Week 7: Inheritance and Polymorphism
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Demonstrate Object-Oriented Programming concepts including
 * inheritance hierarchies, virtual functions, and polymorphism.
 * 
 * Learning Objectives:
 * - Understand inheritance (is-a relationship)
 * - Implement virtual functions for runtime polymorphism
 * - Practice abstract classes and pure virtual functions
 * - Use dynamic binding and method overriding
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ==================== BASE CLASS ====================

class Shape {
protected:
    string name;
    string color;
    
public:
    Shape(string n, string c) : name(n), color(c) {
        cout << "Shape constructor called for " << name << endl;
    }
    
    // Virtual function for polymorphism
    virtual double getArea() const = 0;  // Pure virtual function
    virtual double getPerimeter() const = 0;
    
    virtual void display() const {
        cout << "\nShape: " << name << endl;
        cout << "Color: " << color << endl;
    }
    
    // Virtual destructor is important for proper cleanup
    virtual ~Shape() {
        cout << "Shape destructor called for " << name << endl;
    }
};

// ==================== DERIVED CLASSES ====================

class Rectangle : public Shape {
private:
    double width;
    double height;
    
public:
    Rectangle(string c, double w, double h) 
        : Shape("Rectangle", c), width(w), height(h) {
        cout << "Rectangle constructor called" << endl;
    }
    
    double getArea() const override {
        return width * height;
    }
    
    double getPerimeter() const override {
        return 2 * (width + height);
    }
    
    void display() const override {
        Shape::display();  // Call base class display
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Area: " << getArea() << endl;
        cout << "Perimeter: " << getPerimeter() << endl;
    }
    
    ~Rectangle() {
        cout << "Rectangle destructor called" << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    const double PI = 3.14159;
    
public:
    Circle(string c, double r) 
        : Shape("Circle", c), radius(r) {
        cout << "Circle constructor called" << endl;
    }
    
    double getArea() const override {
        return PI * radius * radius;
    }
    
    double getPerimeter() const override {
        return 2 * PI * radius;
    }
    
    void display() const override {
        Shape::display();
        cout << "Radius: " << radius << endl;
        cout << "Area: " << getArea() << endl;
        cout << "Circumference: " << getPerimeter() << endl;
    }
    
    ~Circle() {
        cout << "Circle destructor called" << endl;
    }
};

class Triangle : public Shape {
private:
    double side1, side2, side3;
    
public:
    Triangle(string c, double s1, double s2, double s3) 
        : Shape("Triangle", c), side1(s1), side2(s2), side3(s3) {
        cout << "Triangle constructor called" << endl;
    }
    
    double getArea() const override {
        // Using Heron's formula
        double s = getPerimeter() / 2;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    
    double getPerimeter() const override {
        return side1 + side2 + side3;
    }
    
    void display() const override {
        Shape::display();
        cout << "Sides: " << side1 << ", " << side2 << ", " << side3 << endl;
        cout << "Area: " << getArea() << endl;
        cout << "Perimeter: " << getPerimeter() << endl;
    }
    
    ~Triangle() {
        cout << "Triangle destructor called" << endl;
    }
};

// ==================== ANOTHER INHERITANCE EXAMPLE ====================

class Employee {
protected:
    string name;
    int id;
    double baseSalary;
    
public:
    Employee(string n, int i, double s) 
        : name(n), id(i), baseSalary(s) {}
    
    virtual double calculateSalary() const {
        return baseSalary;
    }
    
    virtual void displayInfo() const {
        cout << "\nEmployee: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Base Salary: $" << baseSalary << endl;
    }
    
    virtual ~Employee() {}
};

class Manager : public Employee {
private:
    double bonus;
    int teamSize;
    
public:
    Manager(string n, int i, double s, double b, int t) 
        : Employee(n, i, s), bonus(b), teamSize(t) {}
    
    double calculateSalary() const override {
        return baseSalary + bonus;
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Position: Manager" << endl;
        cout << "Team Size: " << teamSize << endl;
        cout << "Bonus: $" << bonus << endl;
        cout << "Total Salary: $" << calculateSalary() << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;
    int projectsCompleted;
    
public:
    Developer(string n, int i, double s, string lang, int projects) 
        : Employee(n, i, s), programmingLanguage(lang), 
          projectsCompleted(projects) {}
    
    double calculateSalary() const override {
        // Bonus based on projects completed
        return baseSalary + (projectsCompleted * 500);
    }
    
    void displayInfo() const override {
        Employee::displayInfo();
        cout << "Position: Developer" << endl;
        cout << "Primary Language: " << programmingLanguage << endl;
        cout << "Projects Completed: " << projectsCompleted << endl;
        cout << "Total Salary: $" << calculateSalary() << endl;
    }
};

// ==================== DEMONSTRATION FUNCTIONS ====================

void demonstratePolymorphism(Shape* shape) {
    // This function works with any Shape object!
    shape->display();
    cout << "---" << endl;
}

void calculateTotalSalary(vector<Employee*>& employees) {
    double total = 0;
    for (Employee* emp : employees) {
        total += emp->calculateSalary();
    }
    cout << "\nTotal Company Salary Budget: $" << total << endl;
}

int main() {
    cout << "=== POLYMORPHISM WITH SHAPES ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Create shapes using base class pointers
    Shape* shapes[3];
    shapes[0] = new Rectangle("Red", 5, 10);
    shapes[1] = new Circle("Blue", 7);
    shapes[2] = new Triangle("Green", 3, 4, 5);
    
    cout << "\n" << string(50, '-') << endl;
    cout << "Displaying all shapes using polymorphism:" << endl;
    cout << string(50, '-') << "\n" << endl;
    
    // Polymorphism in action - same function call, different behavior
    for (int i = 0; i < 3; i++) {
        demonstratePolymorphism(shapes[i]);
    }
    
    // Calculate total area
    double totalArea = 0;
    for (int i = 0; i < 3; i++) {
        totalArea += shapes[i]->getArea();
    }
    cout << "Total area of all shapes: " << totalArea << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== POLYMORPHISM WITH EMPLOYEES ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Create employees
    vector<Employee*> employees;
    employees.push_back(new Manager("Alice Johnson", 101, 80000, 20000, 5));
    employees.push_back(new Developer("Bob Smith", 102, 70000, "C++", 10));
    employees.push_back(new Developer("Carol White", 103, 75000, "Python", 8));
    
    // Display all employee info
    for (Employee* emp : employees) {
        emp->displayInfo();
    }
    
    // Calculate total salary
    calculateTotalSalary(employees);
    
    // Clean up memory
    cout << "\n" << string(50, '=') << endl;
    cout << "=== CLEANUP ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    for (int i = 0; i < 3; i++) {
        delete shapes[i];
    }
    
    for (Employee* emp : employees) {
        delete emp;
    }
    
    return 0;
}

/*
 * Key Concepts Demonstrated:
 * 
 * 1. INHERITANCE:
 *    - Base class (Shape, Employee)
 *    - Derived classes (Rectangle, Circle, Triangle, Manager, Developer)
 *    - "is-a" relationship (Rectangle IS-A Shape)
 * 
 * 2. POLYMORPHISM:
 *    - Runtime polymorphism using virtual functions
 *    - Same interface, different implementations
 *    - demonstratePolymorphism() works with ANY Shape
 * 
 * 3. VIRTUAL FUNCTIONS:
 *    - getArea() and getPerimeter() are overridden in each derived class
 *    - Correct version called based on actual object type, not pointer type
 * 
 * 4. ABSTRACT CLASS:
 *    - Shape is abstract (has pure virtual functions)
 *    - Cannot create Shape objects directly
 *    - Must implement pure virtual functions in derived classes
 * 
 * 5. VIRTUAL DESTRUCTOR:
 *    - Ensures proper cleanup of derived class objects
 *    - Critical when deleting through base class pointers
 * 
 * 6. METHOD OVERRIDING:
 *    - display() overridden in each class
 *    - Can call base class version using Shape::display()
 * 
 * Benefits of Polymorphism:
 * - Code reusability
 * - Extensibility (easy to add new shapes)
 * - Maintainability
 * - Abstraction
 * 
 * Real-World Applications:
 * - Graphics systems (drawing different shapes)
 * - Game development (different character types)
 * - Employee management systems
 * - Payment processing (different payment methods)
 */
