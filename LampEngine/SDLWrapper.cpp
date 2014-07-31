#include "stdafx.h"
#include "SDLWrapper.h"


SDLWrapper::SDLWrapper(SDLConfig config) :
m_pWindow(0),
m_config(config)
{
}

SDLWrapper::~SDLWrapper()
{

	IMG_Quit();
	SDL_Quit();
}

void SDLWrapper::swapBuffers()
{
	SDL_GL_SwapWindow(m_pWindow);
}

bool SDLWrapper::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//reportFatalError("Could not initialize window. Aborting!", SDL_GetError());
		return false;
	}
	else
	{
		//Attempt to init SDL Image
		// load support for the JPG and PNG image formats
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted & flags) != flags) {
			printf("IMG_Init: Failed to init required jpg and png support!\n");
			printf("IMG_Init: %s\n", IMG_GetError());
			// handle error
			return false;
		}

		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create window
		m_pWindow = SDL_CreateWindow(m_config.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_config.width, m_config.height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (m_pWindow == NULL)
		{
			//reportFatalError("Window could not be created!", SDL_GetError());
			return false;
		}
		else
		{
			//Create context
			m_gContext = SDL_GL_CreateContext(m_pWindow);
			if (m_gContext == NULL)
			{
				//reportFatalError("OpenGL context could not be created!", SDL_GetError());
				return false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Everything went fine
				return true;
			}
		}
	}
}