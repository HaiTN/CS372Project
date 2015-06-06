/*
distanceance Vector Routing in this program is implemented using Bellman Ford Algorithm:-
*/
#include <iostream>
#include <stdio.h>

using namespace std;

struct Node
{
    unsigned distance[20];
    unsigned source[20];
}

adj_list[10];

int main() {
    int cost_matrix[20][20];
    int nodes;
    int count = 0;
    //cout << "Enter the number of nodes: ";
    //cin >> nodes;
    nodes = 20;

    //cout << "Enter the cost matrix: " << endl;
    cout << "Cost Matrix: " << endl;
    for(int i = 0; i < nodes; i++) {
        for(int j = 0; j < nodes; j++) {
            //scanf("%d",&cost_matrix[i][j]);
            //cin >> cost_matrix[i][j];
            cost_matrix[i][j] = rand() % 100;
            cost_matrix[i][i] = 0;
            adj_list[i].distance[j] = cost_matrix[i][j]; //initialise the distance equal to cost matrix
            adj_list[i].source[j] = j;
            cout  << cost_matrix[i][j] << " ";
        }
        cout << endl;
    }
        do {
            count = 0;
            //We choose arbitary vertex k and we calculate the direct distanceance source the node i to k using the cost matrix
            //and add the distanceance from k to node j
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

        for(int i = 0; i < nodes; i++)
        {
            //printf("\n\n For router %d\n",i+1);
            cout << endl << endl;
            cout << "For router " << i+1 << ":" << endl;
            for(int j = 0; j < nodes; j++)
            {
                //printf("\t\nnode %d via %d distance %d ",j+1,adj_list[i].source[j]+1,adj_list[i].distance[j]);
                cout << endl;
                cout << "Node [" << j+1 << "] from [" << adj_list[i].source[j]+1 << "] distance " << adj_list[i].distance[j];
            }
        }
    cout << endl;
    //getch();
}
/*
A sample run of the program works as:-
Enter the number of nodes :
3
Enter the cost matrix :
0 2 7
2 0 1
7 1 0
For router 1
node 1 via 1 distanceance 0
node 2 via 2 distanceance 2
node 3 via 3 distanceance 3
For router 2
node 1 via 1 distanceance 2
node 2 via 2 distanceance 0
node 3 via 3 distanceance 1
For router 3
node 1 via 1 distanceance 3
node 2 via 2 distanceance 1
node 3 via 3 distanceance 0
*/
