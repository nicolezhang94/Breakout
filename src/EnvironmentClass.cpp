/*! \file EnvironmentClass.cpp
 * 
 * \brief Manages and controls object movement and behavior
 */

#include "EnvironmentClass.h"

int win = 0;
int lose = 0;
int lostLife = 0;

using namespace std;

// Default constructor
EnvironmentClass::EnvironmentClass() {

}

// Manages all updates within the environment (primarily translation and collision)
void EnvironmentClass::update(double elapsedTime) {
	int numOfObjects = physicalObjectVector.size();
	// Prevents environment from updating if player has no lives left
	if (lives == 0) {
		lose = 1;
		lostLife = 0;
		flag = 1;
		return;
	}
	// Prevents environment from updating if player has already won
	if (numOfObjects == 2) {
		win = 1;
		flag = 1;
		return;
	}
	// Prevents environment from updating if otherwise paused
	if (flag) {
		return;
	}

	lostLife = 0;

	// Cycles through physicalObjectVector to move objects and detect collision
	for(int i = 0; i < numOfObjects; i++) {
		if(physicalObjectVector.size() < numOfObjects) {
			break;
		}
		PhysicalObjectClass* currentObject = physicalObjectVector.at(i);
		ObjectType current_Type = currentObject->getObjectType();

		if (current_Type == ballType) {
			translate(currentObject, elapsedTime);
			int TSR = touchSensorReading(currentObject);
			if (TSR == -1) {
				// Ball did not collide with anything; do nothing
			} else if (TSR == -2) {
				// Ball collided with a wall upon the move and bounces off
				bounceOffWall(currentObject);
			} else {
				// Ball collided with another object upon the move; bounce behavior determined within
				PhysicalObjectClass* hitObject = physicalObjectVector.at(TSR);
				objectCollision(currentObject, hitObject, elapsedTime);
			}
		}
		if (current_Type == paddleType) {
			translate(currentObject, elapsedTime);
		}
	}
}

// Displays the environment and draws the life indicator balls
void EnvironmentClass::display(double elapsedTime) {
	update(elapsedTime);
	for (int i = 0; i < (int) physicalObjectVector.size(); i++) {
		renderEnv->drawObject(physicalObjectVector.at(i));
	}
	int x = 25;
	int y = 575;
	for (int i = 0; i < lives; i++) {
		PhysicalObjectClass* livesUI = new PhysicalObjectClass(x, y); 
		renderEnv->drawObject(livesUI);
		x += 25;
	}
}

// Detects if the ball has collided with any object or wall
int EnvironmentClass::touchSensorReading(PhysicalObjectClass* ball) {
	double ball_Size = ball->getSize();
	double ball_X = ball->getXLocation();
	double ball_Y = ball->getYLocation();
	int numOfObjects = physicalObjectVector.size();
	// Checks for object collision
	for (int i = 0; i < numOfObjects; i++) {
		CollisionType collideLocation = collisionLocation(ball, physicalObjectVector.at(i));
		if (collideLocation != noCollision && physicalObjectVector.at(i)->getID() != ball->getID()) {
			return i;
		}
	}
	// Checks for wall collision
	if (((ball_X + ball_Size) > windowWidth) || (ball_X < ball_Size) || ((ball_Y + ball_Size) > windowHeight) || (ball_Y < ball_Size)) {
		return -2;
	}
	// If no collision, return -1
	return -1;
}

// Translates the ball and paddle objects based on their relative speeds/locations
void EnvironmentClass::translate(PhysicalObjectClass* object, double elapsedTime) {
	double old_X = object->getXLocation();
	double old_Y = object->getYLocation();
 	double old_Orientation = object->getOrientation();
	ObjectType obj_Type = object->getObjectType();
	if (obj_Type == ballType) {
		double ball_Speed = object->getSpeed();
		double moveMagnitude = elapsedTime * (ball_Speed+(4*userSpeed/9));
		double move_X = cos(old_Orientation * (M_PI/180)) * moveMagnitude;
		double move_Y = sin(old_Orientation * (M_PI/180)) * moveMagnitude;
		double new_X = old_X + move_X;
		double new_Y = old_Y + move_Y;
		object->setLocation(new_X, new_Y);
		return;
	}
	if (obj_Type == paddleType) {
		double obj_Width = object->getWidth();
		double new_X = old_X + paddleMovement;
		// Prevent paddle from moving off-screen
		if (new_X < 0 || new_X > (windowWidth - obj_Width)) {
			object->setLocation(old_X, old_Y);
		} else {
			object->setLocation(new_X, old_Y);
		}
		return;
	}
}

