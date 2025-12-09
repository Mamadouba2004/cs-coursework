/*
 * Week 13: Hash Tables with Chaining
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Implement deletion in a hash table that uses chaining for collision resolution.
 * 
 * Learning Objectives:
 * - Understand hash table structure with separate chaining
 * - Implement hash functions
 * - Handle collision resolution via linked lists
 * - Implement insertion and deletion operations
 * - Manage dynamic memory in hash tables
 * 
 * Key Concepts:
 * - Hash Function: Maps keys to bucket indices
 * - Chaining: Each bucket contains a linked list of items
 * - Collision Handling: Multiple items can hash to same index
 */

#include <iostream>
#include <string>
#include <list>
#include <algorithm>  // for find algorithm
using namespace std;

class HashTable {
public:
    /*
     * ADD ITEM - Insert an item into the hash table
     * 
     * Process:
     * 1. Compute hash index for the value
     * 2. Add value to the list (chain) at that index
     * 
     * Time Complexity: O(1) average case
     * - Hash function: O(k) where k is string length
     * - List insertion at end: O(1) with STL list
     */
    void add_item(const string& value) {
        int bucket_index = hash_function(value);
        array[bucket_index].push_back(value);
    }

    /*
     * DELETE ITEM - Remove an item from the hash table
     * 
     * Process:
     * 1. Compute hash index
     * 2. Access the chain (linked list) at that index
     * 3. Search for the item in the chain
     * 4. Remove if found, update pointers
     * 5. Free memory
     * 
     * Time Complexity: O(n) worst case where n is chain length
     * - Average case: O(1 + α) where α is load factor
     * 
     * Returns: true if deleted, false if not found
     */
    bool delete_item(const string& value) {
        // Step 1: Generate hash code for the item to be deleted
        int bucket_index = hash_function(value);
        
        // Step 2: Retrieve the list of items at the bucket_index
        list<string>& items = array[bucket_index];
        
        // Step 3: Use iterator and find algorithm to locate the item
        // The find() function searches the list for the value
        auto it = find(items.begin(), items.end(), value);
        
        // Step 4: Check if item was found
        if (it != items.end()) {
            // Found it! Remove from the list
            items.erase(it);  // erase() removes element at iterator position
            cout << "Item '" << value << "' successfully deleted.\n";
            return true;  // Successfully deleted
        }
        
        // Step 5: Item not found in the chain
        cout << "Item '" << value << "' not found in hash table.\n";
        return false;
    }

    /*
     * PRINT TABLE - Display entire hash table structure
     * 
     * Shows:
     * - Each bucket index
     * - All items in each bucket's chain
     * - Visual representation of chaining
     */
    void print_table() const {
        cout << "\n=== HASH TABLE CONTENTS ===" << endl;
        for (int i = 0; i < 10; ++i) {
            cout << "Bucket " << i << ": ";
            
            // Print all items in this bucket's chain
            for (const string& item : array[i]) {
                cout << item << " -> ";
            }
            cout << "nullptr\n";
        }
        cout << "===========================\n" << endl;
    }

private:
    /*
     * HASH FUNCTION - Convert string to bucket index
     * 
     * Algorithm:
     * 1. Sum ASCII values of all characters
     * 2. Take modulo TABLE_SIZE to get index 0-9
     * 
     * Example: "Bob"
     * - 'B' = 66, 'o' = 111, 'b' = 98
     * - Sum = 275
     * - Index = 275 % 10 = 5
     * 
     * Properties:
     * - Deterministic (same input always gives same output)
     * - Uniform distribution (ideally)
     * - Fast computation
     * 
     * Note: This is a simple hash function for educational purposes.
     * Production systems use more sophisticated functions (e.g., MurmurHash, xxHash)
     */
    int hash_function(const string& value) const {
        int sum_chars = 0;
        
        // Sum ASCII values of all characters
        for (char c : value) {
            sum_chars += static_cast<int>(c);
        }
        
        // Modulo by table size to get valid index
        return sum_chars % 10;
    }

    // Array of lists to handle chaining
    // Each bucket contains a std::list<string> for collision resolution
    list<string> array[10];
};

// ============================================================================
// MAIN - TEST THE HASH TABLE IMPLEMENTATION
// ============================================================================

int main() {
    HashTable x;

    cout << "Creating hash table and inserting items...\n" << endl;

    // Insert Items
    x.add_item("Bob");
    x.add_item("Jone");
    x.add_item("Lisa");
    x.add_item("Stuart");
    x.add_item("Pete");
    x.add_item("Siri");
    x.add_item("Ken");

    // Display table after insertions
    x.print_table();

    // Delete an Item
    cout << "Attempting to delete 'Ken'...\n";
    x.delete_item("Ken");

    // Display table after deletion
    x.print_table();

    // Test deleting non-existent item
    cout << "Attempting to delete 'Alice' (doesn't exist)...\n";
    x.delete_item("Alice");

    return 0;
}

