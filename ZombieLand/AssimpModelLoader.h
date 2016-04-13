#pragma once
#include "CollisionPlane.h"
#include <algorithm>
#include <vector>
#include <GL/glut.h>

using namespace std;
class AssimpModelLoader
{
public:
	AssimpModelLoader();
	void loadObjFile(const char *filename);
	void Draw();
protected:

private:
	GLuint displaylist;
};

