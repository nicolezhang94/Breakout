#include "BaseGfxApp.h"

BaseGfxApp* BaseGfxApp::s_currentApp = NULL;
bool BaseGfxApp::s_glutInitialized = false;

int paddleMovement = 0;

#define INIT_WIDTH 800
#define INIT_HEIGHT 600

BaseGfxApp::BaseGfxApp(int argc, char* argv[], int width, int height, int x, int y, int glutFlags, bool createGLUIWin, int gluiWinX, int gluiWinY) {
	s_currentApp = this;
	m_glui = NULL;
	m_drag = false;
	m_width = width;
	m_height = height;

	// Set window size and position
	glutInitWindowSize(width, height);
	glutInitWindowPosition(x, y);   
	glutInitDisplayMode(glutFlags);

	if (! s_glutInitialized) {
		glutInit(&argc, argv);
		s_glutInitialized = true;
	}

	m_glutWindowHandle = glutCreateWindow("Graphics Window");

	glutReshapeFunc(s_reshape);
	glutKeyboardFunc(s_keyboard);
	glutKeyboardUpFunc(s_keyboardup);
	glutSpecialFunc(s_keyboardspecial);
	glutSpecialUpFunc(s_keyboardspecialup);
	glutMotionFunc(s_mousemotion);
	glutPassiveMotionFunc(s_mousemotion);
	glutMouseFunc(s_mousebtn);
	glutDisplayFunc(s_draw);

	if (createGLUIWin) {
		// Create windows to indicate whether the player has won, lost, or lost 1 life
		resume_glui = GLUI_Master.create_glui("RIP", 0, INIT_WIDTH/2, INIT_HEIGHT/2);
		win_glui = GLUI_Master.create_glui("You won!", 0, INIT_WIDTH/2, INIT_HEIGHT/2);
		lose_glui = GLUI_Master.create_glui("You lost!", 0, INIT_WIDTH/2, INIT_HEIGHT/2);
		
		m_glui = GLUI_Master.create_glui("Controls", 0, gluiWinX, gluiWinY);
		m_glui->set_main_gfx_window(m_glutWindowHandle);
		// Note: if using a glut idle func, it may need to be registered with glui rather than glut.
		GLUI_Master.set_glutIdleFunc(NULL);
	}
}

BaseGfxApp::~BaseGfxApp() {
	s_currentApp = NULL;
	glutDestroyWindow(m_glutWindowHandle);
}

void BaseGfxApp::s_draw() {
	s_currentApp->display();
	glutPostRedisplay();
}

void BaseGfxApp::s_reshape(int width, int height) {
	s_currentApp->reshape(width, height);
}

// Pause/unpause the simulation when the spacebar is pressed
void BaseGfxApp::s_keyboard(unsigned char c, int x, int y) {
	s_currentApp->keyboard(c, x, y);
	if (c == ' ') {
		if (flag == 0) {
			flag = 1;
		} else if (flag == 1) {
			flag = 0;
		}
	}
	glutPostRedisplay();
}

// Move the paddle left or right 5 pixels when the corresponding arrow key is pressed
void BaseGfxApp::s_keyboardspecial(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			paddleMovement -= 5;
			break;
		case GLUT_KEY_RIGHT:
			paddleMovement += 5;
			break;
	}
	glutPostRedisplay();
}

void BaseGfxApp::s_keyboardup(unsigned char c, int x, int y) {
	s_currentApp->keyboardUp(c, x, y);
	glutPostRedisplay();
}

// Stop moving the paddle when the arrow keys are released
void BaseGfxApp::s_keyboardspecialup(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT:
			paddleMovement = 0;
			break;
		case GLUT_KEY_RIGHT:
			paddleMovement = 0;
			break;
	}
	glutPostRedisplay();
}

void BaseGfxApp::s_mousemotion(int x, int y) {
	glutPostRedisplay();
}

void BaseGfxApp::s_mousebtn(int b, int s, int x, int y) {
	if ((b==GLUT_LEFT_BUTTON) && (s==GLUT_UP)) {
		s_currentApp->leftMouseUp(x,y);
		s_currentApp->m_drag = false;
	}
	else if ((b==GLUT_LEFT_BUTTON) && (s==GLUT_DOWN)) {
		s_currentApp->leftMouseDown(x,y);
		s_currentApp->m_drag = true;
	}
	else if ((b==GLUT_RIGHT_BUTTON) && (s==GLUT_UP)) {
		s_currentApp->rightMouseUp(x,y);
	}
	else if ((b==GLUT_RIGHT_BUTTON) && (s==GLUT_DOWN)) {
		s_currentApp->rightMouseDown(x,y);
	}
	else if ((b==GLUT_MIDDLE_BUTTON) && (s==GLUT_UP)) {
		s_currentApp->middleMouseUp(x,y);
	}
	else if ((b==GLUT_MIDDLE_BUTTON) && (s==GLUT_DOWN)) {
		s_currentApp->middleMouseDown(x,y);
	}
	glutPostRedisplay();
}

void BaseGfxApp::s_gluicallback(int controlID) {
	s_currentApp->gluiControl(controlID);
}

void BaseGfxApp::runMainLoop() {
	glutMainLoop();
}

int BaseGfxApp::width() const {
	return m_width;
}

int BaseGfxApp::height() const {
	return m_height;
}

void BaseGfxApp::setCaption(const std::string& caption) {
	glutSetWindowTitle(caption.c_str());
	glutSetIconTitle(caption.c_str());
}

void BaseGfxApp::reshape(int width, int height) {
	if (s_currentApp->width() != width || s_currentApp->height() != height) {
		glutReshapeWindow( s_currentApp->width(), s_currentApp->height() );
	}
}


