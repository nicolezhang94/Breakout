/*! \file main.cpp
 * 
 * \brief driver file for robot class
 *
 * Creates objects and runs simulation loop
 *
 * \author Nicole Zhang
 */

#include "Simulation.h"
#include "EnvironmentClass.h"

// The following global variables can be adjusted to change game settings
int windowWidth = 800;
int windowHeight = 600;
int bricksPerRow = 16;
int brickWidth = 800 / bricksPerRow;
int brickHeight = 15;
int numBricks = bricksPerRow * 6;
int lives = 3;
int flag = 1;
double pastTime = 0;
float userSpeed = 0;

using namespace std;

EnvironmentClass environment;

int main(int argc, char* argv[])
{
	srand(time(0));

	// Create the ball
	PhysicalObjectClass* ball = new PhysicalObjectClass(ballType, 400, 80, 'W');
	ball->setID(0);
	environment.physicalObjectVector.push_back(ball);

	// Create the paddle
	PhysicalObjectClass* paddle = new PhysicalObjectClass(paddleType, 360, 73, 'W');
	paddle->setID(1);
	environment.physicalObjectVector.push_back(paddle);

	// Create all of the bricks
	double gapSize = 70;
	double x = 0;
	double y = windowHeight - gapSize;
	double yStart = y;
	char colorIn = 'R';
	for (int i = 0; i < numBricks; i++)
	{
		if (x > (windowWidth-brickWidth)) {
			x = 0;
			y -= brickHeight;
			if (y == (yStart - brickHeight)) {
				colorIn = 'O';
			} else if (y == (yStart - (2 * brickHeight))) {
				colorIn = 'Y';
			} else if (y == (yStart - (3 * brickHeight))) {
				colorIn = 'G';
			} else if (y == (yStart - (4 * brickHeight))) {
				colorIn = 'B';
			} else if (y == (yStart - (5 * brickHeight))) {
				colorIn = 'P';
			}
		}
		PhysicalObjectClass* brick_i = new PhysicalObjectClass(brickType, x, y, colorIn);
		brick_i->setID(i+2);
		environment.physicalObjectVector.push_back(brick_i);
		x+=brickWidth;
	}

	Simulation *app = new Simulation(argc, argv, windowWidth, windowHeight);
	app->runMainLoop();
	exit(0);
}

