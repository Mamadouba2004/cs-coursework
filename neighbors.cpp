#include <iostream>
#include <string>
using namespace std;

const int N = 5;
int M[N][N];    // adjacency matrix (already built)
int M2[N][N];   // M^2
int M3[N][N];   // M^3

void multiply(int A[N][N], int B[N][N], int R[N][N]) {
    // TODO 4: Implement matrix multiplication R = A * B
    // Hint: Triple nested loops:
    // for i in [0..N-1]
    for (int i = 0; i < N; ++i) {
    //   for j in [0..N-1]
    for(int j = 0; j < N; ++j){
    //     R[i][j] = sum over k of (A[i][k] * B[k][j]);
    // Initialize result cell to 0
            R[i][j] = 0;
    // Inner loop: sum over k
            for (int k = 0; k < N; ++k) {
                R[i][j] += A[i][k] * B[k][j];
                //         What indices multiply together?
            }
        }
    }
}

void printNeighborsKSteps(int Mk[N][N], int start, int k) {
    const string names = "ABCDE";
    cout << k << "-length away neighbors of " << names[start] << ": ";
    for (int j = 0; j < N; ++j) {
        if (Mk[start][j] > 0) { // there exists a path of length k
            cout << names[j] << " ";
        }
    }
    cout << "\n";
}

int main() {
    // Assume M is already filled as the adjacency matrix
    
    // TODO 5: Compute M2 = M * M
    multiply(M, M, M2);  // What matrices multiply?
    
    // TODO 6: Compute M3 = M2 * M
    multiply(M2, M, M3);  // What matrices multiply?
    
    int start = 0; // A as starting node
    
    // TODO 7: Print 2-length away neighbors of A
    printNeighborsKSteps(M2, start, 2);  // Which matrix shows 2-step paths?
    
    // TODO 8: Print 3-length away neighbors of A
    printNeighborsKSteps(M3, start, 3);  // Which matrix shows 3-step paths?

    return 0;
}