// Determines whether the ball has collided with a brick or the paddle
void EnvironmentClass::objectCollision(PhysicalObjectClass* currentObject, PhysicalObjectClass* hitObject, double elapsedTime) {
	ObjectType current_Type = currentObject->getObjectType();
	ObjectType hit_Type = hitObject->getObjectType();
	if ((current_Type == ballType) && (hit_Type == brickType)) {
		bounceOffBrick(currentObject, hitObject);
		translate(currentObject, elapsedTime);
		removeObject(hitObject);
	} else if ((current_Type == ballType) && (hit_Type == paddleType)) {
		bounceOffPaddle(currentObject, hitObject);
		translate(currentObject, elapsedTime);
	}
}

// Determines which side on a brick the ball has collided with
CollisionType EnvironmentClass::collisionLocation(PhysicalObjectClass* ball, PhysicalObjectClass* brick) {
	double ball_Size = ball->getSize();
	double ball_X = ball->getXLocation();
	double ball_Y = ball->getYLocation();

	double brick_Size = brick->getSize();
	double brick_X = brick->getXLocation();
	double brick_Y = brick->getYLocation();
	double brick_Width = brick->getWidth();

	if ((ball_Y <= brick_Y && ball_Y >= brick_Y-brick_Size) && (ball_X+ball_Size >= brick_X && ball_X+ball_Size <= brick_X+40)) {
		return leftCollision;
	} else if ((ball_Y <= brick_Y && ball_Y >= brick_Y-brick_Size) && (ball_X-ball_Size <= brick_X+brick_Width && ball_X-ball_Size >= brick_X+brick_Width-40)) {
		return rightCollision;
	} else if ((ball_X >= brick_X && ball_X <= brick_X+brick_Width) && (ball_Y-ball_Size <= brick_Y && ball_Y-ball_Size >= brick_Y-brick_Size-7)) {
		return topCollision;
	} else if ((ball_X >= brick_X && ball_X <= brick_X+brick_Width) && (ball_Y+ball_Size <= brick_Y+7 && ball_Y+ball_Size >= brick_Y-brick_Size)) {
		return bottomCollision;
	}
	return noCollision;
}

// Performs wall bounce movement corresponding to collision location and original orientation
void EnvironmentClass::bounceOffWall(PhysicalObjectClass* ball) {
	double variation = (double) (rand() % 6) - 3;

	double ball_Size = ball->getSize();

	double old_Orientation = ball->getOrientation();
	double old_XLocation = ball->getXLocation();
	double old_YLocation = ball->getYLocation();

	double new_Orientation = old_Orientation;
	double new_XLocation = old_XLocation;
	double new_YLocation = old_YLocation;

	if (old_XLocation >= windowWidth - ball_Size) {
		// Right wall
		if (old_Orientation < 180) {
			new_Orientation = 180 - old_Orientation;
			new_XLocation = windowWidth - ball_Size;
		} else if (old_Orientation > 180) {
			new_Orientation = 180 + (360 - old_Orientation);
			new_XLocation = windowWidth - ball_Size;
		} else if (old_Orientation == 0) {
			new_Orientation = 180 + variation;
			new_XLocation = windowWidth - ball_Size;
		}
	} else if (old_XLocation <= ball_Size) {
		// Left wall
		if (old_Orientation < 180) {
			new_Orientation = 180 - old_Orientation;
			new_XLocation = ball_Size;
		} else if (old_Orientation > 180) {
			new_Orientation = 360 - (old_Orientation - 180);
			new_XLocation = ball_Size;
		} else if (old_Orientation == 180) {
			new_Orientation = 0 + variation;
			new_XLocation = ball_Size;
		}
	} else if (old_YLocation >= windowHeight - ball_Size) {
		// Top wall
		if (old_Orientation < 90) {
			new_Orientation = 360 - old_Orientation;
			new_YLocation = windowHeight - ball_Size;
		} else if (old_Orientation > 90) {
			new_Orientation = 360 - old_Orientation;
			new_YLocation = windowHeight - ball_Size;
		} else if (old_Orientation == 90) {
			new_Orientation = 270 + variation;
			new_YLocation = windowHeight - ball_Size;
		}
	} else if (old_YLocation <= ball_Size) {
		// Bottom wall: Lose a life and restart
		new_XLocation = 400;
		new_YLocation = 80;
		new_Orientation = 90;
		physicalObjectVector.at(1)->setLocation(360, 73);
		lives--;
		lostLife = 1;
		flag = 1;
	}

	ball->setOrientation(new_Orientation);
	ball->setLocation(new_XLocation, new_YLocation);
}

