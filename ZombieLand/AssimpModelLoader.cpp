#include "AssimpModelLoader.h"
#include <iostream>
#include <string>
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "CollisionPlane.h"
#include <assimp/postprocess.h>
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
#include "Vector.h"
#include <assert.h>

using namespace std;

AssimpModelLoader::AssimpModelLoader() {}

AssimpModelLoader::~AssimpModelLoader()
{
}

void AssimpModelLoader::loadObjFile(const char *filename)
{

	// Load the model and create a display list for it.
	std::cout << "loading " << filename << std::endl;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);

	GLuint displaylist = glGenLists(1);
	glNewList(displaylist, GL_COMPILE);

	int matNum = 0;

	for (int meshnum = 0; meshnum < scene->mNumMeshes; meshnum++) {
		aiMesh *mesh = scene->mMeshes[meshnum];

		aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];

		aiString name;
		mtl->Get(AI_MATKEY_NAME, name);
		//std::cout << name.data << "\n";

		aiColor4D diffuse;

		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		{

			float diffusal[] = { diffuse.r,diffuse.g,diffuse.b,diffuse.a };
			//std::cout << diffusal[0] << " " << diffusal[1] << " " << diffusal[2] << "\n";
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffusal);
		}

		aiColor4D specular;
		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		{

			float specularity[] = { specular.r,specular.g,specular.b,specular.a };
			//std::cout << specularity[0] << " " << specularity[1] << " " << specularity[2] << "\n";
			glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
		}

		aiColor4D ambient;
		if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		{
			float ambiention[] = { ambient.r,ambient.g,ambient.b,ambient.a };
			//std::cout << ambiention[0] << " " << ambiention[1] << " " << ambiention[2] << "\n";
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambiention);
		}

		GLuint texture = 0;
		aiString path;
		bool hasTexture = false;
		//std::cout << meshnum << "mesh number\n";

		int texIndex = 0;
		// filename

		aiReturn texFound = scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);

		if (texFound == AI_SUCCESS)
		{
			glEnable(GL_TEXTURE_2D);
			SDL_Surface*  surface = IMG_Load((path.data));
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
			
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
			SDL_FreeSurface(surface);
			glDisable(GL_TEXTURE_2D);
		}


		for (int facenum = 0; facenum < mesh->mNumFaces; facenum++) {
			aiFace *face = &mesh->mFaces[facenum];


			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_TRIANGLES);

			for (int v = 0; v < face->mNumIndices; v++) {
				int vertex = face->mIndices[v];


				glNormal3f(mesh->mNormals[vertex].x,
					mesh->mNormals[vertex].y,
					mesh->mNormals[vertex].z);


				glTexCoord2f(mesh->mTextureCoords[0][vertex].x, mesh->mTextureCoords[0][vertex].y);


				glVertex3f(mesh->mVertices[vertex].x,
					mesh->mVertices[vertex].y,
					mesh->mVertices[vertex].z);
				/*cout << mesh->mVertices[vertex].x << 
					mesh->mVertices[vertex].y << 
					mesh->mVertices[vertex].z << endl;*/

			
			}
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
	}
	glEndList();
}

void AssimpModelLoader::Draw(int id) {
	glCallList(id);
}
