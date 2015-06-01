#include <iostream>

using namespace std;

struct Edge {
    int node;
    int location;
    int weight;
};

struct Graph {
    int vertice;
    int edge;

    struct Edge* edge;
};

struct Graph* generateGraph(int vertice, int edge) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->vertice = vertice;
    graph->edge = edge;

    graph->edge = (struct Edge*) malloc(graph->edge * sizeof(struct Edge));

    return graph;
};

int main() {

    return 0;
}
