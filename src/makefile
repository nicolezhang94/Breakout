UNAME = $(shell uname)

CC = g++
CFLAGS = -Wall -m64
LDFLAGS =

##
# List of cpp files to be compiled
# Note, if you add any cpp files to your project, you must also add them here
##
CPPFILES += main.cpp
CPPFILES += BaseGfxApp.cpp
CPPFILES += Simulation.cpp
CPPFILES += PhysicalObjectClass.cpp
CPPFILES += EnvironmentClass.cpp
CPPFILES += RenderingWindowClass.cpp

##
# Lists all the cpp files in /src
# Note, this means you can make from /src, /lib, or /bin
##
SOURCES=$(addprefix ../src/, $(CPPFILES))

OBJECTS = $(addprefix ../bin/, $(CPPFILES:.cpp=.o))

GLUI = glui

##
# Linking the GLUI libraries
##
LINK_LIBS += -L../lib/$(GLUI)/lib/ -lglui
INCLUDE = -I../lib/$(GLUI)/include/ -I../src

##
# Linking GLUT and OpenGl for Mac
##
ifeq ($(UNAME), Darwin)
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = ../bin/gorobot
##
# Linking GLUT and OpenGl for Linux
##
else
ifeq ($(UNAME), Linux)
	LINK_LIBS += -lglut -lGL -lGLU -lpthread
	EXECUTABLE = ../bin/gorobot
##
# Linking GLUT and OpenGl for Windows
# Note, you must have freeGlut installed; see the Resource page for details
##
else
	GLUTINCLUDEPATH = C:\Dev-Cpp\mingw32\freeglut\include\
	GLUTLIBPATH = C:\Dev-Cpp\mingw32\freeglut\lib\
	LINK_LIBS += -L$(GLUTLIBPATH) -lfreeglut -lopengl32 -Wl,--subsystem,windows
	INCLUDE += -I$(GLUTPATH)
	EXECUTABLE = gorobot.exe

endif
endif

##
# Sets up the /bin folder, checks for all cpp files, and compiles the executable
##
all: setup $(SOURCES) gorobot

setup:
	mkdir -p ../bin

gorobot: $(GLUI) $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINK_LIBS) -o $(EXECUTABLE)

##
# This creates the object files in the /bin folder
##
../bin/%.o: ../src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -rf test.cpp $(OBJECTS) $(EXECUTABLE)
	rm -f *~
	$(MAKE) -C ../lib/$(GLUI) clean

$(GLUI):
	$(MAKE) -C ../lib/$(GLUI) all
