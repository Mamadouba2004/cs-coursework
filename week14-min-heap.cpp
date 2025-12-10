/*
 * Week 14: Priority Queues and Heaps - Min Heap Implementation
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Implement insertion operation for a Min Heap using array-based representation
 * 
 * Learning Objectives:
 * - Understand heap data structure and heap property
 * - Implement array-based heap representation
 * - Master heapify-up operation
 * - Learn priority queue fundamentals
 * - Practice parent-child index calculations
 * 
 * Key Concepts:
 * - Min Heap Property: Parent ≤ Children
 * - Complete Binary Tree: Filled left-to-right, level by level
 * - Array Representation: Parent at (i-1)/2, Children at 2i+1 and 2i+2
 */

#include <iostream>
#include <vector>

class MinHeap {
private:
    std::vector<int> data;  // Array-based heap storage

    /*
     * HEAPIFY UP - Restore min-heap property after insertion
     * 
     * Process:
     * 1. Start at newly inserted element (last position)
     * 2. Compare with parent
     * 3. If smaller than parent, swap and move up
     * 4. Repeat until heap property satisfied or reach root
     * 
     * Time Complexity: O(log n)
     * - Maximum swaps = height of tree = log n
     * 
     * Space Complexity: O(1)
     * - Only uses constant extra space
     */
    void heapifyUp(int idx) {
        // Step 1: Keep going while not at root (idx > 0)
        while (idx > 0) {
            
            // Step 2: Calculate parent index
            // Parent formula: (child_index - 1) / 2
            // Example: child at 4 → parent at (4-1)/2 = 1
            int parent = (idx - 1) / 2;
            
            // Step 3: Compare with parent (MIN-HEAP rule!)
            // Min-Heap: Parent must be ≤ children
            // If current < parent, we need to swap
            if (data[idx] < data[parent]) {
                
                // Step 4: Swap with parent
                std::swap(data[idx], data[parent]);
                
                // Step 5: Move up to parent position
                // Continue checking from parent's position
                idx = parent;
                
            } else {
                // Step 6: Heap property satisfied, stop
                // Current element is in correct position
                break;
            }
        }
    }

public:
    MinHeap() = default;

    /*
     * INSERT - Add new value to heap
     * 
     * Algorithm:
     * 1. Add element at end (maintains complete tree property)
     * 2. Bubble up to restore heap property
     * 
     * Time Complexity: O(log n)
     * - Append to vector: O(1) amortized
     * - Heapify up: O(log n)
     * 
     * Example: Insert 2 into heap [3, 7, 9, 5]
     * 
     * Initial:        3
     *               /   \
     *              7     9
     *             /
     *            5
     * 
     * After append:   3
     *               /   \
     *              7     9
     *             / \
     *            5   2   (violates heap property!)
     * 
     * After heapify:  2   (2 bubbled to root)
     *               /   \
     *              3     9
     *             / \
     *            5   7
     */
    void insert(int value) {
        // Step 1: Place the new value at the end
        // This maintains the complete binary tree structure
        data.push_back(value);
        
        // Step 2: Restore heap property by heapifying up
        // Start from the newly inserted element
        heapifyUp(data.size() - 1);
    }

