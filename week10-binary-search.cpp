/*
 * Week 10: Algorithm Analysis and Searching
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Binary Search Implementation and Analysis
 * 
 * Exercise: Implement manual binary search on sorted containers using iterators.
 * Compare performance across std::set and std::vector, and implement both
 * iterative and recursive versions.
 * 
 * Learning Objectives:
 * - Understand binary search algorithm (O(log n))
 * - Work with iterators vs indices
 * - Compare iterative vs recursive implementations
 * - Analyze algorithm efficiency through iteration counting
 * - Practice with STL containers (set and vector)
 */

#include <iostream>
#include <set>
#include <vector>
#include <iterator>

// ================================================
// PART 1: Binary Search on std::set (iterators)
// ================================================
bool binarySearchSet(const std::set<int>& s, int key, int* iters = nullptr);

// ================================================
// PART 2: Binary Search on std::vector (indices)
// ================================================
bool binarySearchVector(const std::vector<int>& v, int key, int* iters = nullptr);

// ================================================
// PART 3: Recursive Binary Search on std::vector
// ================================================
bool binarySearchRecursive(const std::vector<int>& v, int key, 
                          int lhs, int rhs, int* iters);
bool binarySearchRecursive(const std::vector<int>& v, int key, int* iters = nullptr);

// ================================================
// MAIN - Test all implementations
// ================================================
int main() {
    // Create and populate set
    std::set<int> numSet;
    int init[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    numSet.insert(init, init + (sizeof(init) / sizeof(init[0])));
    
    // Create and populate vector with same data
    std::vector<int> numVec(init, init + (sizeof(init) / sizeof(init[0])));
    
    // Get key from user
    int key = 0;
    std::cout << "Enter a number to search: ";
    std::cin >> key;
    std::cout << "\n";
    
    // ================================================
    // Test 1: Binary Search on SET
    // ================================================
    std::cout << "=== PART 1: Binary Search on std::set ===\n";
    int setIters = 0;
    bool setFound = binarySearchSet(numSet, key, &setIters);
    
    if (setFound)
        std::cout << key << " found in the set!\n";
    else
        std::cout << key << " not found in the set.\n";
    
    // Verify with std::set::find()
    if (numSet.find(key) != numSet.end())
        std::cout << "(Verification) std::set::find() found the key.\n";
    else
        std::cout << "(Verification) std::set::find() did not find the key.\n";
    
    std::cout << "Iterations: " << setIters << "\n\n";
    
    // ================================================
    // Test 2: Binary Search on VECTOR (iterative)
    // ================================================
    std::cout << "=== PART 2: Binary Search on std::vector (iterative) ===\n";
    int vecIters = 0;
    bool vecFound = binarySearchVector(numVec, key, &vecIters);
    
    if (vecFound)
        std::cout << key << " found in the vector!\n";
    else
        std::cout << key << " not found in the vector.\n";
    
    std::cout << "Iterations: " << vecIters << "\n\n";
    
    // ================================================
    // Test 3: Binary Search on VECTOR (recursive)
    // ================================================
    std::cout << "=== PART 3: Binary Search on std::vector (recursive) ===\n";
    int recIters = 0;
    bool recFound = binarySearchRecursive(numVec, key, &recIters);
    
    if (recFound)
        std::cout << key << " found in the vector!\n";
    else
        std::cout << key << " not found in the vector.\n";
    
    std::cout << "Iterations: " << recIters << "\n\n";
    
    // ================================================
    // Summary
    // ================================================
    std::cout << "=== SUMMARY ===\n";
    std::cout << "All three methods found: " << (setFound && vecFound && recFound ? "YES" : "NO") << "\n";
    std::cout << "Set iterations:       " << setIters << "\n";
    std::cout << "Vector iterations:    " << vecIters << "\n";
    std::cout << "Recursive iterations: " << recIters << "\n";
    
    return 0;
}

// ================================================
// IMPLEMENTATION: Binary Search on Set
// Uses iterators (std::set doesn't support random access)
// ================================================
bool binarySearchSet(const std::set<int>& s, int key, int* iters) {
    std::set<int>::const_iterator lhs = s.begin();
    std::set<int>::const_iterator rhs = s.end();
    
    int count = 0;
    
    while (lhs != rhs) {
        // Calculate distance and midpoint
        // Note: std::set uses bidirectional iterators, not random access
        int dist = std::distance(lhs, rhs);
        int mid_dist = dist / 2;
        
        std::set<int>::const_iterator mid = lhs;
        std::advance(mid, mid_dist);  // Move iterator forward by mid_dist
        
        ++count;
        
        if (*mid == key) {
            if (iters) *iters = count;
            return true;
        } else if (*mid < key) {
            // Search right half: move lhs past mid
            std::set<int>::const_iterator next = mid;
            ++next;
            lhs = next;
        } else {
            // Search left half: shrink rhs to mid
            rhs = mid;
        }
    }
    
    if (iters) *iters = count;
    return false;
}

// ================================================
// IMPLEMENTATION: Binary Search on Vector (iterative)
// Uses indices (std::vector supports random access)
// ================================================
bool binarySearchVector(const std::vector<int>& v, int key, int* iters) {
    int lhs = 0;
    int rhs = v.size();  // [lhs, rhs) - half-open interval
    
    int count = 0;
    
    while (lhs < rhs) {
        ++count;
        
        // Calculate midpoint (avoiding overflow)
        int mid = lhs + (rhs - lhs) / 2;
        
        if (v[mid] == key) {
            if (iters) *iters = count;
            return true;
        } else if (v[mid] < key) {
            // Search right half: [mid+1, rhs)
            lhs = mid + 1;
        } else {
            // Search left half: [lhs, mid)
            rhs = mid;
        }
    }
    
    if (iters) *iters = count;
    return false;
}

// ================================================
// IMPLEMENTATION: Binary Search Recursive (helper)
// ================================================
bool binarySearchRecursive(const std::vector<int>& v, int key, 
                          int lhs, int rhs, int* iters) {
    // Base case: empty range
    if (lhs >= rhs) {
        return false;
    }
    
    // Increment counter
    if (iters) (*iters)++;
    
    // Calculate mid
    int mid = lhs + (rhs - lhs) / 2;
    
    // Check if found
    if (v[mid] == key) {
        return true;
    }
    
    // Recursive case: search left or right
    if (v[mid] < key) {
        // Search RIGHT half: [mid+1, rhs)
        return binarySearchRecursive(v, key, mid + 1, rhs, iters);
    } else {
        // Search LEFT half: [lhs, mid)
        return binarySearchRecursive(v, key, lhs, mid, iters);
    }
}

// ================================================
// IMPLEMENTATION: Binary Search Recursive (wrapper)
// ================================================
bool binarySearchRecursive(const std::vector<int>& v, int key, int* iters) {
    if (iters) *iters = 0;
    return binarySearchRecursive(v, key, 0, v.size(), iters);
}

/*
 * EXAMPLE OUTPUT:
 * 
 * Enter a number to search: 14
 * 
 * === PART 1: Binary Search on std::set ===
 * 14 found in the set!
 * (Verification) std::set::find() found the key.
 * Iterations: 3
 * 
 * === PART 2: Binary Search on std::vector (iterative) ===
 * 14 found in the vector!
 * Iterations: 3
 * 
 * === PART 3: Binary Search on std::vector (recursive) ===
 * 14 found in the vector!
 * Iterations: 3
 * 
 * === SUMMARY ===
 * All three methods found: YES
 * Set iterations:       3
 * Vector iterations:    3
 * Recursive iterations: 3
 */

/*
 * ALGORITHM ANALYSIS:
 * 
 * Time Complexity: O(log n)
 * - Each iteration eliminates half the search space
 * - For n=10 elements, max iterations = ceil(log2(10)) ≈ 4
 * - For n=1000 elements, max iterations ≈ 10
 * - For n=1,000,000 elements, max iterations ≈ 20
 * 
 * Space Complexity:
 * - Iterative: O(1) - constant space
 * - Recursive: O(log n) - recursion stack depth
 * 
 * COMPARISON: std::set vs std::vector
 * 
 * std::set:
 * - Uses bidirectional iterators
 * - std::distance() and std::advance() needed
 * - Slightly more overhead per iteration
 * - Already sorted by design
 * 
 * std::vector:
 * - Uses random access (indices)
 * - Direct array access: v[mid]
 * - Faster per iteration
 * - Must be pre-sorted for binary search
 * 
 * COMPARISON: Iterative vs Recursive
 * 
 * Iterative:
 * ✓ More efficient (no stack overhead)
 * ✓ No risk of stack overflow
 * ✓ Easier to optimize
 * 
 * Recursive:
 * ✓ More elegant/readable
 * ✓ Easier to understand logically
 * ✗ Function call overhead
 * ✗ Stack space usage
 * 
 * KEY INSIGHTS:
 * 
 * 1. Binary Search Requirements:
 *    - Data must be SORTED
 *    - Need random or bidirectional access
 *    - Works on any comparable type
 * 
 * 2. When to use Binary Search:
 *    ✓ Large sorted datasets
 *    ✓ Frequent searches
 *    ✓ When O(log n) matters vs O(n) linear search
 * 
 * 3. Iterator vs Index:
 *    - Iterators: More generic, works with any container
 *    - Indices: Faster, but only for random-access containers
 * 
 * 4. Overflow Prevention:
 *    - mid = lhs + (rhs - lhs) / 2  ✓ SAFE
 *    - mid = (lhs + rhs) / 2        ✗ CAN OVERFLOW
 * 
 * REAL-WORLD APPLICATIONS:
 * - Database indexing
 * - Dictionary/phone book lookup
 * - Finding version in sorted changelog
 * - Game development (collision detection)
 * - Finding bugs in code (git bisect)
 */
