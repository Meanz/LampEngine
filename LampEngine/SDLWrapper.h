#pragma once

//SDL
#include "stdafx.h"

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

		SDL_Window* getWindow();

		bool init();

		void swapBuffers();
	};

}