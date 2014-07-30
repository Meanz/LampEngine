#pragma once

//SDL
#include "stdafx.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

namespace LampProject {

	struct SDLConfig
	{

		int width;
		int height;
		std::string title;

	};

	class SDLWrapper
	{

	private:
		SDL_Window* m_pWindow;
		SDL_GLContext m_gContext;
		SDLConfig m_config;

	public:
		SDLWrapper(SDLConfig config);
		~SDLWrapper();

		bool init();

		void swapBuffers();
	};

}