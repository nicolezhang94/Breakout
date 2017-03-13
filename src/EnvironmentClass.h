/*! \file EnvironmentClass.h
 * Environment Class header
 * 
 * \brief The class that controls the environment that the objects move in
 */

class PhysicalObjectClass;
class RenderingWindowClass;

#ifndef ENVIRONMENTCLASS_H
#define ENVIRONMENTCLASS_H

#include "RenderingWindowClass.h"
#include <time.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#ifndef __FLAG
#define __FLAG
extern int flag;
#endif
extern float userSpeed;
extern int lives;
extern int paddleMovement;
extern int windowWidth;
extern int windowHeight;

//! Relative collision locations on a brick
enum CollisionType {
	leftCollision,
	rightCollision,
	topCollision,
	bottomCollision,
	noCollision
};

class EnvironmentClass {

public:
	//! Default constructor for EnvironmentClass
	EnvironmentClass();

	//! Updates the environment and all its objects
	/*! This function takes in one argument, elapsedTime, and iterates through
	 *    the physicalObjects array, calling move each time. Move then returns
	 *    a double[2] array containing the direction and magnitude of movement.
	 *    Based on which coordinate the object currently is in, it sets the object's
	 *    new position.
	 *
	 * \param elapsedTime the amount of time passed
	 * 
	 * \author Nicholas Inman
	 * \author Rachel Soble
	 * \author Nicole Zhang
	 */
	void update(double elapsedTime);

	//! Draw and displays objects and environment
	/*! This function is constantly called from simulation. It displays and draws all the objects
	 *    and calls the update function and effectively sets up the environment. It uses the elapsed
	 *    time input to determine the amount of movement for each object. This function also draws
	 *    the life indicator balls in the upper left corner of the simulation.
	 *
	 * \param elapsedTime amount of time passed since last update
	 *
	 * \author Nicole Zhang
	 */
	void display(double elapsedTime);

	//! Collision detection
	/*! This function takes in the ball and checks if it's colliding with 
	 *    another object or a wall. It returns -1 if the ball is not colliding with
	 *    anything, -2 if it is colliding with a wall, or the index of the object it is
	 *    colliding with.
	 *
	 * \param ball the ball
	 * 
	 * \return -1 if the ball is not colliding with anything
	 *    -2 if the ball is colliding with a wall
	 *    index of the object the ball is colliding with
	 *
	 * \author Nicole Zhang
	 */
	int touchSensorReading(PhysicalObjectClass* ball);

	//! Moves the input object
	/*! This function resets the location of the input object based on its speed, original
	 *    location, orientation, and elapsed time.
	 *
	 * \param object the object being translated
	 * \param elapsedTime the amount of time passed
	 *
	 * \author Nicholas Inman
	 * \author Rachel Soble
	 * \author Nicole Zhang
	 */
	void translate(PhysicalObjectClass* object, double elapsedTime);

	//! Performs wall collision movement
	/*! This function determines whether the object being hit is a brick or a paddle. If it
	 *    is a brick, it will remove the brick after performing the appropriate collision
	 *    movement. If it is a paddle, then it will perform the paddle collision movement but
	 *    the paddle not be removed from the simulation.
	 *
	 * \param currentObject ball object
	 * \param hitObject object being hit
	 * \param elapsedTime elapsed time
	 *
	 * \author Nicole Zhang
	 */
	void objectCollision(PhysicalObjectClass* currentObject, PhysicalObjectClass* hitObject, double elapsedTime);

	//! Determines which side of a brick has been hit
	/*! This function determines which side of a brick the ball is colliding with and returns the
	 *    CollisionType enum indicating whether the left, right, top, or bottom side has been
	 *    collided into. If no collision is detected, noCollision will be returned.
	 *
	 * \param ball the ball
	 * \param brick the brick being hit
	 *
	 * \return enum CollisionType location of collision
	 *
	 * \author Nicole Zhang
	 */	
	CollisionType collisionLocation(PhysicalObjectClass* ball, PhysicalObjectClass* brick);

	//! Performs wall collision movement
	/*! This function performs collision movement when the ball has hit a wall. It first
	 *    detects which wall it has hit and then bounces off in a natural manner, based on
	 *    its old orientation. The ball is also translated inwards a bit in order to prevent
	 *    clipping. If the ball has collided with the bottom wall, the ball does not bounce off
	 *    but instead returns to the starting location and orientation. The paddle also returns
	 *    to its starting location. In this case, a turn is lost and the game is paused, until
	 *    the player presses "Start" again.
	 *
	 * \param ball the ball
	 *
	 * \author Nicole Zhang
	 */
	void bounceOffWall(PhysicalObjectClass* ball);

	//! Performs brick collision movement
	/*! This function first determines which side of a brick the ball has collided with through
	 *    the collisionLocation function. It then determines the new orientation the ball must
	 *    have in order to have a natural looking bounce, which is based on its old orientation.
	 *
	 * \param ball the ball
	 * \param brick the brick being hit
	 *
	 * \author Nicole Zhang
	 */
	void bounceOffBrick(PhysicalObjectClass* ball, PhysicalObjectClass* brick);

	//! Performs paddle collision movement
	/*! This function finds where on the paddle the ball has collided with and determines
	 *    its new orientation based on this information. The further away from the paddle's
	 *    centerpoint the ball has collided with, the sharper the angle the ball will
	 *    bounce back towards.
	 *
	 * \param ball the ball
	 * \param paddle the paddle
	 *
	 * \author Nicole Zhang
	 */
	void bounceOffPaddle(PhysicalObjectClass* ball, PhysicalObjectClass* paddle);

	//! Removes the object from the simulation
	/*! This function removes the input object from the simulation by erasing it from
	 *    the PhysicalObjectVector.
	 *
	 * \param object the object that needs removing
	 *
	 * \author Nicholas Inman
	 */
	void removeObject(PhysicalObjectClass* object);

	std::vector<PhysicalObjectClass*> physicalObjectVector;
	RenderingWindowClass *renderEnv;
};

#endif
