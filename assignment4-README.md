# Assignment 4: Hash Map with Chaining

## Overview
Implementation of the ADT Map using a hash table with separate chaining for collision resolution. This assignment demonstrates advanced data structures concepts including:
- Hash table implementation
- Collision resolution via chaining (linked lists)
- Template programming in C++
- Smart pointers (std::shared_ptr)
- Object-oriented design with inheritance

## Course Information
**Course:** CSC 326 - Data Structures  
**Institution:** CUNY College of Staten Island  
**Semester:** Fall 2025  
**Due Date:** November 26, 2025

## Problem Statement
Implement a hash map that:
- Uses separate chaining for collision resolution
- Supports key-value pair storage and retrieval
- Implements standard map operations (add, remove, contains, etc.)
- Handles hash collisions gracefully
- Uses modern C++ features (templates, smart pointers)

## File Structure
```
assignment4/
├── MapEntry.h          - Base key-value pair class
├── HashedEntry.h       - Extended entry with next pointer for chaining
├── HashedMap.h         - Complete hash map implementation
├── main.cpp            - Comprehensive test suite
└── README.md           - This file
```

## Implementation Details

### 1. MapEntry Class
Base class representing a simple key-value pair.

**Key Features:**
- Template class supporting any key/value types
- Comparison operators for sorting
- Protected setter for derived classes

### 2. HashedEntry Class
Extends MapEntry to support chaining.

**Key Features:**
- Inherits from MapEntry
- Contains `nextPtr` for linked list chaining
- Uses `std::shared_ptr` for automatic memory management

### 3. HashedMap Class
Complete hash map implementation.

**Key Features:**
- **Hash Function:** `hash = (hash * 31 + char) % tableSize`
- **Collision Resolution:** Separate chaining with linked lists
- **Dynamic Sizing:** Configurable table size
- **Smart Pointers:** Automatic memory management

**Supported Operations:**
```cpp
bool add(const KeyType&, const ValueType&)        // Insert or update
bool remove(const KeyType&)                        // Delete entry
bool getValue(const KeyType&, ValueType&) const    // Retrieve value
bool contains(const KeyType&) const                // Check existence
bool isEmpty() const                               // Check if empty
int getNumberOfEntries() const                     // Get count
void clear()                                       // Remove all entries
```

## Algorithm Analysis

### Time Complexity

| Operation | Average Case | Worst Case |
|-----------|-------------|------------|
| add()     | O(1)        | O(n)       |
| remove()  | O(1)        | O(n)       |
| getValue()| O(1)        | O(n)       |
| contains()| O(1)        | O(n)       |

**Notes:**
- Average case assumes uniform distribution
- Worst case occurs when all keys hash to same index
- Performance depends on load factor (items/table_size)

### Space Complexity
- O(n) where n is the number of entries
- Additional O(m) for hash table array where m is table size

## Hash Function Explanation

```cpp
int getHashIndex(const KeyType& key) const {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % hashTableSize;
    }
    return hash;
}
```

**Why This Works:**
1. **Prime Multiplier (31)**: Reduces collisions, well-tested in Java's String.hashCode()
2. **Character Processing**: Each character contributes to hash value
3. **Modulo Operation**: Ensures hash fits within table size
4. **Continuous Modulo**: Prevents integer overflow

## Collision Handling

**Separate Chaining Strategy:**
```
Index 0: Alice(1234) -> NULL
Index 1: Bob(5678) -> Charlie(9012) -> NULL  ← Collision!
Index 2: David(3456) -> NULL
Index 3: Eve(7890) -> NULL
```

When a collision occurs:
1. New entry is added to front of chain (O(1) insertion)
2. Search traverses chain to find matching key
3. Removal updates pointers to maintain chain

## Test Cases

### Test 1: Basic Operations
- Add 5 entries
- Verify all operations work correctly
- Test isEmpty() and getNumberOfEntries()

### Test 2: Update Existing Key
- Add entry with key "Alice"
- Add again with same key but different value
- Verify value is updated (not duplicated)

