/*! \file PhysicalObjectClass.cpp
 * PhysicalObjectClass.cpp 
 *
 * \brief The class that creates all physical objects
 */

#include "PhysicalObjectClass.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Default constructor
PhysicalObjectClass::PhysicalObjectClass() {

}

// Primary constructor. Attributes are determined based on object type and other input
PhysicalObjectClass::PhysicalObjectClass(ObjectType objTypeIn, double x, double y, char colorIn) {
	location[0] = x;
	location[1] = y;
	color = colorIn;
	id = -1;
	if (objTypeIn == ballType) {
		objType = ballType;
		size = 6;
		width = 0;
		speed = 3;
		orientation = 90;
	} else if (objTypeIn == paddleType) {
		objType = paddleType;
		size = 10;
		width = 80;
		speed = 0;
		orientation = 0;
	} else if (objTypeIn == brickType) {
		objType = brickType;
		size = brickHeight;
		width = brickWidth;
		speed = 0;
		orientation = 0;
	}
}

// Constructor for life indicator balls
PhysicalObjectClass::PhysicalObjectClass(double x, double y) {
	objType = ballType;
	size = 6;
	location[0] = x;
	location[1] = y;
	color = 'W';
}

// Destructor
PhysicalObjectClass::~PhysicalObjectClass() {

}

// Set the color of the object
void PhysicalObjectClass::setColor(char colorIn) {
	color = colorIn;
}

// Set the size of the object
void PhysicalObjectClass::setSize(double sizeIn) {
	size = sizeIn;
}

// Set the double (x, y) location of the object
void PhysicalObjectClass::setLocation(double x, double y) {
	location[0] = x;
	location[1] = y;
}

// Set the speed of the object (pps, pixels per second)
// Speed cannot be negative. It remains constant once set.
void PhysicalObjectClass::setSpeed(double pps) {
	if (pps < 0) {
		cout << "Incorrect input: speed cannot be negative.\n" << endl;
	} else {
	speed = pps;
	}
}

// Set the orientation of the object
// 0 degrees = positive x-axis; increases counterclockwise
// If input negative value, turned into positive (degrees % 360 = degrees || 360-degrees)
void PhysicalObjectClass::setOrientation(double degrees) {
	if (degrees > 360.0) {
		while (degrees > 360.0) {
			degrees -= 360.0;
		}
	} else if (degrees < 0.0) {
		while (degrees < 0.0) {
			degrees += 360.0;
		}
	}
	orientation = degrees;
}

// Set the ID of the object
void PhysicalObjectClass::setID(int idIn) {
	id = idIn;
}

// Get the ObjectType of the object
ObjectType PhysicalObjectClass::getObjectType() {
	return objType;
}

// Get the color of the object
char PhysicalObjectClass::getColor() {
	return color;
}

// Get the size of the object
double PhysicalObjectClass::getSize() {
	return size;
}

// Get the width of the object
double PhysicalObjectClass::getWidth() {
	return width;
}

// Get the x location of the object
double PhysicalObjectClass::getXLocation() {
	return location[0];
}

// Get the y location of the object
double PhysicalObjectClass::getYLocation() {
	return location[1];
}

// Get the speed of the object
double PhysicalObjectClass::getSpeed() {
	return speed;
}

// Get the orientation of the object
double PhysicalObjectClass::getOrientation() {
	return orientation;
}

// Get the ID of the object
int PhysicalObjectClass::getID() {
	return id;
}