// Performs brick bounce movement corresponding to collision location and original orientation
void EnvironmentClass::bounceOffBrick(PhysicalObjectClass* ball, PhysicalObjectClass* brick) {
	double old_Orientation = ball->getOrientation();
	double new_Orientation = old_Orientation;
	double variation = (double) (rand() % 6) - 3;

	CollisionType collideLocation = collisionLocation(ball, brick);

	if (collideLocation == rightCollision) {
		if (old_Orientation < 180) {
			new_Orientation = 180 - old_Orientation;
		} else if (old_Orientation > 180) {
			new_Orientation = 360 - (old_Orientation - 180);
		} else if (old_Orientation == 180) {
			new_Orientation = 0 + variation;
		}
	} else if (collideLocation == leftCollision) {
		if (old_Orientation < 180) {
			new_Orientation = 180 - old_Orientation;
		} else if (old_Orientation > 180) {
			new_Orientation = 180 + (360 - old_Orientation);
		} else if (old_Orientation == 0) {
			new_Orientation = 180 + variation;
		}
	} else if (collideLocation == topCollision || collideLocation == bottomCollision) {
		if (old_Orientation < 90) {
			new_Orientation = 360 - old_Orientation;
		} else if (old_Orientation > 90 && old_Orientation < 180) {
			new_Orientation = 360 - old_Orientation;
		} else if (old_Orientation > 180 && old_Orientation < 270) {
			new_Orientation = old_Orientation - (old_Orientation - 180);
		} else if (old_Orientation > 270 && old_Orientation < 360) {
			new_Orientation = 360 - old_Orientation;
		} else if (old_Orientation == 90) {
			new_Orientation = 270 + variation;
		} else if (old_Orientation == 180) {
			new_Orientation = 0 + variation;
		} else if (old_Orientation == 270) {
			new_Orientation = 90 + variation;
		} else if (old_Orientation == 360 || old_Orientation == 0) {
			new_Orientation = 180 + variation;
		}
	}
	ball->setOrientation(new_Orientation);
}

// Performs paddle bounce movement corresponding to collision location on paddle
void EnvironmentClass::bounceOffPaddle(PhysicalObjectClass* ball, PhysicalObjectClass* paddle) {
	double new_Orientation;

	double ball_XLocation = ball->getXLocation();
	double paddle_XLocation = paddle->getXLocation();

	double paddle_Width = paddle->getWidth();
	double paddle_Middle = paddle_XLocation + (paddle_Width / 2);
	double hitLocation;

	// Bounce back angle is sharper the further away from the centerpoint the ball hits
	if (ball_XLocation < paddle_Middle) {
		hitLocation = paddle_Middle - ball_XLocation;
		new_Orientation = 90 + hitLocation;
	} else if (ball_XLocation > paddle_Middle) {
		hitLocation = ball_XLocation - paddle_Middle;
		new_Orientation = 90 - hitLocation;
	} else if (ball_XLocation == paddle_Middle) {
		new_Orientation = 90;
	}
	ball->setOrientation(new_Orientation);
}

// Removes an object from the physicalObjectVector and therefore from the simulation
void EnvironmentClass::removeObject(PhysicalObjectClass* object) {
	int i;
	for(i = 0; i < (int)physicalObjectVector.size(); i++){
		if(physicalObjectVector.at(i)->getID() == object->getID()){
			physicalObjectVector.erase(physicalObjectVector.begin() + i);
			return;
		}
	}
}
