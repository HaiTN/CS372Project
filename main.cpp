#include <limits.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
	int** adjust_matrix;
	size_t size;
	size_t max_size;

	void delete_matrix() {
		for (size_t count = 0; count < this->max_size; ++count) {
			delete[] this->adjust_matrix[count];
		}
		delete[] this->adjust_matrix;
	}

	void resize(size_t newSize) {
		int ** newMatr;
		copy_matrix(this->adjust_matrix, &newMatr, this->size, newSize);
		delete_matrix();
		this->adjust_matrix = newMatr;
	}

	void copy_matrix(int** src, int*** dest, size_t size, size_t max_size) {
		*dest = new int*[this->max_size];
		for (size_t count = 0; count < this->max_size; ++count) {
			*dest[count] = new int[this->max_size];
		}
		for (size_t count = 0; count < this->max_size; ++count)
			for (size_t count2 = 0; count2 < this->max_size; ++count2) {
				if (count < size && count2 < size)
					*dest[count][count2] = src[count][count2];
				else
					*dest[count][count2] = 0;
			}
	}

public:
	Graph(size_t max_size = 20) {
		this->size = 0;
		this->max_size = max_size;
		this->adjust_matrix = new int*[this->max_size];
		for (size_t count = 0; count < this->max_size; ++count) {
			this->adjust_matrix[count] = new int[this->max_size];
			for (size_t count2 = 0; count2 < this->max_size; ++count2) {
				this->adjust_matrix[count][count2] = 0;
			}
		}
	}
	Graph(const Graph& src) {
		this->copy_matrix(src.adjust_matrix, &this->adjust_matrix,src.size, src.max_size);
	}
	~Graph() {
		this->delete_matrix();
	}

	void addNodes(int numOfNodes) {
		if (this->size + 1 >= this->max_size)
		{
			resize(this->max_size * 2);
		}
		this->size += numOfNodes;
	}

	void addEdge(size_t from, size_t to, int weight) {
		if (from < size && to < size)
			this->adjust_matrix[from][to] = weight;
	}

	void removeEdge(size_t from, size_t to) {
		if (from < size && to < size)
			this->adjust_matrix[from][to] = 0;
	}

	int hasEdge(size_t from, size_t to) {
		if (from < size && to < size)
			return this->adjust_matrix[from][to];
		return false;
	}

	void print() {
		cout << setw(3)<< "  ";
		for (size_t count = 0; count < this->size; ++count) {
			cout << setw(3) << count;
		}
		cout << endl;
		cout << endl;
		for (size_t count = 0; count < this->size; ++count) {
			cout << setw(2)<< count << " ";
			for (size_t count2 = 0; count2 < this->size; ++count2) {
				cout << setw(3) << this->adjust_matrix[count][count2];
			}
			cout << endl;
		}
	}

	size_t GetSize() {
		return this->size;
	}

};


template<class T>
class Heap
{
	struct HeapNode {
		HeapNode(){}
		int weight;
		T val;
	};

	HeapNode * nodes;
	size_t size;
	size_t max_size;

	unsigned LeftChildIndex(int index)const {
		return index * 2;
	}
	unsigned RightChildIndex(int index)const {
		return index * 2 + 1;
	}
	unsigned ParentIndex(int index)const {
		if (index > 1)
			return index / 2;
		else
			return 1;
	}

	void Swap(int left, int right) {
		HeapNode tmp;
		tmp = this->nodes[left];
		this->nodes[left] = this->nodes[right];
		this->nodes[right] = tmp;
	}

	bool Resize(size_t newSize) {
		if (newSize < size)
			return false;

		HeapNode* newArr = new HeapNode[newSize + 1];
		if (!newArr) {
			return false;
		}

		for (unsigned i = 1; i <= size; ++i) {
			newArr[i] = this->nodes[i];
		}

		delete[] this->nodes;
		this->nodes = newArr;

		return true;
	}
public:

	Heap() {
		this->size = 0;
		this->max_size = 20;
		this->nodes = new HeapNode[this->max_size + 1];
	}
	~Heap() {
		delete[] this->nodes;
	}
	bool Push(const T& val, int weight) {
		if (this->IsEmpty()) {
			this->nodes[1].val = val;
			this->nodes[1].weight = weight;
			this->size++;
			return true;
		}

		if (size + 1 <= max_size) {
			this->Resize(max_size * 2);
		}

		int iter = size + 1;
		this->nodes[iter].val = val;
		this->nodes[iter].weight = weight;
		this->size++;

		while (iter > 1 && this->nodes[iter].weight < this->nodes[ParentIndex(iter)].weight) {
			this->Swap(iter, ParentIndex(iter));
			iter = ParentIndex(iter);
		}

		return true;
	}

