#include "tnode.h"
#include <iostream>

int main(int argc, const char * argv[]) {
	tnode * node0 = new tnode(0);
        tnode * node1 = new tnode(1);
        std::cout << node0->find_label() << std::endl;
        std::cout << node1->find_label() << std::endl;
        node0->join(node1);
        std::cout << node0->find_label() << std::endl;
        std::cout << node1->find_label() << std::endl;
	delete node0;
        delete node1;

	std::cout << "Hello world" << std::endl;
}
