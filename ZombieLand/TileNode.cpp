#include "TileNode.h"


TileNode::TileNode()
{
}

TileNode::TileNode(int x, int y) {
	this->x = x;
	this->y = y;
}

void TileNode::setParent(TileNode *parent) {
	g = parent->g + 1;
	this->parent = parent;
}

TileNode::~TileNode()
{
}
