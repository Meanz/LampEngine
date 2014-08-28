#pragma once

#include "stdafx.h"
#include "LampFontRenderer.hpp"

namespace LampProject
{

	class LampGUIPainter
	{

	private:

		//The area this painter is currently drawing on
		Area m_Area;

		//The color this painter is currently drawing with
		LampColor m_Color;

		LampFont m_DefaultFont;
		bool m_FontInitialized;

		//Draw an opengl quad
		void drawQuad(GLfloat x, GLfloat y, GLfloat w, GLfloat h);

	public:

		LampGUIPainter();
		~LampGUIPainter();

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

		//Draw the given image at x,y
		void drawImage(std::string textureId, int x, int y);

		//Draw the given image at x,y with dimensions width and height
		void drawImage(std::string textureId, int x, int y, int width, int height);

		//Draw the given image at x,y
		void drawImage(LampTexture* pTexture, int x, int y);

		//Draw the given image at x,y with dimensions width and height
		void drawImage(LampTexture* pTexture, int x, int y, int width, int height);

		//Draw a string at the given x,y coordinates
		void drawString(std::string, int x, int y);

	};

}