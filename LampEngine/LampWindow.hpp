#pragma once
#include "stdafx.h"

namespace LampProject
{

	class LampWindow
	{
	private:
		int m_width;
		int m_height;
		std::string m_title;

		SDL_Window* m_pSDL_Window;

	public:

		LampWindow(int width, int height, std::string title, SDL_Window* pSDL_Window) :
			m_width(width),
			m_height(height),
			m_title(title),
			m_pSDL_Window(pSDL_Window)
		{
			
		}

		int getWidth() 
		{
			return m_width;
		}

		int getHeight()
		{
			return m_height;
		}

		int getCenterX()
		{
			return m_width / 2;
		}

		int getCenterY()
		{
			return m_height / 2;
		}

		double getAspect()
		{
			return (double)m_width / (double)m_height;
		}

		SDL_Window* getSDLWindow()
		{
			return m_pSDL_Window;
		}
	};

}