	T Pop() {

		T tmp = this->nodes[1].val;
		this->Swap(1, this->size);
		this->size--;

		int iter = 1;

		while ((this->nodes[iter].weight > this->nodes[LeftChildIndex(iter)].weight && LeftChildIndex(iter) <= size)
			|| (this->nodes[iter].weight > this->nodes[RightChildIndex(iter)].weight && RightChildIndex(iter) <= size))
		{
			if (this->nodes[iter].weight > this->nodes[LeftChildIndex(iter)].weight && LeftChildIndex(iter) <= size
				&& this->nodes[iter].weight > this->nodes[RightChildIndex(iter)].weight && RightChildIndex(iter) <= size)
			{
				if (this->nodes[LeftChildIndex(iter)].weight > this->nodes[RightChildIndex(iter)].weight) {
					this->Swap(iter, RightChildIndex(iter));
					iter = RightChildIndex(iter);
				}
				else {
					this->Swap(iter, LeftChildIndex(iter));
					iter = LeftChildIndex(iter);
				}
			}
			else if (this->nodes[iter].weight > this->nodes[LeftChildIndex(iter)].weight) {
				this->Swap(iter, LeftChildIndex(iter));
				iter = LeftChildIndex(iter);
			}
			else {
				this->Swap(iter, RightChildIndex(iter));
				iter = RightChildIndex(iter);
			}
		}

		if (max_size > 2 * size)
			this->Resize(max_size / 2);
		return tmp;
	}

	bool IsEmpty()const {
		return this->size <= 0;
	}

	size_t GetSize()const {
		return this->size;
	}

	int GetTopWeight() {
		return this->nodes[1].weight;
	}

	void print() {
		for (int i = 1; i <= this->size; ++i) {
			cout << this->nodes[i].val << endl;
		}
	}
};

/*************
Dijkstra Implementation
Input: graph, and initial node
*************/


void dijkstra(Graph& gr, int initial)
{
	size_t size = gr.GetSize();
	int* dist = new int[size];

	Heap<int> heap;
	heap.Push(initial, 0);

	for (size_t count = 0; count < size; ++count) {
		dist[count] = INT_MAX;
	}
	dist[initial] = 0;

	while (!heap.IsEmpty())
	{
		int crnWeight = heap.GetTopWeight();
		int crnElem = heap.Pop();
		for (int count = 0; count < size; ++count) {
			if (gr.hasEdge(crnElem, count)) {
				if (dist[count] > crnWeight + gr.hasEdge(crnElem, count)) {
					dist[count] = crnWeight + gr.hasEdge(crnElem, count);
					heap.Push(count, dist[count]);
				}
			}
		}
	}

	//print result
	for (int i = 0; i < size; ++i) {
        if(dist[i] == 2147483647)
            cout << "From node[" << initial << "] to [" << i << "]:" << "NO PATH FOUND" << endl;
        else
            cout << "From node[" << initial << "] to [" << i << "]:" << dist[i] << endl;
	}
	delete[] dist;
}

void inputGraph(Graph& gr)
{
	int node;
	int destination;
	int n, weight;
	//cout << "Number of Nodes(Maximum 20):";
	//cin >> n;
	n = 20;
	gr.addNodes(n);
	//cout << "Number of edges:";
	//cin >> n;
	n = 1000000; //set to the amount of edges
	while (n > 0)
    {
		node = rand() % n;
		destination = rand() % n;
		weight = rand() % 100;

       // cout << "Node: " << from
         //   << "    -----     Destination: " << to
           // << "    -----     Weight: " << weight << endl;

		gr.addEdge(node, destination, weight);
		--n;
	}
}

int main()
{
    clock_t t;
    t = clock();
	Graph graph;
	inputGraph(graph);
	graph.print();

	int n = 0;
	//cout << "initial node:" << endl;
	//cin >> n;

	dijkstra(graph, n);
	//cout << ((float)t/CLOCKS_PER_SEC) << " seconds." << endl;

	return 0;
}