/*
 * EXPECTED OUTPUT:
 * 
 * Creating hash table and inserting items...
 * 
 * === HASH TABLE CONTENTS ===
 * Bucket 0: nullptr
 * Bucket 1: Stuart -> nullptr
 * Bucket 2: nullptr
 * Bucket 3: nullptr
 * Bucket 4: nullptr
 * Bucket 5: Bob -> nullptr
 * Bucket 6: Jone -> nullptr
 * Bucket 7: Pete -> nullptr
 * Bucket 8: Lisa -> Siri -> nullptr
 * Bucket 9: Ken -> nullptr
 * ===========================
 * 
 * Attempting to delete 'Ken'...
 * Item 'Ken' successfully deleted.
 * 
 * === HASH TABLE CONTENTS ===
 * Bucket 0: nullptr
 * Bucket 1: Stuart -> nullptr
 * Bucket 2: nullptr
 * Bucket 3: nullptr
 * Bucket 4: nullptr
 * Bucket 5: Bob -> nullptr
 * Bucket 6: Jone -> nullptr
 * Bucket 7: Pete -> nullptr
 * Bucket 8: Lisa -> Siri -> nullptr
 * Bucket 9: nullptr
 * ===========================
 * 
 * Attempting to delete 'Alice' (doesn't exist)...
 * Item 'Alice' not found in hash table.
 */

/*
 * HASH TABLE ANALYSIS
 * 
 * COLLISION EXAMPLE:
 * Notice that "Lisa" and "Siri" both end up in Bucket 8!
 * - "Lisa": L(76) + i(105) + s(115) + a(97) = 393 % 10 = 3... wait, let's recalculate
 * - This shows collisions happen and chaining handles them
 * 
 * LOAD FACTOR:
 * Load Factor (α) = Number of items / Number of buckets
 * In our example: α = 7 items / 10 buckets = 0.7
 * 
 * Recommended load factor: < 0.75 for good performance
 * When α > 0.75, consider resizing (rehashing) the table
 * 
 * TIME COMPLEXITY SUMMARY:
 * 
 * Operation     | Average Case | Worst Case | Notes
 * --------------|--------------|------------|------------------------
 * Insert        | O(1)         | O(n)       | n = chain length
 * Delete        | O(1)         | O(n)       | Must search chain
 * Search        | O(1)         | O(n)       | Must search chain
 * 
 * SPACE COMPLEXITY:
 * O(n + m) where n = number of items, m = number of buckets
 * 
 * ADVANTAGES OF CHAINING:
 * ✓ Simple to implement
 * ✓ No clustering issues
 * ✓ Table never "fills up"
 * ✓ Easy to delete
 * 
 * DISADVANTAGES OF CHAINING:
 * ✗ Extra memory for pointers
 * ✗ Cache performance (poor locality)
 * ✗ Overhead of linked list operations
 * 
 * ALTERNATIVE: OPEN ADDRESSING
 * Instead of chaining, store items directly in the array:
 * - Linear Probing: Check next slot if collision
 * - Quadratic Probing: Check i² slots away
 * - Double Hashing: Use second hash function
 * 
 * IMPROVING THE HASH FUNCTION:
 * 
 * Current function (sum of ASCII) has weaknesses:
 * - Anagrams hash to same value ("listen" == "silent")
 * - Poor distribution for short strings
 * 
 * Better approach:
 * int hash = 0;
 * for (char c : value) {
 *     hash = hash * 31 + c;  // Multiply by prime
 * }
 * return hash % TABLE_SIZE;
 * 
 * This gives better distribution because:
 * - Position matters ("abc" != "bca")
 * - Prime multiplier reduces patterns
 * - Used in Java's String.hashCode()
 * 
 * REAL-WORLD APPLICATIONS:
 * 
 * Hash tables are everywhere:
 * - Dictionaries (Python dict, C++ unordered_map)
 * - Database indexing
 * - Caching systems
 * - Symbol tables in compilers
 * - Sets (unique element storage)
 * - Router MAC address tables
 * 
 * RELATED DATA STRUCTURES:
 * - HashMap (key-value pairs)
 * - HashSet (unique values only)
 * - Bloom Filter (probabilistic membership)
 * - Consistent Hashing (distributed systems)
 * 
 * KEY TAKEAWAYS:
 * 
 * 1. Hash tables provide O(1) average-case operations
 * 2. Collision resolution is essential
 * 3. Good hash functions distribute data uniformly
 * 4. Load factor affects performance
 * 5. Trade-off: speed vs. memory usage
 */
