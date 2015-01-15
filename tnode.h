#ifndef TNODE_H
#define TNODE_H

class tnode {
	private:
		int rank;
		int name;
		tnode * find_label();
		void join(tnode * node);

		tnode();
	public:
		tnode(int name);
		~tnode();
};

#endif
