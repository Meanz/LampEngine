#pragma once
#include "stdafx.h"

namespace LampProject
{

	class LampWindow
	{
	private:
		int m_Width;
		int m_Height;
		std::string m_title;

		SDL_Window* m_pSDL_Window;

	public:

		LampWindow(int width, int height, std::string title, SDL_Window* pSDL_Window) :
			m_Width(width),
			m_Height(height),
			m_title(title),
			m_pSDL_Window(pSDL_Window)
		{
			
		}

		int getWidth() 
		{
			return m_Width;
		}

		int getHeight()
		{
			return m_Height;
		}

		int getCenterX()
		{
			return m_Width / 2;
		}

		int getCenterY()
		{
			return m_Height / 2;
		}

		double getAspect()
		{
			return (double)m_Width / (double)m_Height;
		}

		SDL_Window* getSDLWindow()
		{
			return m_pSDL_Window;
		}
	};

}