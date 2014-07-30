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

	public:

		LampWindow(int width, int height, std::string title) :
			m_width(width),
			m_height(height),
			m_title(title)
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

		double getAspect()
		{
			return (double)m_width / (double)m_height;
		}

	};

}