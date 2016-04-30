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
	//glEnable(GL_LIGHT2);//corner2
	//glEnable(GL_LIGHT3);//below


	GLfloat diffuseSun[] = { 0.3, 0.3, 0.3, 1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseSun);

	GLfloat ambientSun[] = { 0.5, 0.5, 0.5, 0.4 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientSun);

	GLfloat specularSun[] = { 0.5, 0.5, 0.5, 0.2 };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularSun);

	GLfloat posSun[] = { light_X, 100, light_Z, 0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posSun);

	//GLfloat sunDirection[] = { 30.0, 5.0, -40.0 };
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, sunDirection);

	GLfloat sunCutoff[] = { 360 };
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, sunCutoff);

	//GLfloat sunConstAtten[] = { 1 };
	//glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, sunConstAtten);

	//GLfloat sunExponent[] = { 100.0f };
	//glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, sunExponent);

	update();

	//int dimx = 60;
	//int dimz = 80;
	//GLfloat light_position1[] = { 0, 15, 0, 1 };
	GLfloat light_position1[] = { 55, 10, -75, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);


	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING); // turns on the lighting model in OpenGL

	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 0.8 };
	GLfloat specular[] = { 0.3, 0.3, 0.3, 0.2 };
	//GLfloat ambient0[] = { 0.3,0.3,0.3,0.3 };
	//GLfloat ambient[] = { 0.5, 0.5, 0.5, 0.5 };

	GLfloat spot_direction[] = { 15, -50, 40, 0 };
	GLfloat spot_exponent[] = { 150.0f };
	GLfloat spot_cutoff[] = { 70.0 };



	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.2);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);


	GLfloat ambientColor[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


	//GLfloat mat_amb[] = { 0.2,0.2,0.2,0.2 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);


}

void Lighting::update()
{
	GLfloat time_New = glutGet(GLUT_ELAPSED_TIME);
	GLfloat diff = time_New - time_Prev;
	time_Prev = time_New;
	diff = diff / 1000;
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
