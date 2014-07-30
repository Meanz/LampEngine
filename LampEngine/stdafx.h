// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// TODO: reference additional headers your program requires here

//Cstring
#include <string>

//Windows stuff
#include <Windows.h>

//Glew
#include <GL\glew.h>
//OpenGL
#include <gl\GL.h>

//For asserting
#include <assert.h>

//OpengGL Mathematics (GLM)(v0.9.5.2)
#include <glm.hpp>

//A configuration structure for the lamp engine
struct LampConfig {

	int width;
	int height;
	std::string title;
	int targetUpdatesPerSecond;
	bool vsync;

	LampConfig() 
	{
		width = 800;
		height = 640;
		title = "Untitled Application";
		targetUpdatesPerSecond = 60;
		vsync = false;
	}

};

//Include types
#include "LampTypes.hpp"

//Main thingy, it will include the rest, yeyes
#include "Lamp.hpp"

//Woah!
using namespace LampProject;