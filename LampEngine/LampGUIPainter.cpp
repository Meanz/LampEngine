#include "stdafx.h"
#include "LampGUIPainter.hpp"

LampGUIPainter::LampGUIPainter()
{
	m_FontInitialized = false;
	m_Color = WHITE;
}

LampGUIPainter::~LampGUIPainter()
{
	m_DefaultFont.deleteFont();
}

LampColor& LampGUIPainter::getColor()
{
	return m_Color;
}

Area& LampGUIPainter::getDrawingArea()
{
	return m_Area;
}

void LampGUIPainter::setColor(LampColor color)
{
	m_Color = color;
}

//Not so sure about this
//Revise! 
//TODO: <- this makes my thingy find this
void LampGUIPainter::setDrawingArea(Area& area)
{
	m_Area = area;
}

void LampGUIPainter::drawRect(int x, int y, int width, int height)
{

}

void LampGUIPainter::fillRect(int x, int y, int width, int height)
{

}


void LampGUIPainter::drawQuad(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(x, y + h);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(x + w, y + h);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(x + w, y);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(x, y);
	}
	glEnd();
}


void LampGUIPainter::drawImage(std::string textureId, int x, int y)
{
	//Find the texture
	LampTexture* pTexture = Lamp::getAssetManager().getTexture(textureId);
	if (pTexture == NULL)
	{
		//Draw some default shit?
	}
	else
	{
		drawImage(pTexture, x, y);
	}
}

void LampGUIPainter::drawImage(std::string textureId, int x, int y, int width, int height)
{
	LampTexture* pTexture = Lamp::getAssetManager().getTexture(textureId);
	if (pTexture == NULL)
	{
		//Draw some default shit?
	}
	else
	{
		drawImage(pTexture, x, y, width, height);
	}
}

void LampGUIPainter::drawImage(LampTexture* pTexture, int x, int y)
{
	drawImage(pTexture, x, y, pTexture->m_Width, pTexture->m_Height);
}

void LampGUIPainter::drawImage(LampTexture* pTexture, int x, int y, int width, int height)
{

	//Force coloring
	applyColor(m_Color);

	//Enable texturing
	glEnable(GL_TEXTURE_2D);

	//Bind our texture
	pTexture->bind();

	//Draw our quad
	drawQuad(x, y, width, height);

}

void LampGUIPainter::drawString(std::string str, int x, int y)
{
	//Force coloring
	applyColor(m_Color);

	if (!m_FontInitialized)
	{
		//Initialize our default font :D
		m_DefaultFont.loadFont("./data/fonts/ITCKRIST.ttf", 11);
		m_FontInitialized = true;
	}
	m_DefaultFont.draw(str, x, y);
}


