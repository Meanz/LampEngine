#include "stdafx.h"
#include "LampTexture.hpp"

LampTexture::LampTexture() :
m_glId(0)
{

}

LampTexture::~LampTexture()
{
	if (m_glId > 0)
	{
		glDeleteTextures(1, &m_glId);
	}
}

bool LampTexture::isValid()
{
	return m_glId > 0;
}

int LampTexture::getGLId()
{
	return m_glId;
}

void LampTexture::generateGLId()
{
	assert(m_glId == 0); //it should be 0!
	glGenTextures(1, &m_glId);
}

void LampTexture::bind()
{
	assert(m_glId != 0); //it should be 0!
	glBindTexture(GL_TEXTURE_2D, m_glId);
}
