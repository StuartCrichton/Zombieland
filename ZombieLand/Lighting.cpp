#include "Lighting.h"
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <GL/glut.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;



void Lighting::lightInitGL()
{

	glEnable(GL_FLAT);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_NORMAL_ARRAY);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT0);//corner1
	glEnable(GL_LIGHT1);//middle
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);


	GLfloat diffuseSun[] = { 0.3, 0.3, 0.3, 0.6 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseSun);

	GLfloat ambientSun[] = { 0.5, 0.5, 0.5, 0.4 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientSun);

	GLfloat specularSun[] = { 0.5, 0.5, 0.5, 0.2 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularSun);

	GLfloat posSun[] = { light_X, 100, light_Z, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posSun);


	GLfloat sunCutoff[] = { 360 };
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, sunCutoff);


	update();


	GLfloat light_position1[] = { 55, 10, -75, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);




	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 0.5 };
	GLfloat specular[] = { 0.3, 0.3, 0.3, 0.2 };


	GLfloat spot_direction[] = { 15, -50, 40, 0 };
	GLfloat spot_exponent[] = { 150.0f };
	GLfloat spot_cutoff[] = { 70.0 };



	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.2);


	GLfloat ambientColor[] = { 0.4f, 0.4f, 0.4f, 0.3f }; //Color (0.2, 0.2, 0.2)
	GLfloat ambientDiff[] = { 0.7f, 0.7f, 0.7f, 0.3f };
	
	GLfloat ambC[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, ambC);
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambC);

	GLfloat ambientPos[] = { 0.0f, 0.0f, -40.0f, 1.0f };
	glLightfv(GL_LIGHT3, GL_POSITION, ambientPos);

	///////////////////////////////////////////////////////

	glLightfv(GL_LIGHT4, GL_DIFFUSE, ambientDiff);
	glLightfv(GL_LIGHT4, GL_AMBIENT, ambientColor);

	GLfloat ambientPos2[] = { 60.0f, 0.0f, -40.0f, 1.0f };
	glLightfv(GL_LIGHT4, GL_POSITION, ambientPos2);

	///////////////////////////////////////////////////////
	glLightfv(GL_LIGHT5, GL_DIFFUSE, ambientDiff);
	glLightfv(GL_LIGHT5, GL_AMBIENT, ambientColor);

	GLfloat ambientPos3[] = { 30.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT5, GL_POSITION, ambientPos3);

	///////////////////////////////////////////////////////
	GLfloat ambientColor2[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat ambientDiff2[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	glLightfv(GL_LIGHT6, GL_DIFFUSE, ambientDiff2);
	glLightfv(GL_LIGHT6, GL_AMBIENT, ambientColor2);

	GLfloat ambientPos4[] = { 30.0f, 0.0f, -80.0f, 1.0f };
	glLightfv(GL_LIGHT6, GL_POSITION, ambientPos4);

	//////////////////////////////////////////////////////
	glLightfv(GL_LIGHT7, GL_DIFFUSE, ambientDiff2);
	glLightfv(GL_LIGHT7, GL_AMBIENT, ambientColor2);

	GLfloat ambientPos5[] = { 30.0f, -20.0f, -40.0f, 0.0f };
	glLightfv(GL_LIGHT7, GL_POSITION, ambientPos5);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);


	glEnable(GL_LIGHTING);

}

void Lighting::update()
{
	GLfloat time_New = glutGet(GLUT_ELAPSED_TIME);
	GLfloat diff = time_New - time_Prev;
	time_Prev = time_New;
	diff = diff / 100;
	GLfloat steps = diff;
	this->angle += steps;

	GLfloat radius = sqrt((40 * 40) + (20 * 20));

	light_X = 150 * cos(angle*M_PI / 180);
	light_Z = -150 * sin(angle*M_PI / 180);

}

Lighting::Lighting()
{
	this->light_X = light_X;
	this->light_Y = light_Y;
	this->light_Z = light_Z;
}

Lighting::~Lighting()
{
}
