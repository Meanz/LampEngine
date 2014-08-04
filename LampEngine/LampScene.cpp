#include "stdafx.h"
#include "LampScene.hpp"


LampScene::LampScene()
{
	m_pRootNode = new LampGameObject();
	m_pMainCamera = new LampFreeCamera();
	m_pMainCamera->perspective(60.0f, (float)Lamp::getWindow().getAspect(), 1.0f, 100.0f);
}

LampScene::~LampScene()
{
	delete m_pRootNode;
}

void LampScene::setCamera(LampCamera* pCamera)
{
	m_pMainCamera = pCamera;
}

LampGameObject* LampScene::getRoot()
{
	return m_pRootNode;
}

LampCamera* LampScene::getCamera()
{
	return m_pMainCamera;
}

void LampScene::attach(LampGameObject* child)
{
	m_pRootNode->attach(child);
}

void LampScene::detatch(LampGameObject* child)
{
	m_pRootNode->detach(child);
}

void LampScene::onTick()
{
	m_pRootNode->doTick();
	m_pMainCamera->onTick(); //Update camera :D
}

void LampScene::onFrame()
{
	m_pRootNode->doFrame();
}