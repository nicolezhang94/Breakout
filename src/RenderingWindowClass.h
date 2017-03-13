/*! \file RenderingWindowClass.h
 * RenderingWindowClass header
 *
 * \brief Interface between the graphics and EnvironmentClass
 */

class PhysicalObjectClass;

#ifndef RENDERINGWINDOWCLASS_H
#define RENDERINGWINDOWCLASS_H

#include <GL/glui.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "PhysicalObjectClass.h"

class RenderingWindowClass {

public:

	//! Default constructor for RenderingWindowClass
	RenderingWindowClass();

	//! Default destructor for RenderingWindowClass
	~RenderingWindowClass();
	
	//! Determines how to render the color a PhysicalObjectClass object
	/*! This function takes in a PhysicalObjectClass object as an argument and decides based on
	 *    the object's color attribute which parameters to pass to GLUT's glColor3f function, which
	 *    is called in the drawCircle and drawRectangle method.
	 *
	 * \param object a PhysicalObjectClass object within the simulation
	 * 
	 * \return array with RGB values
	 * 
	 * \author Nicole Zhang
	 * \author Rachel Soble
	 */
	double* setGraphicsColor(PhysicalObjectClass* object);

	//! Determines how to draw a PhysicalObjectClass object
	/*! This function takes in a PhysicalObjectClass object as an argument and decides based on
	 *    the object's ObjectType attribute (ballType, paddleType, or brickType) whether to draw the
	 *    object as a circle or rectangle. If an invalid ObjectType is detected, no object is drawn.
	 *
	 * \param object a PhysicalObjectClass object within the simulation
	 *
	 * \author Nicole Zhang
	 */
	void drawObject(PhysicalObjectClass* object);

	//! Draws a circular object
	/*! This function takes in a PhysicalObjectClass object and draws it as a circle of radius "size"
	 *    using 50 triangle fans using GL_TRIANGLE_FAN. The size, color, and location are determined
	 *    by the object's own attributes.
	 *
	 * \param object an object within the simulation
	 *
	 * \author Nicole Zhang
	 */
	void drawCircle(PhysicalObjectClass* object);

	//! Draws a rectangular object
	/*! This function takes in a PhysicalObjectClass object and draws it as a GL_QUADS. Its width, height,
	 *    color, and location are all dependent on the input object's own attributes.
	 * 
	 * \param object an object within the simulation
	 *
	 * \author Nicole Zhang
	 */
	void drawRectangle(PhysicalObjectClass* object);
};

#endif
