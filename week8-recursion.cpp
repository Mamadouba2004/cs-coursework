/*
 * Week 8: Recursion
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Explore recursive problem-solving techniques with various
 * classic recursion problems and applications.
 * 
 * Learning Objectives:
 * - Understand base cases and recursive cases
 * - Implement recursive algorithms
 * - Analyze recursion vs iteration
 * - Practice recursive data structure operations
 */

#include <iostream>
#include <string>
using namespace std;

// ==================== BASIC RECURSION EXAMPLES ====================

// 1. Factorial - Classic recursion example
long long factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

// 2. Fibonacci - Multiple recursive calls
int fibonacci(int n) {
    // Base cases
    if (n <= 1) {
        return n;
    }
    // Recursive case
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 3. Power function - a^b
double power(double base, int exponent) {
    // Base case
    if (exponent == 0) {
        return 1;
    }
    // Recursive case
    if (exponent > 0) {
        return base * power(base, exponent - 1);
    } else {
        return 1.0 / power(base, -exponent);
    }
}

// 4. Sum of digits
int sumOfDigits(int n) {
    // Base case
    if (n == 0) {
        return 0;
    }
    // Recursive case
    return (n % 10) + sumOfDigits(n / 10);
}

// ==================== STRING RECURSION ====================

// 5. Reverse a string
string reverseString(string str) {
    // Base case
    if (str.length() <= 1) {
        return str;
    }
    // Recursive case: last char + reverse of rest
    return str[str.length() - 1] + reverseString(str.substr(0, str.length() - 1));
}

// 6. Check if string is palindrome
bool isPalindrome(string str, int start, int end) {
    // Base cases
    if (start >= end) {
        return true;
    }
    if (str[start] != str[end]) {
        return false;
    }
    // Recursive case
    return isPalindrome(str, start + 1, end - 1);
}

// ==================== ARRAY RECURSION ====================

// 7. Sum of array elements
int arraySum(int arr[], int size) {
    // Base case
    if (size == 0) {
        return 0;
    }
    // Recursive case
    return arr[size - 1] + arraySum(arr, size - 1);
}

// 8. Find maximum in array
int findMax(int arr[], int size) {
    // Base case
    if (size == 1) {
        return arr[0];
    }
    // Recursive case
    int maxOfRest = findMax(arr, size - 1);
    return (arr[size - 1] > maxOfRest) ? arr[size - 1] : maxOfRest;
}

// 9. Binary search - recursive implementation
int binarySearch(int arr[], int left, int right, int target) {
    // Base case
    if (left > right) {
        return -1;  // Not found
    }
    
    int mid = left + (right - left) / 2;
    
    // Found the target
    if (arr[mid] == target) {
        return mid;
    }
    
    // Recursive cases
    if (arr[mid] > target) {
        return binarySearch(arr, left, mid - 1, target);
    } else {
        return binarySearch(arr, mid + 1, right, target);
    }
}

// ==================== ADVANCED RECURSION ====================

// 10. Tower of Hanoi
void towerOfHanoi(int n, char from, char to, char aux) {
    // Base case
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    
    // Recursive case
    towerOfHanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    towerOfHanoi(n - 1, aux, to, from);
}

// 11. Generate all permutations of a string
void generatePermutations(string str, int left, int right) {
    // Base case
    if (left == right) {
        cout << str << endl;
        return;
    }
    
    // Recursive case
    for (int i = left; i <= right; i++) {
        // Swap
        swap(str[left], str[i]);
        
        // Recurse
        generatePermutations(str, left + 1, right);
        
        // Backtrack
        swap(str[left], str[i]);
    }
}

// 12. Print all subsets of a set (Power Set)
void printSubsets(int arr[], int size, int index, int subset[], int subsetSize) {
    // Base case - print current subset
    if (index == size) {
        cout << "{ ";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i] << " ";
        }
        cout << "}" << endl;
        return;
    }
    
    // Recursive case 1: Include current element
    subset[subsetSize] = arr[index];
    printSubsets(arr, size, index + 1, subset, subsetSize + 1);
    
    // Recursive case 2: Exclude current element
    printSubsets(arr, size, index + 1, subset, subsetSize);
}

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "=== BASIC RECURSION EXAMPLES ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Factorial
    cout << "1. Factorial:" << endl;
    cout << "   5! = " << factorial(5) << endl;
    cout << "   10! = " << factorial(10) << endl;
    
    // Fibonacci
    cout << "\n2. Fibonacci:" << endl;
    cout << "   fib(0) = " << fibonacci(0) << endl;
    cout << "   fib(5) = " << fibonacci(5) << endl;
    cout << "   fib(10) = " << fibonacci(10) << endl;
    
    // Power
    cout << "\n3. Power:" << endl;
    cout << "   2^5 = " << power(2, 5) << endl;
    cout << "   3^4 = " << power(3, 4) << endl;
    
    // Sum of digits
    cout << "\n4. Sum of Digits:" << endl;
    cout << "   sumOfDigits(12345) = " << sumOfDigits(12345) << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== STRING RECURSION ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Reverse string
    string str1 = "Hello";
    cout << "5. Reverse String:" << endl;
    cout << "   Original: " << str1 << endl;
    cout << "   Reversed: " << reverseString(str1) << endl;
    
    // Palindrome check
    string str2 = "racecar";
    string str3 = "hello";
    cout << "\n6. Palindrome Check:" << endl;
    cout << "   \"" << str2 << "\" is " 
         << (isPalindrome(str2, 0, str2.length() - 1) ? "a palindrome" : "not a palindrome") << endl;
    cout << "   \"" << str3 << "\" is " 
         << (isPalindrome(str3, 0, str3.length() - 1) ? "a palindrome" : "not a palindrome") << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== ARRAY RECURSION ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    int arr[] = {5, 2, 8, 1, 9, 3};
    int size = 6;
    
    // Array sum
    cout << "7. Array Sum:" << endl;
    cout << "   Sum of [5, 2, 8, 1, 9, 3] = " << arraySum(arr, size) << endl;
    
    // Find max
    cout << "\n8. Find Maximum:" << endl;
    cout << "   Max of [5, 2, 8, 1, 9, 3] = " << findMax(arr, size) << endl;
    
    // Binary search
    int sortedArr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int sortedSize = 8;
    cout << "\n9. Binary Search:" << endl;
    cout << "   Searching for 7 in [1, 3, 5, 7, 9, 11, 13, 15]" << endl;
    int index = binarySearch(sortedArr, 0, sortedSize - 1, 7);
    cout << "   Found at index: " << index << endl;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "=== ADVANCED RECURSION ===" << endl;
    cout << string(50, '=') << "\n" << endl;
    
    // Tower of Hanoi
    cout << "10. Tower of Hanoi (3 disks):" << endl;
    towerOfHanoi(3, 'A', 'C', 'B');
    
    // Permutations
    cout << "\n11. All Permutations of 'ABC':" << endl;
    string str = "ABC";
    generatePermutations(str, 0, str.length() - 1);
    
    // Subsets
    cout << "\n12. All Subsets of {1, 2, 3}:" << endl;
    int set[] = {1, 2, 3};
    int subset[3];
    printSubsets(set, 3, 0, subset, 0);
    
    return 0;
}

