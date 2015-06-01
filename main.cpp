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

    return 0;
}
