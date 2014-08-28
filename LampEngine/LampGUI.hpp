#pragma once

#include "stdafx.h"
#include "LampComponent.hpp"

namespace LampProject 
{

	class LampGUI : public LampGameObject
	{

	private:

		//Basically a placeholder component for our window, or "root" component :p
		LampComponent* m_pWindow;
		//Our GUI painter!
		LampGUIPainter m_Painter;

	public:

		LampGUI();
		~LampGUI();

		//This be very important mr houston
		virtual void onTick();
		virtual void onFrame();

	};

}