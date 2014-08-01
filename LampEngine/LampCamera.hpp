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
		mat4 m_projectionMatrix;
		mat4 m_viewMatrix;

	public:

		LampCamera();
		~LampCamera();

		void perspective(float fovY, float aspect, float zNear, float zFar);

		void ortho2D(float left, float right, float bottom, float top);

		void lookAt(vec3 eye, vec3 center);

		mat4* getPM()
		{
			return &m_projectionMatrix;
		}

		mat4* getV()
		{
			return &m_viewMatrix;
		}

		mat4& getProjectionMatrix();

		mat4& getViewMatrix();

		void onTick();

		virtual void onCameraUpdate() {}; //Nothing here

		void applyLegacyTransform();

	};
	
	class LampChaseCamera : public LampCamera
	{

	};

	class LampFreeCamera : public LampCamera
	{
	private:

		vec3 position;
		vec3 rotation;

		vec3 forward;

	public:
		LampFreeCamera();

		void calculateForward();
		virtual void onCameraUpdate();
	};

}