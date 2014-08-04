#include "stdafx.h"
#include "LampRenderer.hpp"


LampRenderer::LampRenderer() :
m_clearColor(BLUE)
{

}

LampRenderer::~LampRenderer()
{

}

void LampRenderer::render(LampGameObject* pRenderNode)
{
	//Clear :D
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Oh lawd
	//This kills it all :o?
	glEnable(GL_DEPTH_TEST);

	//Do legacy matrix loading
	//Do some 3d rendering, cus is cool
	LampCamera* pMainCamera = Lamp::getScene().getCamera();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(&pMainCamera->getProjectionMatrix()[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(&pMainCamera->getViewMatrix()[0][0]);

	//Render all nodes
	pRenderNode->doFrame();
}