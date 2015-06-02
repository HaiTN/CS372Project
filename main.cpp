#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>

using namespace std;

struct Node {
    int index;
    unsigned int distance;
};

struct Edge {
    int node;
    int location;
    int weight;
    int distance;
    int prev;
};

struct Graph {
    int v;
    int e;

    struct Edge* edge;
};

struct Graph* generateGraph(int vertex, int edge) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->v = vertex;
    graph->e = edge;

    graph->edge = (struct Edge*) malloc(graph->e * sizeof(struct Edge));

    return graph;
};

int dijkstraAlg(struct Graph* graph, int destination, int node, int vertex) {
    graph->edge->distance = 0;
    graph->edge->prev = NULL;

    cout << "Before Search 1" << endl;

    struct Graph* visited;
    struct Graph* sequence;

    cout << "Before Search 2" << endl;
    for(int i = 0; i < vertex; i++) {
        if(graph->edge[i].node != graph->edge[node].node) {
            cout << "Searching step " << i << "..." << endl;
            graph->edge[i].distance = 99999999;
            graph->edge[i].prev = NULL;
        }

        cout << "Out of if statement " << i << "..." << endl;
        graph->edge[i].node = visited->edge[i].node;
        cout << "After visited" << endl;

    }

    cout << "End Search" << endl;

    while(graph->edge->prev != NULL) {
        graph->edge[0].node = destination;
        destination = graph->edge[destination].node;
    }


}

int main() {
    int v, e;
    struct Graph* graph = generateGraph(v, e);

    cout << "Insert amount of vertices: ";
    cin >> v;
    cout << "Insert amount of edges: ";
    cin >> e;

    cout << "Edges: " << e << " Vertices: " << v << endl;
    cout << "Generating graph..." << endl;

    for(int x = 0; x < e; x++) {
        graph->edge[x].node = rand() % v;
        graph->edge[x].location = rand() % v;
        graph->edge[x].weight = rand() % 100;

        cout << "Node: " << graph->edge[x].node
            << "    -----     Destination: " << graph->edge[x].location
            << "    -----     Weight: " << graph->edge[x].weight << endl;
    }

    dijkstraAlg(graph, 10, 0, v);

    return 0;
}
