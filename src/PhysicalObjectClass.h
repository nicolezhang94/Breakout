/*! \file PhysicalObjectClass.h
 * PhysicalObjectClass header
 *
 * \brief The class that creates all physical objects
 */

class EnvironmentClass;

extern EnvironmentClass environment;
extern int brickWidth;
extern int brickHeight;

#ifndef PHYSICALOBJECTCLASS_H
#define PHYSICALOBJECTCLASS_H

//! Different object types of PhysicalOjbects
enum ObjectType {
	ballType,
	paddleType,
	brickType
};

class PhysicalObjectClass {

public:

	//! Default constructor for PhysicalObjectClass
	PhysicalObjectClass();

	//! Primary constructor for PhysicalObjectClass
	/*! This constructor is used to create all the physical objects in the simulation.
	 *    It takes in the object type, location, and color, as specified when the
	 *    objects are created in the main file. The remaining attributes are determined
	 *    based on its specified object type.
	 * 
	 * \param objTypeIn object type
	 * \param x x location
	 * \param y y location
	 * \param colorIn object color
	 *  
	 * \author Nicole Zhang
	 */
	PhysicalObjectClass(ObjectType objTypeIn, double x, double y, char colorIn);

	//! Constructor for life indicator balls
	/*! This constructor is only used to create the life indicator UI (three
	 *    balls in the upper left corner).
	 * 
	 * \param x x location
	 * \param y y location
	 *
	 * \author Nicole Zhang
	 */
	PhysicalObjectClass(double x, double y);

	//! Default destructor for PhysicalObjectClass
	~PhysicalObjectClass();

	//! Set the PhysicalObject color
	/*! This function takes in the char argument color and sets the object's color
	 *    to the corresponding input color.
	 *
	 * \param colorIn character representing color
	 *
	 * \author Nicole Zhang
	 */
	void setColor(char colorIn);

	//! Set the PhysicalObject size
	/*! This function takes in the double argument sizeIn and sets thusly the object's
	 *    size.
	 *
	 * \param sizeIn double sizeIn
	 *
	 * \author Nicole Zhang
	 */
	void setSize(double sizeIn);

	//! Set the PhysicalObject location
	/*! This function takes in the double arguments (x, y). The object's location is
	 *    determined for each ObjectType.
	 *
	 * \param x double x-coordinate
	 * \param y double y-coordinate
	 *
	 * \author Nicole Zhang
	 */
	virtual void setLocation(double x, double y);

	//! Sets the PhysicalObject speed
	/*! This function takes in the double argument pps and sets it as the object's
	 *    speed in pixels per second.
	 *
	 * \param pps double speed in pixels per second
	 *
	 * \author Rachel Soble
	 */
	void setSpeed(double pps); 

	//! Sets the object orientation
	/*! This function takes in a double argument degrees and then orients the robot.
	 *    If the degree value is out of bounds, this function adds or subtracts the
	 *    degree value by 360 in order to bring it back in bounds.
	 *
	 * \param degrees double argument for orientation
	 *
	 * \author Rachel Soble
	 * \author Nicole Zhang
	 */ 
	void setOrientation(double degrees);

	//! Sets the object's ID in the env PhysicalObject vector
	/*!
	 * \param id integer identifier
	 *
	 * \author Nicole Zhang
	 */
	void setID(int idIn);

	//! Returns the object ObjectType
	/*!
	 * \return ObjectType objType
	 *
	 * \author Nicole Zhang
	 */
	ObjectType getObjectType();

	//! Returns the object color
	/*!
	 * \return char color
	 *
	 * \author Nicole Zhang
	 */
	char getColor();

	//! Returns the object size
	/*!
	 * \return double size
	 *
	 * \author Nicole Zhang
	 */
	double getSize();

	//! Returns the object width
	/*!
	 * \return double width
	 *
	 * \author Nicole Zhang
	 */
	double getWidth();

	//! Returns the object's x-position
	/*!
	 * \return double x-position (in pixels)
	 *
	 * \author Nicole Zhang
	 */
	double getXLocation();

	//! Returns the object's y-position
	/*!
	 * \return double y-position
	 *
	 * \author Nicole Zhang
	 */
	double getYLocation();

	//! Returns the object's speed
	/*!
	 * \return double speed
	 *
	 * \author Nicole Zhang
	 */
	double getSpeed();

	//! Returns object orientation
	/*!
	 * \return double degrees
	 *
	 * \author Nicole Zhang
	 */
	double getOrientation();

	//! Returns the object's ID in the env PhysicalObject vector
	/*!
	 * \return integer ID
	 *
	 * \author Nicole Zhang
	 */
	int getID();

protected:

	ObjectType objType;
	char color;
	double size;
	double width;
	double location[2];
	double speed;
	double orientation;
	int id;
};

#endif