    /*
     * PRINT - Display current heap contents
     * 
     * Shows array representation of heap
     * Not the tree structure, but the underlying array
     */
    void print() const {
        std::cout << "Heap contents: ";
        for (int v : data) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    
    /*
     * GET MIN - Return minimum element (root)
     * 
     * In a min-heap, the root always contains the minimum
     * Time Complexity: O(1)
     */
    int getMin() const {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return data[0];
    }
    
    /*
     * GET SIZE - Return number of elements
     */
    int size() const {
        return data.size();
    }
    
    /*
     * IS EMPTY - Check if heap is empty
     */
    bool isEmpty() const {
        return data.empty();
    }
};

// ============================================================================
// MAIN - TEST THE MIN HEAP IMPLEMENTATION
// ============================================================================

int main() {
    MinHeap h;

    std::cout << "=== MIN HEAP INSERTION DEMO ===" << std::endl;
    std::cout << "\nInserting elements: 7, 3, 9, 2, 5\n" << std::endl;

    // Sequential insertions with step-by-step visualization
    std::cout << "Insert 7:" << std::endl;
    h.insert(7);
    h.print();  // Expected: 7
    
    std::cout << "\nInsert 3:" << std::endl;
    h.insert(3);
    h.print();  // Expected: 3 7 (3 becomes root)
    
    std::cout << "\nInsert 9:" << std::endl;
    h.insert(9);
    h.print();  // Expected: 3 7 9
    
    std::cout << "\nInsert 2:" << std::endl;
    h.insert(2);
    h.print();  // Expected: 2 3 9 7 (2 bubbles to root)
    
    std::cout << "\nInsert 5:" << std::endl;
    h.insert(5);
    h.print();  // Expected: 2 3 9 7 5

    std::cout << "\n=== FINAL RESULT ===" << std::endl;
    h.print();  // Expected: Heap contents: 2 3 9 7 5
    
    std::cout << "\nMinimum element: " << h.getMin() << std::endl;
    std::cout << "Heap size: " << h.size() << std::endl;

    return 0;
}

/*
 * EXPECTED OUTPUT:
 * 
 * === MIN HEAP INSERTION DEMO ===
 * 
 * Inserting elements: 7, 3, 9, 2, 5
 * 
 * Insert 7:
 * Heap contents: 7 
 * 
 * Insert 3:
 * Heap contents: 3 7 
 * 
 * Insert 9:
 * Heap contents: 3 7 9 
 * 
 * Insert 2:
 * Heap contents: 2 3 9 7 
 * 
 * Insert 5:
 * Heap contents: 2 3 9 7 5 
 * 
 * === FINAL RESULT ===
 * Heap contents: 2 3 9 7 5 
 * 
 * Minimum element: 2
 * Heap size: 5
 */

/*
 * HEAP VISUALIZATION:
 * 
 * Array: [2, 3, 9, 7, 5]
 * 
 * Tree Structure:
 *           2       ← Index 0 (root)
 *         /   \
 *        3     9    ← Index 1, 2
 *       / \
 *      7   5        ← Index 3, 4
 * 
 * Parent-Child Relationships:
 * - Node at index i:
 *   - Parent at: (i - 1) / 2
 *   - Left child at: 2i + 1
 *   - Right child at: 2i + 2
 * 
 * Index Mapping:
 * Index | Value | Parent | Left Child | Right Child
 * ------|-------|--------|------------|------------
 *   0   |   2   |  N/A   |     1      |     2
 *   1   |   3   |   0    |     3      |     4
 *   2   |   9   |   0    |     5      |     6
 *   3   |   7   |   1    |     7      |     8
 *   4   |   5   |   1    |     9      |    10
 * 
 * Heap Property Verification:
 * ✓ 2 < 3 (parent < left child)
 * ✓ 2 < 9 (parent < right child)
 * ✓ 3 < 7 (parent < left child)
 * ✓ 3 < 5 (parent < right child)
 */

/*
 * ALGORITHM ANALYSIS
 * 
 * TIME COMPLEXITY:
 * 
 * Operation   | Best Case | Average | Worst Case | Notes
 * ------------|-----------|---------|------------|------------------
 * Insert      | O(1)      | O(log n)| O(log n)  | Best: no swaps needed
 * Get Min     | O(1)      | O(1)    | O(1)      | Always at root
 * Size        | O(1)      | O(1)    | O(1)      | Vector size
 * 
 * SPACE COMPLEXITY: O(n) for storing n elements
 * 
 * COMPARISON WITH OTHER DATA STRUCTURES:
 * 
 * Structure     | Insert  | Find Min | Extract Min | Space
 * --------------|---------|----------|-------------|-------
 * Unsorted Array| O(1)    | O(n)     | O(n)        | O(n)
 * Sorted Array  | O(n)    | O(1)     | O(1)        | O(n)
 * **Min Heap**  | **O(log n)**| **O(1)**| **O(log n)**| **O(n)**
 * BST (balanced)| O(log n)| O(log n) | O(log n)    | O(n)
 * 
 * MIN HEAP vs MAX HEAP:
 * 
 * Property      | Min Heap        | Max Heap
 * --------------|-----------------|------------------
 * Root contains | Minimum element | Maximum element
 * Parent vs child| Parent ≤ Child | Parent ≥ Child
 * Use case      | Priority queue  | Priority queue
 *               | (smallest first)| (largest first)
 * 
 * HEAPIFY UP EXAMPLE:
 * 
 * Insert 2 into [3, 7, 9, 5]:
 * 
 * Step 1: Append to end
 * Array: [3, 7, 9, 5, 2]
 *          3
 *        /   \
 *       7     9
 *      / \
 *     5   2   ← New element
 * 
 * Step 2: Compare 2 with parent 7
 * 2 < 7, so swap
 * Array: [3, 2, 9, 5, 7]
 *          3
 *        /   \
 *       2     9
 *      / \
 *     5   7
 * 
 * Step 3: Compare 2 with parent 3
 * 2 < 3, so swap
 * Array: [2, 3, 9, 5, 7]
 *          2       ← Final position
 *        /   \
 *       3     9
 *      / \
 *     5   7
 * 
 * Step 4: 2 is now at root, done!
 * 
 * COMPLETE BINARY TREE PROPERTY:
 * 
 * Definition: All levels are fully filled except possibly the last,
 * which is filled from left to right.
 * 
 * Valid Complete Trees:
 *       1              1              1
 *      / \            / \            / \
 *     2   3          2   3          2   3
 *    /              / \            / \ /
 *   4              4   5          4  5 6
 * 
 * Invalid (not complete):
 *       1              1
 *      / \            / \
 *     2   3          2   3
 *      \                  \
 *       4                  4
 * 
 * Why Complete Tree Matters:
 * - Guarantees O(log n) height
 * - Enables efficient array representation
 * - No wasted space in array
 * 
 * APPLICATIONS OF MIN HEAPS:
 * 
 * 1. **Priority Queues:**
 *    - Task scheduling (smallest priority first)
 *    - Event-driven simulation
 *    - Dijkstra's algorithm
 * 
 * 2. **Heap Sort:**
 *    - Build heap: O(n)
 *    - Extract min n times: O(n log n)
 *    - In-place sorting algorithm
 * 
 * 3. **K Smallest Elements:**
 *    - Efficiently find k smallest from n elements
 *    - Better than sorting entire array
 * 
 * 4. **Median Maintenance:**
 *    - Use two heaps (min + max)
 *    - Efficiently track median of stream
 * 
 * 5. **Graph Algorithms:**
 *    - Dijkstra's shortest path
 *    - Prim's minimum spanning tree
 *    - A* pathfinding
 * 
 * HEAP OPERATIONS (NOT IMPLEMENTED HERE):
 * 
 * Extract Min:
 * 1. Save root value
 * 2. Move last element to root
 * 3. Heapify down to restore property
 * Time: O(log n)
 * 
 * Decrease Key:
 * 1. Decrease value at index
 * 2. Heapify up from that index
 * Time: O(log n)
 * 
 * Build Heap:
 * 1. Start from last non-leaf
 * 2. Heapify down for each
 * Time: O(n) - better than n insertions!
 * 
 * REAL-WORLD USAGE:
 * 
 * C++ STL:
 * - std::priority_queue<int> (max heap by default)
 * - std::priority_queue<int, vector<int>, greater<int>> (min heap)
 * 
 * Python:
 * - heapq module (min heap)
 * - heapq.heappush(), heapq.heappop()
 * 
 * Java:
 * - PriorityQueue<Integer> (min heap by default)
 * 
 * COMMON PITFALLS:
 * 
 * ✗ Forgetting to subtract 1 in parent calculation
 *   Wrong: parent = idx / 2
 *   Right: parent = (idx - 1) / 2
 * 
 * ✗ Using wrong comparison for min vs max heap
 *   Min heap: data[child] < data[parent]
 *   Max heap: data[child] > data[parent]
 * 
 * ✗ Not checking if at root before accessing parent
 *   Must check: idx > 0 before calculating parent
 * 
 * KEY TAKEAWAYS:
 * 
 * 1. Heaps provide O(log n) insertion and O(1) min access
 * 2. Array representation is space-efficient
 * 3. Complete binary tree property ensures balanced height
 * 4. Parent-child index formulas are crucial
 * 5. Heapify operations maintain heap property
 * 6. Perfect for priority queue implementations
 */
