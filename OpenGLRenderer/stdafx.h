// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"


#undef min
#undef max

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <math.h>
#include <string>

////OPENGL includes
//#include <GL/gl.h>
//#include <GL/glu.h>

////GLEW
//#define GLEW_STATIC
//#include "../../3rd-party/glew-2.0.0/src/glew.h"


//GLUT
#define FREEGLUT_STATIC 1
#define FREEGLUT_LIB_PRAGMAS 0
#include "../freeglut3/include/GL/freeglut.h"
#pragma comment (lib,"opengl32.lib")

//tinyxml2
#include "../tinyxml2/tinyxml2.h"
using namespace tinyxml2;

//SOIL
#include "../SOIL/src/SOIL.h"