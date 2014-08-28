#include "stdafx.h"
#include "LampGUI.hpp"

LampGUI::LampGUI()
{
	m_pWindow = new LampComponent();
	Area windowArea(0, 0, Lamp::getWindow().getWidth(), Lamp::getWindow().getHeight());
	m_pWindow->setArea(windowArea);
}

LampGUI::~LampGUI()
{
	//Delete our main window and all it's sub components! Not really needed since it's vmem
	//BUT WE DO IT NEWAYS OKAY!??!???!?!?!?
	delete m_pWindow;
}

LampGUIPainter& LampGUI::getPainter()
{
	return m_Painter;
}

void LampGUI::add(LampComponent* pComponent)
{
	m_pWindow->add(pComponent);
}

void LampGUI::remove(LampComponent* pComponent)
{
	m_pWindow->remove(pComponent);
}

void LampGUI::onTick()
{

	//Tell our main component to update all it's sub components
	m_pWindow->doTick();

}

void LampGUI::onFrame()
{

	//Tell our main component that it's drawing time :D
	m_pWindow->doDraw(m_Painter);

}