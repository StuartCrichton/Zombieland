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
	~AssimpModelLoader();
	void loadObjFile(const char *filename);
	void Draw(int id);
protected:

private:
	GLuint displaylist;
};

