#include "tnode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class edge {
	public:
		int end1;
		int end2;
		int weight;
		edge(int end1, int end2, int weight) {
			this->end1 = end1;
			this->end2 = end2;
			this->weight = weight;
		}
};

bool operator<(const edge & l, const edge & r) {
	return l.weight < r.weight;
}

bool edgePtrCompare(const edge *l, const edge *r) {
	return *l < *r;
}

int main(int argc, const char * argv[]) {
	int n_nodes, n_edges;

	if( argc < 2 ) {
		std::cout << "Must include path to graph data" << std::endl;
		return 1;
	}
	std::fstream fin;
	fin.open(argv[1], std::fstream::in);
	
	// Read in number of nodes and edges
	fin >> n_nodes >> n_edges;

	// Allocate memory
	tnode *nodes = new tnode[n_nodes];
	std::vector<edge *> edges = std::vector<edge *>();

	// Initialize nodes
	for( int i = 0; i < n_nodes; i++ ) nodes[i].init(i);

	// Read in edge data
	int end1_t, end2_t, weight_t;
	for( int i = 0; i < n_edges; i++ ) {
		fin >> end1_t >> end2_t >> weight_t;
		edges.push_back(new edge(end1_t, end2_t, weight_t));	
	}
	fin.close();

	// Sort edges by weight
	std::sort(edges.begin(), edges.end(), edgePtrCompare);

/* Some debug prints
	for( int i = 0; i < n_edges; i++ ) {
		std::cout << edges[i]->end1 << " "  << edges[i]->end2 << " " << edges[i]->weight << std::endl;
	}

	tnode * node0 = new tnode(0);
        tnode * node1 = new tnode(1);
        std::cout << node0->find_label() << std::endl;
        std::cout << node1->find_label() << std::endl;
        node0->join(node1);
        std::cout << node0->find_label() << std::endl;
        std::cout << node1->find_label() << std::endl;
	delete node0;
        delete node1;
*/

	// Free nodes and edges
	delete [] nodes;
	for( int i = 0; i < n_edges; i++ ) {
		delete edges[i];
	}
}
