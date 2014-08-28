#pragma once

#include "stdafx.h"
#include "LampComponent.hpp"

namespace LampProject 
{

	class LampGUI
	{

	private:

		//Basically a placeholder component for our window, or "root" component :p
		LampComponent* m_pWindow;
		//Our GUI painter!
		LampGUIPainter m_Painter;

	public:

		LampGUI();
		~LampGUI();

		LampGUIPainter& getPainter();

		void add(LampComponent* pComponent);
		void remove(LampComponent* pComponent);

		//This be very important mr houston
		void onTick();
		void onFrame();

	};

}