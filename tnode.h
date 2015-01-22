#ifndef TNODE_H
#define TNODE_H

class tnode {
	private:
		int rank;
		int name;
                tnode * parent;
                tnode * find();

	public:
		tnode();
		void init(int name);
		~tnode();
                int find_label();
                void join(tnode * node);
};

#endif
