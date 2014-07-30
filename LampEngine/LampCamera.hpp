#pragma once

#include "stdafx.h"

namespace LampProject
{
	//Not sure whether to add this as a node or not
	//I mean, sure that could work, and I've seen it in many other engines
	//But personally I think the camera should be something unique
	//So, well I'll create the camera as if it was unique
	//It's going to be referenced in the scene anyways.
	//so it's not really hard to make changes to it.


	class LampCamera
	{

	private:
		LampTransform m_transform;
		mat4 m_projectionMatrix;

	public:

		LampCamera() :
			m_transform(),
			m_projectionMatrix(1.0f)
		{

		}

		void perspective(float fovY, float aspect, float zNear, float zFar)
		{
			m_projectionMatrix = glm::perspective(fovY, aspect, zNear, zFar);
		}

		void ortho2D(float left = 0, float right = Lamp::getWindow().getWidth(), float bottom = Lamp::getWindow().getHeight(), float top = 0)
		{
			m_projectionMatrix = glm::ortho(left, right, bottom, top);
		}

		mat4 getProjectionMatrix()
		{
			return m_projectionMatrix;
		}

		mat4 getViewMatrix()
		{
			return m_transform.getGlobal();
		}

		void onTick() 
		{
			//Calculate the view matrix every frame :p
			//Or in this case, 60 times per second.
			
			m_transform.calculateGlobal(mat4(1.0f));
		}


	};


}