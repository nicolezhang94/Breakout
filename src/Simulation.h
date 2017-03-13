/*! \file Simulation.h
 * Simulation header
 * 
 * \brief Main application class for the robot simulation
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "BaseGfxApp.h"

extern int win;
extern int lose;
extern int lostLife;
extern int lives;
extern int flag;
extern double pastTime;
extern float userSpeed;

/** The Simulation class.  This sets up the GUI and the drawing environment. */  
class Simulation : public BaseGfxApp {

public: 

	enum UIControlType {
		UI_QUIT = 0,
	};

	//! Initializes OpenGL window
	/*! Creates OpenGL window and UI panel with Start and Quit buttons, instructions,
	 *    and a speed adjuster.
	 *  
	 * \author Nicole Zhang
	 */
	Simulation(int argc, char* argv[], int width, int height);

	//! Default destructor
	virtual ~Simulation();

	//! Displays the simulation
	/*! This function first determines which GLUI windows need to be displayed based
	 *    on varying flags. Then, it calculates the passed time in the simulation and
	 *    displays the environment and objects accordingly by calling the EnvironmentClass
	 *    display function.
	 * 
	 * \author Nicole Zhang
	 */
	void display();

	//! Starts simulation
	/*! Starts simulation by toggling flag. This allows the environment to 
	 *    run the update function and move the objects.
	 * 
	 * \author Nicholas Inman
	 * \author Nicole Zhang
	 */
	static void start();

	//! Lets user increase speed of all robots
	/*! This function increases the speed of all robots by increasing a global
	 *    flag. Once changed, this flag is added into the calculations performed in
	 *    translate robot
	 * 
	 * \author Nicholas Inman
	 */
	static void adjustSpeed();
};

#endif
