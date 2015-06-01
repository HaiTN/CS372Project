#include <iostream>

using namespace std;

struct Edge {
    int node;
    int location;
    int weight;
};

struct Graph {
    int v;
    int e;

    struct Edge* edge;
};

struct Graph* generateGraph(int vertice, int edge) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->v = vertice;
    graph->e = edge;

    graph->edge = (struct Edge*) malloc(graph->e * sizeof(struct Edge));

    return graph;
};

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

    return 0;
}
