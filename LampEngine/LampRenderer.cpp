#include "stdafx.h"
#include "LampRenderer.hpp"


LampRenderer::LampRenderer() :
m_clearColor(BLUE)
{

}

LampRenderer::~LampRenderer()
{

}

void LampRenderer::setTransform(LampTransform* pTransform)
{
	m_pTransform = pTransform;
}

mat4& LampRenderer::getTransform()
{
	m_pWorldMatrix = new mat4();
	*m_pWorldMatrix = (Lamp::getScene().getCamera()->getViewMatrix() * m_pTransform->getGlobal());
	return *m_pWorldMatrix;
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

	//Do GUI Rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, Lamp::getWindow().getWidth(), Lamp::getWindow().getHeight(), 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Disable depth testing
	//Enable Texturing
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	//Draw debug!
	std::string fps = "FPS: ";
	
	char buffer[8];
	_itoa_s(Lamp::getEngine().getFPS(), buffer, 4);
	fps.append(buffer);

	Lamp::getGUI().getPainter().setColor(WHITE);
	Lamp::getGUI().getPainter().drawString(fps, 10, 10);

	Lamp::getScene().onGUI();
}