#include "Zombie.h"
#include <GL/glut.h>
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32
#include <ctime>
#include <cstdlib>
#include "Vector.h"
#include <math.h>
#include <iostream>
using namespace std;

void Zombie::drawZombie() {
	glPushMatrix();

	GLfloat white[] = { 1.0f,1.0f,1.0f, 1.0f };
	GLfloat black[] = { 0.0f,0.0f,0.0f, 1.0f };
	GLfloat red[] = { 1.0f,0.0f,0.0f, 1.0f };
	GLfloat green[] = { 0.0f,1.0f,0.0f, 1.0f };
	GLfloat blue[] = { 0.0f,0.0f,1.0f, 1.0f };
	GLfloat navyblue[] = { 0.0f,0.0f,0.3f, 1.0f };
	GLfloat pink[] = { 1.0f,0.0f,1.0f, 1.0f };
	GLfloat yellow[] = { 1.0f,1.0f,0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);

	/// Shininess levels:
	GLfloat mat_shininess1[] = { 20.0 };
	GLfloat mat_shininess2[] = { 60.0 };
	GLfloat mat_shininess3[] = { 70.0 };
	GLfloat mat_shininess4[] = { 0.0 };
	GLfloat mat_shininess5[] = { 90.0 };
	GLfloat mat_shininess6[] = { 100.0 };
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess4);
	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glRotatef(-thetha * 180 / M_PI, 0, 1, 0);
	glPushMatrix();

	/// Draw Torso
	glTranslatef(0.0, 0.36, 0.0);
	glScalef(1.0, 1.15, 0.45);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Shirt Pocket
	glPushMatrix();
	//glColor3f(0.842, 0.842, 0.842);
	GLfloat color2[] = { 0.842f, 0.842f, 0.842f, 1.0f };
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess6);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color2);
	glTranslatef(-0.13, 0.45, -0.11);
	glScalef(0.25, 0.28, 0.05);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Pen
	// (1) Body
	glPushMatrix();
	//glColor3f(0.0, 0.0, 1.0);
	GLfloat color3[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color3);
	glTranslatef(-0.15, 0.56, -0.1125);
	glRotatef(90, 1.0, 0.0, 0.0);
	GLUquadric* quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	//gluQuadricDrawStyle( quadratic, GLU_FILL);
	gluQuadricTexture(quadratic, GL_TRUE); // Tried both GL_TRUE and GL_FALSE
	gluCylinder(quadratic, 0.008, 0.008, 0.18, 12, 1);
	glPopMatrix();

	// (2) Top Of Lid
	glPushMatrix();
	//glColor3f(0.0, 0.0, 1.0);
	glTranslatef(-0.15, 0.56, -0.1125);
	glutSolidSphere(0.008, 10, 10);
	glPopMatrix();

	// (3) Clip
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0.5);
	GLfloat color4[] = { 0.015f, 0.015f, 0.015f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color4);
	glTranslatef(-0.15, 0.51, -0.12);
	glScalef(0.009, 0.122, 0.02);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Name Badge
	// (1) Clip
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0.5);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color4);
	glTranslatef(0.125, 0.49, -0.12);
	glScalef(0.025, 0.05, 0.02);
	glutSolidCube(0.5);
	glPopMatrix();

	// (2) Card
	glPushMatrix();
	//glColor3f(1.0, 1.0, 1.0);
	GLfloat color5[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color5);
	glTranslatef(0.125, 0.45, -0.11);
	glScalef(0.27, 0.16, 0.05);
	glutSolidCube(0.5);
	glPopMatrix();

	// (3) Photo
	glPushMatrix();
	//glColor3f(0.5, 0.62, 0.7); // Perfect colour
	GLfloat color6[] = { 0.05f, 0.062f, 0.07f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color6);
	glTranslatef(0.162, 0.4585, -0.111);
	glScalef(0.09, 0.09, 0.05);
	glutSolidCube(0.5);
	glPopMatrix();

	// (4) Writing
	glPushMatrix();
	//glColor3f(0.35, 0.35, 0.35);
	GLfloat color7[] = { 0.026f, 0.026f, 0.026f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color7);
	glTranslatef(0.12, 0.468, -0.12);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.015, 0.02, 0.02);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0.35, 0.35, 0.35);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color7);
	glTranslatef(0.09, 0.468, -0.12);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.015, 0.05, 0.02);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0.45, 0.45, 0.45);
	GLfloat color8[] = { 0.45f, 0.45f, 0.54f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color8);
	glTranslatef(0.096, 0.451, -0.12);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.005, 0.12, 0.02);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0.45, 0.45, 0.45);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color8);
	glTranslatef(0.096, 0.444, -0.12);
	glRotatef(90, 0.0, 0.0, 1.0);
	glScalef(0.005, 0.12, 0.02);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Left Upper Arm
	glPushMatrix();
	//glColor3f(0.8, 0.8, 0.8);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glTranslatef(-0.35, 0.45, -0.125);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(20, 0.0, 0.0, -1.0);
	glRotatef(8, 0.0, 1.0, 0.0);
	glRotatef(25, -1.0, 0.0, 0.0);
	glScalef(0.31, 0.8, 0.31);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Right Upper Arm
	glPushMatrix();
	//glColor3f(0.8, 0.8, 0.8);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glTranslatef(0.35, 0.45, -0.125);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
	glRotatef(8, 0.0, -1.0, 0.0);
	glRotatef(25, -1.0, 0.0, 0.0);
	glScalef(0.31, 0.8, 0.31);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Left Forearm
	glPushMatrix();

	//glColor3f(0.0, 0.12, 0.0);
	GLfloat color9[] = { 0.0f, 0.12f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color9);
	glTranslatef(-0.37, 0.38, -0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(5, 0.0, 0.0, 1.0);
	glRotatef(18, 0.0, 1.0, 0.0);
	glScalef(0.27, 1.0, 0.27);
	glutSolidCube(0.5);
	//gluQuadricNormals(quadratic, GLU_SMOOTH);
	//gluQuadricDrawStyle( quadratic, GLU_FILL);
	//gluQuadricTexture(quadratic, GL_TRUE); // Tried both GL_TRUE and GL_FALSE
	//glRotatef(90, 1.0, 0.0, 0.0);
	//gluCylinder(quadratic, 0.27, 0.27, 0.5, 20, 1);

	glPopMatrix();

	/// Draw Left Hand
	//glPushMatrix();
	//GLfloat color20[] = {0.0f, 0.44f, 0.0f, 1.0f};
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color20);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
	//glTranslatef(-0.336275, 0.40001, -0.7);
	//glutSolidSphere(0.07305, 20, 12);
	//glPopMatrix();

	/// Draw Right Forearm
	glPushMatrix();
	//glColor3f(0.0, 0.12, 0.0);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color9);
	glTranslatef(0.37, 0.38, -0.5);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(5, 0.0, 0.0, -1.0);
	glRotatef(18, 0.0, -1.0, 0.0);
	glScalef(0.27, 1.0, 0.27);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Left Sleeve Roll
	glPushMatrix();
	//glColor3f(0.835, 0.835, 0.835);
	GLfloat color10[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color10);
	glTranslatef(-0.39, 0.39, -0.28);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(16.8, 0.0, 0.0, -1.0);
	glRotatef(14, 0.0, 1.0, 0.0);
	glRotatef(5, 0.0, 0.0, 1.0);
	glRotatef(12, -1.0, 0.0, 0.0);
	glScalef(0.38, 0.2, 0.38);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Right Sleeve Roll
	glPushMatrix();
	//glColor3f(0.835, 0.835, 0.835);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color10);
	glTranslatef(0.39, 0.39, -0.28);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(16.8, 0.0, 0.0, 1.0);
	glRotatef(14, 0.0, -1.0, 0.0);
	glRotatef(5, 0.0, 0.0, -1.0);
	glRotatef(12, -1.0, 0.0, 0.0);
	glScalef(0.38, 0.2, 0.38);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Tie
	// (1) Top Piece
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	GLfloat color11[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(0.0, 0.6465, -0.123);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.02, 0.07, 0.07);
	glutSolidCone(0.7, 1.2, 3, 0);
	glPopMatrix();

	// (2) Middle Piece
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(0.0, 0.25, -0.114);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(0.03, 0.07, 0.07);
	glutSolidCone(1.0, 5.7, 3, 0);
	glPopMatrix();

	// (3) Bottom Piece
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(0.0, 0.25, -0.114);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glScalef(0.03, 0.07, 0.07);
	glutSolidCone(1.0, 1.0, 3, 0);
	glPopMatrix();

	/// Draw Waist
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(0.0, -0.05215, 0.0);
	glScalef(1.0, 0.5, 0.45);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Belt
	// Buckle
	glPushMatrix();
	//glColor3f(0.32, 0.32, 0.32);
	GLfloat color12[] = { 0.32f, 0.32f, 0.32f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color12);
	glTranslatef(0.0, 0.03, -0.11);
	glScalef(0.2, 0.1, 0.05);
	glutSolidCube(0.5);
	glPopMatrix();

	// Gap
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(0.0, 0.03, -0.11005);
	glScalef(0.15, 0.075, 0.05);
	glutSolidCube(0.5);
	glPopMatrix();

	// Pin
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0.5);
	GLfloat color13[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color13);
	glTranslatef(-0.012, 0.03, -0.1101);
	glScalef(0.13, 0.02, 0.05);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Left Leg
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(-0.155, -0.51, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.39, 1.6, 0.38);
	glutSolidCube(0.5);
	glPopMatrix();

	/// Draw Right Leg
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.155, -0.51, 0.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(0.39, 1.6, 0.38);
	glutSolidCube(0.5);
	glPopMatrix();


	/// Draw Head
	//glColor3f(0.0, 0.12, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color9);
	glTranslatef(0.0, 0.95, 0.0);
	glutSolidCube(0.40);

	/// Draw Neck
	glPushMatrix();
	glTranslatef(0.0, -0.25, 0.0);
	glScalef(1.6, 2.0, 1.6);
	glutSolidCube(0.1);
	glPopMatrix();

	/// Draw Eyes
	// Left Iris
	glPushMatrix();
	//glColor3f(0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color11);
	glTranslatef(0.1, 0.1, -0.2);
	glutSolidSphere(0.05, 10, 10);
	//Right Iris
	glTranslatef(-0.2, 0.0, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();

	// Left Pupil
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	GLfloat color14[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color14);
	glTranslatef(0.1, 0.1, -0.211);
	glutSolidSphere(0.04, 10, 10);

	// Right Pupil
	glTranslatef(-0.2, 0.0, 0.0);
	glutSolidSphere(0.04, 10, 10);
	glPopMatrix();

	/// Draw Eyebrows
	// Left
	glPushMatrix();
	glTranslatef(0.085, 0.13, -0.2);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotated(30, 0.0, 0.0, -1.0);
	glScalef(2.2, 0.27, 1.5);
	//glColor3f(0.0, 0.065, 0.0);
	GLfloat color15[] = { 0.0f, 0.065f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color15);
	glutSolidCube(0.06);
	glPopMatrix();

	// Right
	glPushMatrix();
	glTranslatef(-0.085, 0.13, -0.2);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotated(30, 0.0, 0.0, 1.0);
	glScalef(2.2, 0.27, 1.5);
	//glColor3f(0.0, 0.065, 0.0);
	glutSolidCube(0.06);
	glPopMatrix();

	/// Draw Mouth
	glPushMatrix();
	glTranslatef(0.0, -0.08, -0.182);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(3, 1, 1);
	//glColor3f(0.04, 0.0, 0.0);
	GLfloat color16[] = { 0.04f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color16);
	glutSolidCube(0.06);
	glPopMatrix();

	/// Draw Teeth
	// Top Far Left
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	GLfloat color17[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color17);
	glTranslatef(-0.06, -0.0575, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Top Far Right
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.06, -0.0575, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Top Middle Left
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.03, -0.0575, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Top Middle Right
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.03, -0.0575, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	//Top Middle
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.0575, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Bottom Far Left
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.06, -0.1025, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	//glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Bottom Far Right
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.06, -0.1025, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	//glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Bottom Middle Left
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.03, -0.1025, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	//glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	// Bottom Middle Right
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.03, -0.1025, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	//glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	//Bottom Middle
	glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.1025, -0.215);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(90, -1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	//glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(180, 0.0, 0.0, 1.0);
	glRotatef(10, 0.0, -1.0, 0.0);
	glScalef(0.005, 0.05, 0.07);
	glutSolidCone(0.3, 0.25, 3, 0);
	glPopMatrix();

	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
}

void Zombie::render() {
	glPushMatrix();
	glTranslated(pos_v.getX(), pos_v.getY(), pos_v.getZ());
	drawZombie();
	glPopMatrix();
}

Vector Zombie::update(Vector p) {
	this->playerPos = p;
	float x = (pos_v.getX()), z = -(pos_v.getZ());
	int roundX = (x + 0.5) >= trunc(x) + 1 ? ceil(x) : trunc(x);
	int roundZ = (z + 0.5) >= trunc(z) + 1 ? ceil(z) : trunc(z);
	PathFinder pathF(this->world);
	if(counter == 0 || path.correctPath.size() == 0)
		this->path = pathF.findPath(roundX, roundZ, playerPos.getX(), -playerPos.getZ(), floor, getFloor(playerPos.getY(), 1.6));
	counter++;
	if (counter == 20) counter = 0;//check for new path every twenty steps, less processing
	if (path.correctPath.size() > 0) {
		int newX = path.correctPath.top().getX();
		int newZ = path.correctPath.top().getY();
		bool up = false, down = false, left = false, right = false;
		if (x > newX) {
			left = true;
		}
		else if (x < newX) {
			right = true;
		}
		if (z > newZ) {
			down = true;
		}
		else if (z < newZ) {
			up = true;
		}
		if (up) {
			this->thetha = 0;
			if (right) {
				this->thetha = 45;
			}
			else if (left) {
				this->thetha = 315;
			}
		}
		else if (down) {
			this->thetha = 180;
			if (right) {
				this->thetha = 135;
			}
			else if (left) {
				this->thetha = 225;
			}
		}
		else if (right) {
			this->thetha = 90;
		}
		else if (left) {
			this->thetha = 270;
		}
		this->thetha = (this->thetha)*M_PI / 180;
		this->checkStairs();
		pos_v.setY(pos_v.getY() - 0.7);
		Vector v = Vector(newX, pos_v.getY(), -newZ);
		mask.update(v);
		if (mask.intersects(CollisionMask(playerPos, 0.7))) {
			mask.update(pos_v);
		}
		else {
			return v;
		}
	}
	floor = getFloor(1);
	return pos_v;
}


Zombie::Zombie(float x1, float y1, float z1, World* w) {
	this->phi = 0;
	this->thetha = 0;
	this->pos_v = Vector(x1, y1, z1);
	this->look_v.setV(sin(thetha), sin(phi), -cos(thetha));
	Vector v = getNewPosition(FORWARD);//shift the mask one step forward to accomodate for arms out
	this->mask = CollisionMask(v, 1);
	this->world = w;
	this->floor = getFloor(1);
}

void Zombie::set(Vector v) {
	this->pos_v = v;
	this->look_v.setV(sin(this->thetha), sin(phi), -cos(this->thetha));
	if(path.correctPath.size()>0)
		path.correctPath.pop();
}

Zombie::~Zombie()
{
	//dtor
}
