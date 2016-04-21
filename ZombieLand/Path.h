#pragma once
#include<stack>
class Path
{
	struct Step {
		int x;
		int y;

		Step(int x, int y) {
			this->x = x;
			this->y = y;
		}

		int getX() { return x; }
		int getY() { return y; }
	};

public:
	std::stack<Step> correctPath;
	Path();
	~Path();
	void addStep(int x, int y);
};

