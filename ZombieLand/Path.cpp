#include "Path.h"



Path::Path()
{
}

void Path::addStep(int x, int y) {
	correctPath.push(Step(x, y));
}

Path::~Path()
{
}
