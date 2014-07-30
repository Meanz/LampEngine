#pragma once
#include "stdafx.h"


namespace LampProject
{

	class LampRenderer
	{

	private:
		LampColor m_clearColor;


	public:
		
		LampRenderer();
		~LampRenderer();

		//Calls the render function!
		void render();

	};


}