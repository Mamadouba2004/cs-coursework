#include <iostream>
#include <string>
#include "HashedMap.h"

using namespace std;

int main() {
    // Create a HashedMap
    HashedMap<string, int> phoneBook(10);  // Small table to force collisions!

    cout << "=== Testing HashedMap ===" << endl << endl;

    // Test 1: isEmpty on empty map
    cout << "Test 1: Is map empty? " << (phoneBook.isEmpty() ? "YES" : "NO") << endl;
    cout << "Number of entries: " << phoneBook.getNumberOfEntries() << endl << endl;

    // Test 2: Add some entries
    cout << "Test 2: Adding entries..." << endl;
    phoneBook.add("Alice", 1234);
    phoneBook.add("Bob", 5678);
    phoneBook.add("Charlie", 9012);
    phoneBook.add("David", 3456);
    phoneBook.add("Eve", 7890);
    cout << "Added 5 entries" << endl;
    cout << "Number of entries: " << phoneBook.getNumberOfEntries() << endl << endl;

    // Test 3: contains
    cout << "Test 3: Testing contains()..." << endl;
    cout << "Contains 'Alice'? " << (phoneBook.contains("Alice") ? "YES" : "NO") << endl;
    cout << "Contains 'Bob'? " << (phoneBook.contains("Bob") ? "YES" : "NO") << endl;
    cout << "Contains 'Zoe'? " << (phoneBook.contains("Zoe") ? "YES" : "NO") << endl << endl;

    // Test 4: getValue
    cout << "Test 4: Testing getValue()..." << endl;
    int value;
    if (phoneBook.getValue("Alice", value)) {
        cout << "Alice's number: " << value << endl;
    }
    if (phoneBook.getValue("Charlie", value)) {
        cout << "Charlie's number: " << value << endl;
    }
    if (!phoneBook.getValue("Zoe", value)) {
        cout << "Zoe not found (expected)" << endl;
    }
    cout << endl;

    // Test 5: Update existing key
    cout << "Test 5: Updating Alice's number..." << endl;
    cout << "Old number: ";
    phoneBook.getValue("Alice", value);
    cout << value << endl;
    phoneBook.add("Alice", 9999);  // Update
    cout << "New number: ";
    phoneBook.getValue("Alice", value);
    cout << value << endl << endl;

    // Test 6: Remove
    cout << "Test 6: Testing remove()..." << endl;
    cout << "Removing Bob..." << endl;
    phoneBook.remove("Bob");
    cout << "Contains 'Bob'? " << (phoneBook.contains("Bob") ? "YES" : "NO") << endl;
    cout << "Number of entries: " << phoneBook.getNumberOfEntries() << endl << endl;

    // Test 7: Demonstrate collisions
    cout << "Test 7: DEMONSTRATING COLLISION HANDLING" << endl;
    cout << "Creating small hash table (size 5) to force collisions..." << endl;
    HashedMap<string, int> smallMap(5);

    // These will likely collide in a table of size 5
    smallMap.add("cat", 100);
    smallMap.add("dog", 200);
    smallMap.add("rat", 300);
    smallMap.add("bat", 400);
    smallMap.add("hat", 500);

    cout << "Added: cat, dog, rat, bat, hat" << endl;
    cout << "Number of entries: " << smallMap.getNumberOfEntries() << endl;

    // Verify all can be retrieved (proving chaining works!)
    int val;
    cout << "\nRetrieving all values (proves collision handling works):" << endl;
    if (smallMap.getValue("cat", val)) cout << "cat: " << val << endl;
    if (smallMap.getValue("dog", val)) cout << "dog: " << val << endl;
    if (smallMap.getValue("rat", val)) cout << "rat: " << val << endl;
    if (smallMap.getValue("bat", val)) cout << "bat: " << val << endl;
    if (smallMap.getValue("hat", val)) cout << "hat: " << val << endl;
    cout << endl;

    // Test 8: Clear
    cout << "Test 8: Testing clear()..." << endl;
    phoneBook.clear();
    cout << "After clear, is map empty? " << (phoneBook.isEmpty() ? "YES" : "NO") << endl;
    cout << "Number of entries: " << phoneBook.getNumberOfEntries() << endl << endl;

    cout << "=== ALL TESTS COMPLETE ===" << endl;

    return 0;
}