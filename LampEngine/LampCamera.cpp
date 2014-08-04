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

void LampCamera::perspective(float fovY = 60.0f, float aspect = Lamp::getWindow().getAspect(), float zNear = 1.0f, float zFar = 100.0f)
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

vec3 makeFW(float pitch, float yaw)
{
	vec3 forward;
	forward.x = glm::sin(glm::radians(yaw));
	forward.y = glm::sin(glm::radians(-pitch));
	forward.z = glm::cos(glm::radians(yaw));
	forward = glm::normalize(forward);
	return forward;
}

void LampFreeCamera::calculateForward()
{
	forward = makeFW(rotation.x, rotation.y);
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

	//Move the camera according to button presses
	float moveSpeed = 0.1f;
	if (Lamp::getInput().isKeyDown(SDLK_w))
	{
		vec3 tmpForward = forward;
		tmpForward.y = 0.0f;
		position += tmpForward * moveSpeed;
	}
	if (Lamp::getInput().isKeyDown(SDLK_s))
	{
		vec3 tmpForward = forward;
		tmpForward.y = 0.0f;
		position -= tmpForward * moveSpeed;
	}
	if (Lamp::getInput().isKeyDown(SDLK_a))
	{
		//Strafe left :o
		vec3 left = makeFW(rotation.x, rotation.y + 90.0f);
		left.y = 0.0f;
		position += left * moveSpeed;
	}
	if (Lamp::getInput().isKeyDown(SDLK_d))
	{
		vec3 right = makeFW(rotation.x, rotation.y - 90.0f);
		right.y = 0.0f;
		position += right * moveSpeed;
	}
	if (Lamp::getInput().isKeyDown(SDLK_q))
	{
		position.y += moveSpeed;
	}
	if (Lamp::getInput().isKeyDown(SDLK_e))
	{
		position.y -= moveSpeed;
	}

	//update our view matrix!
	calculateForward();

	vec3 eye = position;
	vec3 target = eye + (forward * 10.0f);
	lookAt(eye, target);
}