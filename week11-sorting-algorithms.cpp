/*
 * Week 11: Sorting Algorithms - Insertion Sort vs Merge Sort
 * CSC 326 - Data Structures
 * Fall 2025
 * 
 * Lab: Compare performance of Insertion Sort and Merge Sort by counting
 * the number of comparisons each algorithm makes on the same dataset.
 * 
 * Learning Objectives:
 * - Implement Insertion Sort (O(n²))
 * - Implement Merge Sort (O(n log n))
 * - Count and compare algorithm operations
 * - Understand time complexity through empirical analysis
 * - Practice divide-and-conquer strategy
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// -----------------------------------------------------------
// Function prototypes
// -----------------------------------------------------------
void insertionSort(int a[], int n, long& comparisons);
void mergeSort(int arr[], int first, int last, long& comparisons);
void merge(int arr[], int first, int mid, int last, long& comparisons);
void fillArray(int arr[], int n);
void printArray(int arr[], int n);

// -----------------------------------------------------------
// main() - Test and compare sorting algorithms
// -----------------------------------------------------------
int main() {
    srand(time(0));

    // Ask the user for the array size
    int n;
    cout << "Enter array size: ";
    cin >> n;

    // Create two identical arrays for fair comparison
    int* arr1 = new int[n];
    int* arr2 = new int[n];

    // Fill arr1 with random numbers and copy it into arr2
    fillArray(arr1, n);
    for (int i = 0; i < n; ++i)
        arr2[i] = arr1[i];

    cout << "\nOriginal array (first 10 elements): ";
    printArray(arr1, min(n, 10));

    long insertionComparisons = 0;
    long mergeComparisons = 0;

    // Sort arr1 with Insertion Sort
    insertionSort(arr1, n, insertionComparisons);

    // Sort arr2 with Merge Sort  
    mergeSort(arr2, 0, n - 1, mergeComparisons);

    // Display comparison counts
    cout << "\n=== PERFORMANCE COMPARISON ===" << endl;
    cout << "Array Size: " << n << endl;
    cout << "Insertion Sort comparisons: " << insertionComparisons << endl;
    cout << "Merge Sort comparisons:     " << mergeComparisons << endl;
    
    // Calculate ratio
    double ratio = (double)insertionComparisons / mergeComparisons;
    cout << "Ratio (Insertion/Merge):    " << ratio << "x" << endl;

    cout << "\nSorted array by Merge Sort (first 10 elements): ";
    printArray(arr2, min(n, 10));

    // Cleanup
    delete[] arr1;
    delete[] arr2;
    
    return 0;
}

// -----------------------------------------------------------
// Insertion Sort - O(n²) time complexity
// -----------------------------------------------------------
void insertionSort(int a[], int n, long& comparisons) {
    for (int i = 1; i < n; i++) {
        int tmp = a[i];
        int j;

        // Insert a[i] into the sorted portion a[0..i-1]
        for (j = i; j > 0 && tmp < a[j - 1]; j--) {
            comparisons++;  // Count each comparison
            a[j] = a[j - 1]; // Shift element to the right
        }
        a[j] = tmp;  // Place element in correct position
    }
}

// -----------------------------------------------------------
// Merge Sort - O(n log n) time complexity
// Divide and Conquer Strategy
// -----------------------------------------------------------
void mergeSort(int arr[], int first, int last, long& comparisons) {
    // Base case: array of size 0 or 1 is already sorted
    if (first >= last) {
        return;
    }
    
    // Divide: Split array in half
    int mid = (first + last) / 2;
    
    // Conquer: Recursively sort both halves
    mergeSort(arr, first, mid, comparisons);
    mergeSort(arr, mid + 1, last, comparisons);
    
    // Combine: Merge the two sorted halves
    merge(arr, first, mid, last, comparisons);
}

// -----------------------------------------------------------
// Merge function - Combines two sorted subarrays
// -----------------------------------------------------------
void merge(int arr[], int first, int mid, int last, long& comparisons) {
    // Calculate sizes of the two subarrays
    int n1 = mid - first + 1;  // Size of left subarray
    int n2 = last - mid;       // Size of right subarray

    // Create temporary arrays
    int* left = new int[n1];
    int* right = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i)
        left[i] = arr[first + i];
    for (int j = 0; j < n2; ++j)
        right[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[first..last]
    int i = 0;      // Index for left subarray
    int j = 0;      // Index for right subarray
    int k = first;  // Index for merged array

    // Compare and merge elements
    while (i < n1 && j < n2) {
        comparisons++;  // Count each comparison
        
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements from left subarray (if any)
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy remaining elements from right subarray (if any)
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }

    // Cleanup temporary arrays
    delete[] left;
    delete[] right;
}

// -----------------------------------------------------------
// Utility function: Fill array with random numbers
// -----------------------------------------------------------
void fillArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        arr[i] = rand() % 1000;  // Random numbers 0-999
}

// -----------------------------------------------------------
// Utility function: Print array elements
// -----------------------------------------------------------
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

/*
 * EXAMPLE OUTPUT:
 * 
 * Enter array size: 1000
 * 
 * Original array (first 10 elements): 41 467 334 500 169 724 478 358 962 464 
 * 
 * === PERFORMANCE COMPARISON ===
 * Array Size: 1000
 * Insertion Sort comparisons: 248534
 * Merge Sort comparisons:     8723
 * Ratio (Insertion/Merge):    28.5x
 * 
 * Sorted array by Merge Sort (first 10 elements): 0 1 2 3 4 5 6 7 8 9
 */

