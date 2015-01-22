#include "tnode.h"

tnode::tnode() {
}

void tnode::init(int name) {
  this->rank = 0;
  this->name = name;
  this->parent = this;
}

tnode::~tnode() {
}

void tnode::join(tnode * node) {
  tnode *this_p = this->find(), *node_p = node->find();
  if (this_p->rank > node_p->rank) {
    node_p->parent = this;
  } else {
    this_p->parent = node_p;
  }
  if (this_p->rank == node_p->rank) {
    node_p->rank++;
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
