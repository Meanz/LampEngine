#include "stdafx.h"
#include "LampRenderer.hpp"


LampRenderer::LampRenderer() :
m_clearColor(BLUE)
{

}

LampRenderer::~LampRenderer()
{

}

void LampRenderer::render()
{
	//Clear :D
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}