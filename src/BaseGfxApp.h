/*! \file  BaseGfxApp.h
 * \author CSci3081 Guru
 *
 * \brief The basic application class for CSci-3081 project.  Uses GLUT and 
 *        GLUI and wraps them in a nice C++ interface.
 */

#ifndef BASEGFXAPP_H
#define BASEGFXAPP_H

// Frequently used C++ stuff 
#include <string>
#include <iostream>
using namespace std;
#include <assert.h>

// The GLUI library, which in turn will include gl.h and glut.h
#include <GL/glui.h>

extern int flag;

class BaseGfxApp {
public:
	BaseGfxApp(int argc, char* argv[], int width, int height, int x, int y, int glutFlags, 
				bool createGLUIWin, int gluiWinX, int gluiWinY);
	virtual ~BaseGfxApp();

	void setCaption(const std::string& caption);
	void runMainLoop();

	virtual void display() {};
	
	virtual void mouseMoved(int x, int y) {};
	virtual void mouseDragged(int x, int y) {};

	virtual void leftMouseDown(int x, int y) {};
	virtual void leftMouseUp(int x, int y) {};
	virtual void rightMouseDown(int x, int y) {};
	virtual void rightMouseUp(int x, int y) {};
	virtual void middleMouseDown(int x, int y) {};
	virtual void middleMouseUp(int x, int y) {};
	
	virtual void keyboard(unsigned char c, int x, int y) {};
	virtual void keyboardSpecial(int key, int x, int y) {};
	virtual void keyboardUp(unsigned char c, int x, int y) {};
	virtual void keyboardSpecialUp(int key, int x, int y) {};
	
	virtual void reshape(int width, int height);

	virtual void gluiControl(int controlID) {};

	int width() const;
	int height() const;
	int handle() { return m_glutWindowHandle; }
	GLUI* glui() { return m_glui; }

protected:

	/** GLUT and GLUI event callbacks are sent to the current window/app. Right now, there is only
		one window anyway (not counting the GLUI UI window.. in the future could be extended to 
		support more windows.  In any case, some structure like this is always needed when using 
		glut with C++, since the glut callbacks must be either global or static functions. */
	static BaseGfxApp*		s_currentApp;  

	/** Has glutInit been called? (only allowed once per program) */
	static bool				s_glutInitialized;

	// Glut callbacks:
	static void s_reshape(int width, int height);
	
	//! Perform keyboard press actions
	/*! Pauses or resumes the simulation when spacebar is pressed, depending on the
	 *    current flag status.
	 *
	 * \param c character pressed
	 * \param x mouse x location
	 * \param y mouse y location
	 * 
	 * \author Nicole Zhang
	 */	
	static void s_keyboard(unsigned char c, int x, int y);
	
	//! Perform special keyboard press actions
	/*! Moves the paddle left or right when the left or right arrow key is pressed.
	 *
	 * \param key key pressed
	 * \param x mouse x location
	 * \param y mouse y location
	 * 
	 * \author Nicole Zhang
	 */	
	static void s_keyboardspecial(int key, int x, int y);
	static void s_keyboardup(unsigned char c, int x, int y);
	
	//! Determines which side of a brick has been hit
	/*! The paddle stops moving when the left or right arrow key are released.
	 *
	 * \param key key released
	 * \param x mouse x location
	 * \param y mouse y location
	 *
	 * \author Nicole Zhang
	 */	
	static void s_keyboardspecialup(int key, int x, int y);
	static void s_mousemotion(int x, int y);
	static void s_mousebtn(int b, int s, int x, int y);
	static void s_draw();    
	static void s_gluicallback(int controlID);

	/** Underlying glut window handle */
	int						m_glutWindowHandle;

	// Pointer to GLUI master
	GLUI*					m_glui;
	GLUI*					win_glui;
	GLUI*					resume_glui;
	GLUI*					lose_glui;

	bool m_drag;
	int m_width;
	int m_height;
};


#endif
