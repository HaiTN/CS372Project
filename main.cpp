#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge {
    int node;
    int location;
    int weight;
    int distance;
    Edge *next;
    Edge *prev;
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

int pop(Edge *head) {
    int location, weight, distance, node;
    Edge *temp;

    while(head->next != NULL)
        head = head->next;

    node = head->node;
    location = head->location;
    weight = head->weight;
    distance = head->distance;

    temp = new Edge;
    delete temp;
    return node, location, weight, distance;
}

int numNeighbors(Edge *head) {
    int num_neighbors;
    Edge *tempnext;
    Edge *tempprev;

    tempnext = head->next;
    tempprev = head->prev;

    if(tempnext->node == head->location)
        num_neighbors++;
    if(tempprev->node == head->location)
        num_neighbors++;

    return num_neighbors;
}

int dijkstraAlg(struct Graph* graph, int destination, int node, int vertex, int edge) {
    graph->edge->distance = 0;
    graph->edge->prev = NULL;

    cout << "Before Search 1" << endl;

    struct Graph* visited = generateGraph(vertex, edge);
    struct Graph* sequence;

    cout << "Before Search 2" << endl;
    for(int i = 0; i < vertex; i++) {
        if(graph->edge[i].node != graph->edge[node].node) {
            cout << "Searching step " << i << "..." << endl;
            graph->edge[i].distance = 99999999;
            graph->edge[i].prev = NULL;
        }

        cout << "Out of if statement " << i << "..." << endl;
        visited->edge[i].node = graph->edge[i].node;
        cout << "Already visited: " << visited->edge[i].node << endl;
        cout << "After visited" << endl;
    }

    cout << "End Search 2" << endl;

    while(graph->edge->prev != NULL) {
        graph->edge[0].node = destination;
        pop(graph->edge);

        for(int i = 0; i < numNeighbors(&graph->edge[i]); i++) {
            int alt = graph->edge[0].distance + graph->edge[i].weight;
            if(alt < graph->edge[i].distance) {
                graph->edge[i].distance = alt;
            }
        }
    }

    return graph->edge->distance;
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

    dijkstraAlg(graph, 10, 0, v, e);

    return 0;
}
