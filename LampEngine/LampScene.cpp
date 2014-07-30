#include "stdafx.h"
#include "LampScene.hpp"


LampScene::LampScene()
{
	m_pRootNode = new LampGameObject();
}

LampScene::~LampScene()
{
	delete m_pRootNode;
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
}

void LampScene::onFrame()
{
	//renderer->doRender();
	m_pRootNode->doFrame();
}