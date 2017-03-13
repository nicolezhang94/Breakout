/*! \file Simulation.cpp
 *
 * \brief Contains Simulation class definitions
 */

#include "Simulation.h"
#include "EnvironmentClass.h"
using namespace std;

#define PI 3.14

// Only constructor. Creates the simulation with OpenGL
Simulation::Simulation(int argc, char* argv[], int width, int height) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, 865, 50) {
	// Set up OpenGL windows
	setCaption("Call of Duty: Advanced Warfare");

	GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Control Panel");
	new GLUI_Button(toolPanel, "Start", 2, (GLUI_Update_CB)start);

	GLUI_Panel *instructionsPanel = new GLUI_Panel(m_glui, "Instructions");
	m_glui->add_statictext_to_panel(instructionsPanel, "Use the arrow keys to move the paddle.");
	m_glui->add_statictext_to_panel(instructionsPanel, "Press the spacebar to pause.");

	GLUI_Spinner* speed_control = new GLUI_Spinner(m_glui, "Speed", &userSpeed, -1, (GLUI_Update_CB)adjustSpeed);
	speed_control->set_float_limits(0, 3, GLUI_LIMIT_CLAMP);

	new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);

	win_glui->add_statictext("Yaaaaaaaaaaaaaaaaaaay");
	lose_glui->add_statictext("Were you even trying?");
	resume_glui->add_statictext("Press F to pay respects");
	resume_glui->add_statictext("           (restart)");
	resume_glui->add_button("F", 2, (GLUI_Update_CB)start);
	resume_glui->hide();

	// Initialize OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glViewport(0, 0, m_width, m_height);
}

Simulation::~Simulation() {

}

// Starts/resumes the simulation
void Simulation::start() {
	flag = 0;
	if (lives == 0) {
		flag = 1;
	}
	pastTime = glutGet(GLUT_ELAPSED_TIME);
}

// Adjusts speed
void Simulation::adjustSpeed() {

}

// Displays the simulation
void Simulation::display() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Display Controls window if simulation is paused
	if (flag) {
		m_glui->show();
	} else {
		m_glui->hide();
	}
	// Display Press F to Pay Respects window if player loses a life
	if (lostLife) {
		resume_glui->show();
	} else {
		resume_glui->hide();
	}
	// Display "You Win!" window if player breaks all the bricks
	if (win) {
		win_glui->show();
	} else {
		win_glui->hide();
	}
	// Display "You Lose!" window if player loses all three lives
	if (lose) {
		lose_glui->show();
	} else {
		lose_glui->hide();
	}
	
	int timeStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeStart - pastTime;
	pastTime = timeStart;

	environment.display(deltaTime / 10.0);

	// Debugging messages
	int err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		cerr << "GL is in an error state" << endl;
		cerr << "(GL error code " << err << ")\n";
		assert(0);
	}

	// advance
	glutSwapBuffers();
}