/*
 * RECURSION ANALYSIS:
 * 
 * Time Complexity:
 * - Factorial: O(n)
 * - Fibonacci (naive): O(2^n) - exponential!
 * - Power: O(n)
 * - Binary Search: O(log n)
 * - Tower of Hanoi: O(2^n)
 * - Permutations: O(n!)
 * 
 * Space Complexity (Call Stack):
 * - Most: O(n) for recursion depth
 * - Binary Search: O(log n)
 * 
 * Key Recursion Principles:
 * 
 * 1. ALWAYS have a base case (stopping condition)
 * 2. Recursive case should move toward base case
 * 3. Each recursive call should solve a smaller problem
 * 4. Trust the recursion - assume recursive calls work correctly
 * 
 * When to Use Recursion:
 * ✓ Tree/graph traversal
 * ✓ Divide and conquer algorithms
 * ✓ Backtracking problems
 * ✓ Mathematical sequences
 * ✓ When problem naturally divides into smaller subproblems
 * 
 * When NOT to Use Recursion:
 * ✗ Simple iteration is clearer
 * ✗ Stack overflow concerns (deep recursion)
 * ✗ Performance critical (iteration usually faster)
 * ✗ Memory constraints (recursion uses stack space)
 * 
 * Recursion vs Iteration:
 * - Recursion: More elegant, easier to understand for some problems
 * - Iteration: Usually more efficient, no stack overflow risk
 * - Many recursive solutions can be converted to iterative
 * 
 * Real-World Applications:
 * - File system traversal
 * - JSON/XML parsing
 * - Maze solving
 * - Game AI (minimax algorithm)
 * - Compiler design (parsing)
 */
