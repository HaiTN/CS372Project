#include <iostream>
#include <stdio.h>

using namespace std;

struct Node {
    unsigned distance[20];
    unsigned source[20];
} adj_list[10];

int print(int nodes) {
    for(int i = 0; i < nodes; i++) {
        cout << endl << endl;
        cout << "For router " << i+1 << ":" << endl;
        for(int j = 0; j < nodes; j++) {
            cout << endl;
            cout << "Node " << j+1 << " via " << adj_list[i].source[j]+1 << " distance " << adj_list[i].distance[j];
        }
    }
    cout << endl;
    //getch();
}

/****************
Bellman Implementation
Input: Cost Matrix, nodes
****************/

int bellman(int cost_matrix[20][20], int nodes) {
    int count = 0;
    cout << "Cost Matrix: " << endl;
    for(int i = 0; i < nodes; i++) {
        for(int j = 0; j < nodes; j++) {
            cost_matrix[i][j] = rand() % 20;
            cost_matrix[i][i] = 0;
            adj_list[i].distance[j] = cost_matrix[i][j]; //initialise the distance equal to cost matrix
            adj_list[i].source[j] = j;
            cout  << cost_matrix[i][j] << " ";
        }
        cout << endl;
    }
    do {
        count = 0;
        for(int i = 0; i < nodes; i++) {
            for(int j = 0; j < nodes; j++) {
                for(int k = 0; k < nodes; k++) {
                    if(adj_list[i].distance[j] > cost_matrix[i][k] + adj_list[k].distance[j]) {//We calculate the minimum distance
                        adj_list[i].distance[j] = adj_list[i].distance[k] + adj_list[k].distance[j];
                        adj_list[i].source[j] = k;
                        count++;
                    }
                }
            }
        }
    } while(count != 0);
    print(nodes);
}

int main() {
    int cost_matrix[20][20];
    int nodes;
    int count = 0;
    //cout << "Enter the number of nodes: ";
    //cin >> nodes;
    nodes = 20;

    bellman(cost_matrix, nodes);
}
