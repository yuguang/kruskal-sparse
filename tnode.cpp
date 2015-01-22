#include "tnode.h"

tnode::tnode(int name) {
  this->rank = 0;
  this->name = name;
  this->parent = this;
}

tnode::~tnode() {
}

void tnode::join(tnode * node) {
  if (rank > node->rank) {
    node->parent = this;
  } else {
    parent = node;
  }
  if (this->rank == node->rank) {
    node->rank++;
  }
}

tnode * tnode::find() {
//TODO: test with and without path compression to see which is faster
  if (parent == this) {
    return this;
  }
  parent = parent->find(); // this should do the path compression
  return parent;
}

int tnode::find_label() {
  return this->find()->name;
}
