#pragma once
class TileNode
{
	

public:
	int x;
	int y;
	TileNode *parent;
	int h;
	int g;
	int f;
	char status = 'U';

	TileNode(int x, int y);
	void setParent(TileNode *parent);
	TileNode();
	~TileNode();
};

