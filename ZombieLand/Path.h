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
	};

public:
	std::stack<Step> correctPath;
	Path();
	~Path();
	void addStep(int x, int y);
	
		
};

