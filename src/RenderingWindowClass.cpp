/*! \file RenderingWindowClass.cpp
 * RenderingWindowClass.cpp 
 *
 * \brief Interface between the graphics and EnvironmentClass
 */

#include "RenderingWindowClass.h"

using namespace std;

#define PI 3.14f

// Default constructor
RenderingWindowClass::RenderingWindowClass() {

}

// Destructor
RenderingWindowClass::~RenderingWindowClass() {

}

// Determines glColor3f parameters based on the object's color attribute
double* RenderingWindowClass::setGraphicsColor(PhysicalObjectClass* object) {
	double* colorArray = new double[3];
	switch (object->getColor()) {
		case 'R':			// Red
			colorArray[0] = 1;
			colorArray[1] = 0;
			colorArray[2] = 0;
			break;
		case 'Y':			// Yellow
			colorArray[0] = 1;
			colorArray[1] = 1;
			colorArray[2] = 0;
			break;
		case 'M':			// Magenta
			colorArray[0] = 1;
			colorArray[1] = 0;
			colorArray[2] = 1;
			break;
		case 'G':			// Green
			colorArray[0] = 0;
			colorArray[1] = 1;
			colorArray[2] = 0;
			break;
		case 'C':			// Cyan
			colorArray[0] = 0;
			colorArray[1] = 1;
			colorArray[2] = 1;
			break;
		case 'B':			// Blue
			colorArray[0] = 0;
			colorArray[1] = 0;
			colorArray[2] = 1;
			break;
		case 'W':			// White
			colorArray[0] = 1;
			colorArray[1] = 1;
			colorArray[2] = 1;
			break;
		case 'O':			// Orange
			colorArray[0] = 1;
			colorArray[1] = 0.5;
			colorArray[2] = 0;
			break;
		case 'D':			// Dark Orange
			colorArray[0] = 0.9;
			colorArray[1] = 0.45;
			colorArray[2] = 0;
			break;
		case 'P':			// Purple
			colorArray[0] = 0.5;
			colorArray[1] = 0;
			colorArray[2] = 1;
			break;
	}
	return colorArray;
}

// Decides how to draw a PhysicalObjectClass object based on its ObjectType attribute
void RenderingWindowClass::drawObject(PhysicalObjectClass* object) {
	ObjectType obj_Type = object->getObjectType();
	if (obj_Type == ballType) {
		drawCircle(object);
	} else if (obj_Type == paddleType || obj_Type == brickType) {
		drawRectangle(object);
	} else {
		cout << "Invalid object type. Object not drawn." << endl;
	}
}

// Draws the ball
void RenderingWindowClass::drawCircle(PhysicalObjectClass* object) {
	double object_X = object->getXLocation();
	double object_Y = object->getYLocation();
	double object_Size = object->getSize();
	double* colorArray = setGraphicsColor(object);
 
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(colorArray[0], colorArray[1], colorArray[2]);
	glVertex2f(object_X, object_Y);
	for (int i = 0; i <= 50; i++) {
		glVertex2f(((object_Size * cos(i*2*PI/50)) + object_X),
			((object_Size * sin(i*2*PI/50)) + object_Y));
	}
	glEnd();
}

// Draws bricks and the paddle
void RenderingWindowClass::drawRectangle(PhysicalObjectClass* object) {
	double object_X = object->getXLocation();
	double object_Y = object->getYLocation();
	double object_Size = object->getSize();
	double object_Width = object->getWidth();
	double* colorArray = setGraphicsColor(object);

	glBegin(GL_QUADS);
	glColor3f(colorArray[0], colorArray[1], colorArray[2]);
	glVertex2f(object_X, object_Y);
	glVertex2f(object_X+object_Width, object_Y);
	glVertex2f(object_X+object_Width, object_Y-object_Size);
	glVertex2f(object_X, object_Y-object_Size);
	glEnd();
}
