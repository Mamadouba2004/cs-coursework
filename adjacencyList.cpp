#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int N = 5; // number of vertices: A, B, C, D, E

// Global adjacency list
vector<int> adjList[N];

// Helper to print adjacency list
void printAdjList(const vector<int> graph[]) {
    const string names = "ABCDE";
    for (int u = 0; u < N; ++u) {
        cout << names[u] << ": ";
        for (int v : graph[u]) {
            cout << names[v] << " ";
        }
        cout << "\n";
    }
}

int main() {
    // TODO 1: Build the adjacency list using the given edges:
    // A->B, B->C, B->D, C->E, E->D, D->A

    // Example of how to add an edge u -> v:
    // adjList[u].push_back(v);

    // TODO 1.1: Add edge A->B
    adjList[0].push_back(1);
    // TODO 1.2: Add edge B->C
    adjList[1].push_back(2);
    // TODO 1.3: Add edge B->D
    adjList[1].push_back(3);
    // TODO 1.4: Add edge C->E
    adjList[2].push_back(4);
    // TODO 1.5: Add edge E->D
    adjList[4].push_back(3);
    // TODO 1.6: Add edge D->A
    adjList[3].push_back(0);

    cout << "Adjacency List Representation:\n";
    printAdjList(adjList);

    return 0;
}