/*
 * ALGORITHM ANALYSIS:
 * 
 * INSERTION SORT:
 * Time Complexity:
 * - Best Case:  O(n)   - Array already sorted
 * - Average:    O(n²)  - Random data
 * - Worst Case: O(n²)  - Array reverse sorted
 * 
 * Space Complexity: O(1) - In-place sorting
 * 
 * Characteristics:
 * - Simple implementation
 * - Stable sort (maintains relative order of equal elements)
 * - Adaptive (efficient for nearly sorted data)
 * - Good for small datasets (n < 50)
 * 
 * MERGE SORT:
 * Time Complexity:
 * - Best Case:  O(n log n)
 * - Average:    O(n log n)
 * - Worst Case: O(n log n)
 * 
 * Space Complexity: O(n) - Requires temporary arrays
 * 
 * Characteristics:
 * - Divide and conquer strategy
 * - Stable sort
 * - Consistent performance (always O(n log n))
 * - Excellent for large datasets
 * - Not adaptive (same performance regardless of input order)
 * 
 * COMPARISON INSIGHTS:
 * 
 * For n = 100:
 * - Insertion Sort: ~2,500 comparisons (n²/4)
 * - Merge Sort:     ~600 comparisons (n log n)
 * - Ratio: ~4x
 * 
 * For n = 1,000:
 * - Insertion Sort: ~250,000 comparisons
 * - Merge Sort:     ~9,000 comparisons
 * - Ratio: ~28x
 * 
 * For n = 10,000:
 * - Insertion Sort: ~25,000,000 comparisons
 * - Merge Sort:     ~120,000 comparisons
 * - Ratio: ~208x
 * 
 * As n grows, Merge Sort's advantage becomes MASSIVE!
 * 
 * WHEN TO USE EACH:
 * 
 * Use Insertion Sort when:
 * ✓ Array is small (n < 50)
 * ✓ Array is nearly sorted
 * ✓ Memory is very limited
 * ✓ Simplicity is important
 * 
 * Use Merge Sort when:
 * ✓ Array is large (n > 1000)
 * ✓ Guaranteed O(n log n) is needed
 * ✓ Stability is required
 * ✓ Linked lists (excellent for linked list sorting)
 * 
 * OTHER POPULAR SORTING ALGORITHMS:
 * 
 * Quick Sort:
 * - Average: O(n log n), Worst: O(n²)
 * - Fastest in practice for arrays
 * - Not stable
 * 
 * Heap Sort:
 * - Always O(n log n)
 * - In-place (O(1) space)
 * - Not stable
 * 
 * Counting Sort:
 * - O(n + k) where k is range of input
 * - Only for integers in limited range
 * - Very fast when applicable
 * 
 * REAL-WORLD USAGE:
 * 
 * - C++ std::sort(): Uses Introsort (hybrid Quick/Heap/Insertion)
 * - Python sorted(): Uses Timsort (hybrid Merge/Insertion)
 * - Java Arrays.sort(): Uses Dual-Pivot Quicksort
 * - Database systems: Often use Merge Sort for external sorting
 * 
 * KEY TAKEAWAY:
 * This lab demonstrates why Big O notation matters!
 * The difference between O(n²) and O(n log n) becomes
 * dramatic as dataset size increases.
 */
