#pragma once

#include "stdafx.h"

namespace LampProject
{

	class LampGUIPainter
	{

	private:

		//The area this painter is currently drawing on
		Area m_Area;

		//The color this painter is currently drawing with
		LampColor m_Color;

	public:

		//Get the drawing area this painter is currently painting on
		Area& getDrawingArea();

		//Set the drawing area of this painter
		void setDrawingArea(Area& area);

		//Get the color being used by this painter
		LampColor& getColor();

		//Set the color being used by this painter
		void setColor(LampColor color);

		//Draw a rectangle
		void drawRect(int x, int y, int width, int height);

		//Fill a rectangle
		void fillRect(int x, int y, int width, int height);

	};

}