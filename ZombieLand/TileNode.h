#pragma once
class TileNode
{
	

public:
	int x;
	int y;
	TileNode *parent = nullptr;
	float h;
	float g;
	float f;
	char status = 'U';

	TileNode(int x, int y);
	void setParent(TileNode *parent);
	TileNode();
	~TileNode();
};

