/*
 * Week 12: Binary Trees - Construction and Traversals
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Create a binary tree from level-order input and implement
 * three recursive traversal algorithms: in-order, pre-order, and post-order.
 * 
 * Learning Objectives:
 * - Understand binary tree structure
 * - Implement tree construction from level-order traversal
 * - Master recursive tree traversal algorithms
 * - Learn differences between traversal orders
 * - Practice queue usage for level-order processing
 */

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// Binary Tree Node structure
struct BTNode {
    int val;
    BTNode* left;
    BTNode* right;
    
    // Constructor
    BTNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================================================
// PART 1: CREATE TREE FROM LEVEL-ORDER TRAVERSAL
// ============================================================================

/*
 * Creates a binary tree from level-order traversal input
 * 
 * Level-order means we read nodes level by level, left to right:
 *       1           Level 0: [1]
 *      / \          Level 1: [2, 3]
 *     2   3         Level 2: [4, 5, null, null]
 *    / \
 *   4   5
 * 
 * Input format: [1, 2, 3, 4, 5, -1, -1]
 * Where -1 represents null (no node)
 */
BTNode* createTree(const vector<int>& levelOrder) {
    // Base case: empty tree
    if (levelOrder.empty() || levelOrder[0] == -1)
        return nullptr;
    
    // Create root node
    BTNode* root = new BTNode(levelOrder[0]);
    
    // Queue to process nodes level by level
    queue<BTNode*> q;
    q.push(root);
    
    int i = 1;  // Index for reading from levelOrder
    
    // Process nodes level by level
    while (!q.empty() && i < levelOrder.size()) {
        BTNode* current = q.front();
        q.pop();
        
        // Process left child
        if (i < levelOrder.size() && levelOrder[i] != -1) {
            current->left = new BTNode(levelOrder[i]);
            q.push(current->left);  // Add to queue for its children
        }
        i++;
        
        // Process right child
        if (i < levelOrder.size() && levelOrder[i] != -1) {
            current->right = new BTNode(levelOrder[i]);
            q.push(current->right);  // Add to queue for its children
        }
        i++;
    }
    
    return root;
}

// ============================================================================
// PART 2: TREE TRAVERSAL ALGORITHMS
// ============================================================================

/*
 * IN-ORDER TRAVERSAL: Left -> Root -> Right
 * 
 * For Binary Search Trees, this visits nodes in sorted order!
 * 
 * Example:
 *       4
 *      / \
 *     2   6
 *    / \
 *   1   3
 * 
 * In-order: 1, 2, 3, 4, 6 (sorted!)
 */
vector<int> inorderTraversal(BTNode* root) {
    vector<int> result;
    
    // Base case: empty tree
    if (root == nullptr)
        return result;
    
    // Recursive case: Left -> Root -> Right
    vector<int> leftVals = inorderTraversal(root->left);
    vector<int> rightVals = inorderTraversal(root->right);
    
    // Build result: left subtree values
    for (int val : leftVals)
        result.push_back(val);
    
    // Then root
    result.push_back(root->val);
    
    // Then right subtree values
    for (int val : rightVals)
        result.push_back(val);
    
    return result;
}

/*
 * PRE-ORDER TRAVERSAL: Root -> Left -> Right
 * 
 * Useful for creating a copy of the tree or prefix expression evaluation
 * 
 * Example:
 *       4
 *      / \
 *     2   6
 *    / \
 *   1   3
 * 
 * Pre-order: 4, 2, 1, 3, 6
 */
vector<int> preorderTraversal(BTNode* root) {
    vector<int> result;
    
    // Base case: empty tree
    if (root == nullptr)
        return result;
    
    // Recursive case: Root -> Left -> Right
    vector<int> leftVals = preorderTraversal(root->left);
    vector<int> rightVals = preorderTraversal(root->right);
    
    // Build result: root first
    result.push_back(root->val);
    
    // Then left subtree
    for (int val : leftVals)
        result.push_back(val);
    
    // Then right subtree
    for (int val : rightVals)
        result.push_back(val);
    
    return result;
}

/*
 * POST-ORDER TRAVERSAL: Left -> Right -> Root
 * 
 * Useful for deleting the tree or postfix expression evaluation
 * 
 * Example:
 *       4
 *      / \
 *     2   6
 *    / \
 *   1   3
 * 
 * Post-order: 1, 3, 2, 6, 4
 */
vector<int> postorderTraversal(BTNode* root) {
    vector<int> result;
    
    // Base case: empty tree
    if (root == nullptr)
        return result;
    
    // Recursive case: Left -> Right -> Root
    vector<int> leftVals = postorderTraversal(root->left);
    vector<int> rightVals = postorderTraversal(root->right);
    
    // Build result: left subtree first
    for (int val : leftVals)
        result.push_back(val);
    
    // Then right subtree
    for (int val : rightVals)
        result.push_back(val);
    
    // Finally root
    result.push_back(root->val);
    
    return result;
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// Print traversal result
void printTraversal(const vector<int>& traversal) {
    for (int val : traversal) {
        cout << val << " ";
    }
    cout << endl;
}

// ============================================================================
// MAIN - TEST THE IMPLEMENTATIONS
// ============================================================================

int main() {
    // Create tree from level-order input
    // Tree structure:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    //         \
    //          6
    
    vector<int> levelOrder = {1, 2, 3, 4, 5, -1, -1, -1, -1, -1, 6};
    BTNode* root = createTree(levelOrder);
    
    cout << "Tree created from level-order: [1, 2, 3, 4, 5, -1, -1, -1, -1, -1, 6]" << endl;
    cout << endl;
    
    cout << "In-order Traversal (Left-Root-Right): ";
    printTraversal(inorderTraversal(root));
    
    cout << "Pre-order Traversal (Root-Left-Right): ";
    printTraversal(preorderTraversal(root));
    
    cout << "Post-order Traversal (Left-Right-Root): ";
    printTraversal(postorderTraversal(root));
    
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * 
 * Tree created from level-order: [1, 2, 3, 4, 5, -1, -1, -1, -1, -1, 6]
 * 
 * In-order Traversal (Left-Root-Right): 4 2 5 6 1 3 
 * Pre-order Traversal (Root-Left-Right): 1 2 4 5 6 3 
 * Post-order Traversal (Left-Right-Root): 4 6 5 2 3 1 
 */

/*
 * ALGORITHM ANALYSIS:
 * 
 * TREE CONSTRUCTION (createTree):
 * Time Complexity: O(n)
 * - Process each node exactly once
 * - Queue operations are O(1)
 * 
 * Space Complexity: O(n)
 * - Queue holds at most one level of nodes
 * - Worst case: complete binary tree, last level has n/2 nodes
 * 
 * TRAVERSAL ALGORITHMS:
 * Time Complexity: O(n) for all three
 * - Visit each node exactly once
 * - Constant work per node
 * 
 * Space Complexity: O(h) where h is height
 * - Recursion stack depth equals tree height
 * - Best case (balanced tree): O(log n)
 * - Worst case (skewed tree): O(n)
 * 
 * TRAVERSAL COMPARISON:
 * 
 * Given tree:
 *       1
 *      / \
 *     2   3
 *    / \
 *   4   5
 * 
 * In-order:   4 2 5 1 3  (Left-Root-Right)
 * Pre-order:  1 2 4 5 3  (Root-Left-Right)
 * Post-order: 4 5 2 3 1  (Left-Right-Root)
 * 
 * WHEN TO USE EACH TRAVERSAL:
 * 
 * In-Order:
 * ✓ Binary Search Trees (gives sorted order)
 * ✓ Infix expression evaluation
 * ✓ Finding kth smallest element in BST
 * 
 * Pre-Order:
 * ✓ Creating a copy of the tree
 * ✓ Prefix expression evaluation
 * ✓ Serializing tree structure
 * 
 * Post-Order:
 * ✓ Deleting the tree (children before parent)
 * ✓ Postfix expression evaluation
 * ✓ Calculating directory sizes
 * 
 * Level-Order (BFS):
 * ✓ Finding shortest path
 * ✓ Level-by-level processing
 * ✓ Checking if tree is complete
 * 
 * KEY CONCEPTS DEMONSTRATED:
 * 
 * 1. RECURSIVE THINKING:
 *    - Each traversal is defined recursively
 *    - Process subtrees first, then combine results
 *    - Base case: null node returns empty vector
 * 
 * 2. QUEUE FOR LEVEL-ORDER:
 *    - BFS uses queue (FIFO)
 *    - DFS uses stack (LIFO) or recursion
 *    - Level-order construction processes parents before children
 * 
 * 3. TREE STRUCTURE:
 *    - Binary tree: each node has at most 2 children
 *    - Null pointers represent absence of children
 *    - Level-order input with -1 for null nodes
 * 
 * COMMON TREE PROBLEMS:
 * 
 * Easy:
 * - Maximum depth of binary tree
 * - Same tree (check if two trees are identical)
 * - Invert binary tree
 * - Symmetric tree
 * 
 * Medium:
 * - Level order traversal (BFS)
 * - Validate BST
 * - Lowest common ancestor
 * - Construct tree from in-order and pre-order
 * 
 * Hard:
 * - Serialize and deserialize binary tree
 * - Binary tree maximum path sum
 * 
 * REAL-WORLD APPLICATIONS:
 * 
 * - File systems (directory structures)
 * - Expression parsing (arithmetic expressions)
 * - Database indexing (B-trees, B+ trees)
 * - Decision trees (machine learning)
 * - DOM tree (HTML structure)
 * - Game trees (chess, tic-tac-toe)
 * 
 * PERFORMANCE NOTES:
 * 
 * - Recursive traversals are elegant but use stack space
 * - Iterative versions use explicit stack (same space, no recursion overhead)
 * - Morris traversal achieves O(1) space but modifies tree temporarily
 * - For very deep trees, iterative may be preferred to avoid stack overflow
 */
