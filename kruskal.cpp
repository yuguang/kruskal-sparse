# include "tnode.h"
#include <iostream>

int main(int argc, const char * argv[]) {
	tnode * node = new tnode(0);
	delete node;

	std::cout << "Hello world" << std::endl;
}
