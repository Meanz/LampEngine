#include "stdafx.h"
#include "LampInput.hpp"


LampInput::LampInput()
{
	for (unsigned int i = 0; i < MAX_MOUSE_BUTTONS; i++)
	{
		m_bMouseButtons[i] = false;
	}
	resetKeys();

	m_centerMouse = false;
	m_ignoreNextMouseMotion = false;
}

LampInput::~LampInput()
{

}

bool LampInput::isMouseCentered()
{
	return m_centerMouse;
}

void LampInput::setCenterMouse(bool centerMouse)
{
	SDL_SetRelativeMouseMode((SDL_bool)centerMouse);
	m_centerMouse = centerMouse;
	if (centerMouse) m_ignoreNextMouseMotion = true;
}

void LampInput::resetKeys()
{
	for (unsigned int i = 0; i < MAX_VIRTUAL_KEYS; i++)
	{
		m_bKeys[i] = false;
	}
}

void LampInput::addMouseListener(LampMouseListener* pListener)
{
	m_vMouseListeners.push_back(pListener);
}

void LampInput::addKeyListener(LampKeyListener* pKeyListener)
{
	m_vKeyListeners.push_back(pKeyListener);
}

int LampInput::getMouseX()
{
	return m_lastMouseX;
}

int LampInput::getMouseY()
{
	return m_lastMouseY;
}

int LampInput::getMouseDX()
{
	return m_deltaMouseX;
}

int LampInput::getMouseDY()
{
	return m_deltaMouseY;
}

bool LampInput::isKeyPressed(int vKey)
{
	if (m_vKeysPressed.size() == 0) return false;
	for (unsigned int i = 0; i < m_vKeysPressed.size(); i++)
	{
		if (m_vKeysPressed[i] == vKey) return true;
	}
	return false;
}

bool LampInput::isKeyReleased(int vKey)
{
	if (m_vKeysReleased.size() == 0) return false;
	for (unsigned int i = 0; i < m_vKeysReleased.size(); i++)
	{
		if (m_vKeysReleased[i] == vKey) return true;
	}
	return false;
}

bool LampInput::isKeyDown(int vKey)
{
	if (vKey >= MAX_VIRTUAL_KEYS) return false;
	return m_bKeys[vKey];
}

void LampInput::pollInput()
{

	//Clear old states
	m_vKeysPressed.clear();
	m_vKeysReleased.clear();

	//SDL_CHECKS
	SDL_Event event;

	//!
	m_deltaMouseX = 0;
	m_deltaMouseY = 0;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			//Hehe
		}
		else if (event.type == SDL_TEXTINPUT)
		{
		}
		else if (event.type == SDL_KEYDOWN)
		{
			int vKey = event.key.keysym.sym;
			if (vKey >= MAX_VIRTUAL_KEYS) continue; //Ignore event
			m_vKeysPressed.push_back(vKey);
			m_bKeys[vKey] = true;
		}
		else if (event.type == SDL_KEYUP)
		{
			int vKey = event.key.keysym.sym;
			if (vKey >= MAX_VIRTUAL_KEYS) continue; //Ignore event
			m_vKeysReleased.push_back(vKey);
			m_bKeys[vKey] = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{

		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			
			if (m_ignoreNextMouseMotion)
			{
				m_ignoreNextMouseMotion = false;
				continue;
			}

			LampMouseEvent _event;

			_event.mouseX = event.motion.x;
			_event.mouseY = event.motion.y;

			//Add deltas!
			m_deltaMouseX += event.motion.xrel;
			m_deltaMouseY += event.motion.yrel;

			_event.deltaX = m_deltaMouseX;
			_event.deltaY = m_deltaMouseY;


			for (unsigned int i = 0; i < m_vMouseListeners.size(); i++)
			{
				m_vMouseListeners[i]->onMouseMove(_event);
			}
		}

		//Update mouse position!
		int x = 0, y = 0;
		SDL_GetMouseState(&x, &y);
		m_lastMouseX = x;
		m_lastMouseY = y;
	}

	//Process input updates
}