### Test 3: Collision Demonstration
- Create small hash table (size 5)
- Add multiple entries that will collide
- Verify all entries retrievable (proves chaining works!)

### Test 4: Remove Operation
- Remove entry from middle of chain
- Remove entry at head of chain
- Verify correct pointer updates

### Test 5: Edge Cases
- Operations on empty map
- Remove non-existent key
- getValue for missing key

## Compilation and Execution

### Compile
```bash
g++ -std=c++11 -Wall -o hashmap main.cpp
```

### Run
```bash
./hashmap
```

### Expected Output
```
=== Testing HashedMap ===

Test 1: Is map empty? YES
Number of entries: 0

Test 2: Adding entries...
Added 5 entries
Number of entries: 5

Test 3: Testing contains()...
Contains 'Alice'? YES
Contains 'Bob'? YES
Contains 'Zoe'? NO

...

=== ALL TESTS COMPLETE ===
```

## Key Concepts Demonstrated

### 1. Template Programming
- Generic types for maximum flexibility
- Type safety at compile time
- Code reuse across different data types

### 2. Smart Pointers
- `std::shared_ptr` for automatic memory management
- No manual delete needed
- Prevents memory leaks

### 3. Inheritance
- HashedEntry extends MapEntry
- Code reuse and logical hierarchy
- Protected members for derived class access

### 4. Hash Table Design
- Array of linked lists
- Hash function for index calculation
- Chaining for collision resolution

## Performance Considerations

### Load Factor
```
Load Factor = Number of Entries / Table Size
```

**Optimal Range:** 0.5 - 0.75
- Too low: Wasted space
- Too high: More collisions, slower lookups

### Rehashing (Not Implemented)
In production systems, when load factor exceeds threshold:
1. Create larger table (typically 2x size)
2. Rehash all existing entries
3. Improves average case performance

## Real-World Applications

Hash maps are used in:
- **Databases:** Indexing for fast lookups
- **Caching:** Store frequently accessed data
- **Symbol Tables:** Compilers and interpreters
- **Sets:** Unique element storage
- **Dictionaries:** Language translation
- **Routing Tables:** Network packet routing

## Advantages vs. Other Data Structures

| Data Structure | Search | Insert | Delete |
|---------------|--------|--------|--------|
| Array         | O(n)   | O(1)*  | O(n)   |
| Sorted Array  | O(log n)| O(n)  | O(n)   |
| Linked List   | O(n)   | O(1)*  | O(n)   |
| BST (balanced)| O(log n)| O(log n)| O(log n)|
| **Hash Map**  | **O(1)**| **O(1)**| **O(1)**|

*at specific position

## Limitations and Trade-offs

**Advantages:**
✓ Very fast average-case operations
✓ Simple to implement
✓ Flexible key types (with good hash function)

**Disadvantages:**
✗ No ordering of keys
✗ Wasted space if load factor is low
✗ Performance degrades with poor hash function
✗ Worst-case O(n) if all collisions

## Extensions and Improvements

**Possible Enhancements:**
1. **Dynamic Resizing:** Auto-resize when load factor exceeds threshold
2. **Iterator Support:** Traverse all entries
3. **Open Addressing:** Alternative collision resolution
4. **Better Hash Functions:** Use standard library hash for complex types
5. **Load Factor Monitoring:** Track and report performance metrics

## Learning Outcomes

This assignment demonstrates proficiency in:
- ✅ Hash table implementation
- ✅ Collision resolution strategies
- ✅ Template metaprogramming
- ✅ Memory management with smart pointers
- ✅ Object-oriented design
- ✅ Algorithm analysis
- ✅ Comprehensive testing

## Author
**Mamadou Ba**  
Computer Science @ CUNY College of Staten Island  
Fall 2025

---

**Note:** This implementation is for educational purposes and demonstrates fundamental hash map concepts. Production systems would include additional features like dynamic resizing, thread safety, and optimized hash functions.
