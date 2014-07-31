#include "stdafx.h"
#include "LampCamera.hpp"

LampCamera::LampCamera() :
m_projectionMatrix(1.0f),
m_viewMatrix(1.0f)
{
}

LampCamera::~LampCamera()
{

}

void LampCamera::perspective(float fovY = 60.0f, float aspect = Lamp::getWindow().getAspect(), float zNear = 0.0f, float zFar = 100.0f)
{
	m_projectionMatrix = glm::perspective(glm::radians(fovY), aspect, zNear, zFar);
}

void LampCamera::ortho2D(float left = 0, float right = Lamp::getWindow().getWidth(), float bottom = Lamp::getWindow().getHeight(), float top = 0)
{
	m_projectionMatrix = glm::ortho(left, right, bottom, top);
}

void LampCamera::lookAt(vec3 eye, vec3 center)
{
	m_viewMatrix = glm::lookAt(eye, center, UNIT_Y);
}

mat4& LampCamera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

mat4& LampCamera::getViewMatrix()
{
	return m_viewMatrix;
}


void LampCamera::onTick()
{

	//Calculate the view matrix every frame :p
	//Or in this case, 60 times per second.
	onCameraUpdate();
}

void LampCamera::applyLegacyTransform()
{

	//should this be used?
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(m_viewMatrix));
}


LampFreeCamera::LampFreeCamera() : LampCamera()
{
	//Nothing to initialize I think
	position = vec3(-5.0f, 5.0f, -5.0f);
}

void LampFreeCamera::calculateForward()
{
	forward.x = glm::sin(glm::radians(rotation.y));
	forward.y = glm::sin(glm::radians(-rotation.x));
	forward.z = glm::cos(glm::radians(rotation.y));
	forward = glm::normalize(forward);
}

void LampFreeCamera::onCameraUpdate()
{
	//Process mouse info
	if (Lamp::getInput().isMouseCentered())
	{
		int dx = -Lamp::getInput().getMouseDX();
		int dy = Lamp::getInput().getMouseDY();
		rotation.x += dy * 0.1f;
		rotation.y += dx * 0.1f; //Some weird value :D
	}
	//update our view matrix!
	calculateForward();

	vec3 eye = position;
	vec3 target = eye + (forward * 10.0f);
	lookAt(eye, target);
}