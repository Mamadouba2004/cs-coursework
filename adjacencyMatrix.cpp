#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int N = 5;
int adjMat[N][N]; // adjacency matrix

void initMatrix() {
    // TODO 2: Initialize all entries of adjMat to 0
    for (int i = 0; i < N; ++i){
       for (int j = 0; j < N; ++j){
          adjMat[i][j]=0;
       }
    }
}

void buildMatrix() {
    // TODO 3: Set adjMat[u][v] = 1 for each directed edge:
    // A->B, B->C, B->D, C->E, E->D, D->A
    adjMat[0][1]=1;
    // Remember mapping: A=0, B=1, C=2, D=3, E=4
        // TODO 3.2: B->C (from 1 to 2)
    adjMat[1][2] = 1;

    // TODO 3.3: B->D (from 1 to 3)
    adjMat[1][3] = 1;

    // TODO 3.4: C->E (from 2 to 4)
    adjMat[2][4] = 1;

    // TODO 3.5: E->D (from 4 to 3)
    adjMat[4][3] = 1;

    // TODO 3.6: D->A (from 3 to 0)
    adjMat[3][0] = 1;
    // Example:
    // adjMat[0][1] = 1; // A->B
}

void printMatrix() {
    const string names = "ABCDE";
    cout << "   ";
    for (int j = 0; j < N; ++j) cout << names[j] << " ";
    cout << "\n";

    for (int i = 0; i < N; ++i) {
        cout << names[i] << ": ";
        for (int j = 0; j < N; ++j) {
            cout << adjMat[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    initMatrix();
    buildMatrix();
    cout << "Adjacency Matrix:\n";
    printMatrix();
    return 0;
}
