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

//SDL
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

//OpengGL Mathematics (GLM)(v0.9.5.2)
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Utility class
#include "LampUtil.hpp"

//Include types
#include "LampTypes.hpp"

//Our transformation ckass
#include "LampTransform.hpp"

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



//Main thingy, it will include the rest, yeyes
#include "Lamp.hpp"

//Woah!
using namespace LampProject;