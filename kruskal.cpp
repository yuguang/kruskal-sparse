#include "tnode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "util.h"

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
	double start = CO759_zeit(), done_read, done_tree, done_free, done_sort;

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

	done_read = CO759_zeit();

	// Sort edges by weight
	std::sort(edges.begin(), edges.end(), edgePtrCompare);
	done_sort = CO759_zeit();

	std::vector<edge *> tree = std::vector<edge *>();
	unsigned long long tree_cost = 0;
	
	for( int i = 0; i < n_edges; i++ ) {
		if( nodes[edges[i]->end1].find_label() != nodes[edges[i]->end2].find_label() ) {
			tree.push_back(edges[i]);
			tree_cost += edges[i]->weight;
			nodes[edges[i]->end1].join(&(nodes[edges[i]->end2]));
		}	
		if( tree.size() == n_nodes-1 ) {
			break;
		}
	}

	done_tree = CO759_zeit();

/* Print edges in tree
	for( int i = 0; i < n_nodes-1; i++ ) {
		std::cout << tree[i]->end1 << " " << tree[i]->end2 << std::endl;
	}
*/

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
	done_free = CO759_zeit();

	std::cout << "Tree cost: " << tree_cost << std::endl;
	std::cout << "Read Input: " << done_read - start << "s" << std::endl;
	std::cout << "Sort Edges: " << done_sort - done_read << "s" << std::endl;
	std::cout << "Build Tree: " << done_tree - done_sort << "s" << std::endl;
	std::cout << "Free memory: " << done_free - done_tree << "s" << std::endl;

}
