#pragma once
#include "stdafx.h"


namespace LampProject
{

	class LampRenderer
	{

	private:
		LampColor m_clearColor;
		LampTransform* m_pTransform;
		mat4* m_pWorldMatrix;

	public:
		
		LampRenderer();
		~LampRenderer();
	
		void setTransform(LampTransform* pTransform);
		mat4& getTransform(); //Get a reference to the current transform

		//Calls the render function!
		void render(LampGameObject* pRenderNode);

	};


}