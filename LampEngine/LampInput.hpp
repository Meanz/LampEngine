#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

namespace LampProject
{
	enum LampMouseButton
	{
		MB_LMB = 0,
		MB_RMB = 1,
		MB_MIDDLE = 2,
		MB_KEY1 = 3,
		MB_KEY2 = 4
	};

	struct LampMouseEvent
	{
		int mouseX;
		int mouseY;
		int deltaX;
		int deltaY;
	};

	struct LampMouseClickEvent : public LampMouseEvent
	{
		LampMouseButton button; //The button that was pressed
		bool pressed; //Whether the button was pressed or released
	};

	struct LampKeyEvent
	{
		char keyCode;
		int keyIdThingy;
		std::string keyToStr;
	};

	class LampMouseListener
	{
	private:

	public:

		//Mouse press event
		virtual void onMousePressed(LampMouseClickEvent) {}; //No default implementation

		//Mouse release event
		virtual void onMouseReleased(LampMouseClickEvent) {}

		//Mouse move event
		virtual void onMouseMove(LampMouseEvent) {}
	};

	class LampKeyListener
	{
	private:

	public:

		virtual void onKeyPressed(LampKeyEvent) {} //Default impls
		virtual void onKeyReleased(LampKeyEvent) {} //Default impls

	};

	class LampInput
	{

#define MAX_MOUSE_BUTTONS 20 
#define MAX_VIRTUAL_KEYS 322

	private:

		std::vector<LampMouseListener*> m_vMouseListeners;
		std::vector<LampKeyListener*> m_vKeyListeners;

		bool m_bMouseButtons[MAX_MOUSE_BUTTONS];

		std::vector<int> m_vKeysPressed;
		std::vector<int> m_vKeysReleased;
		bool m_bKeys[MAX_VIRTUAL_KEYS];

		int m_lastMouseX;
		int m_lastMouseY;
		int m_deltaMouseX;
		int m_deltaMouseY;

	public:

		LampInput()
		{
			for (unsigned int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_bMouseButtons[i] = false;
			}
			resetKeys();
		}

		~LampInput()
		{

		}

		void resetKeys()
		{
			for (unsigned int i = 0; i < MAX_VIRTUAL_KEYS; i++)
			{
				m_bKeys[i] = false;
			}
		}

		void addMouseListener(LampMouseListener* pListener)
		{
			m_vMouseListeners.push_back(pListener);
		}

		void addKeyListener(LampKeyListener* pKeyListener)
		{
			m_vKeyListeners.push_back(pKeyListener);
		}

		int getMouseX() 
		{
			return m_lastMouseX;
		}

		int getMouseY()
		{
			return m_lastMouseY;
		}

		int getMouseDX()
		{
			return m_deltaMouseX;
		}

		int getMouseDY()
		{
			return m_deltaMouseY;
		}

		bool isKeyPressed(int vKey) 
		{
			if (m_vKeysPressed.size() == 0) return false;
			for (unsigned int i = 0; i < m_vKeysPressed.size(); i++)
			{
				if (m_vKeysPressed[i] == vKey) return true;
			}
			return false;
		}

		bool isKeyReleased(int vKey)
		{
			if (m_vKeysReleased.size() == 0) return false;
			for (unsigned int i = 0; i < m_vKeysReleased.size(); i++)
			{
				if (m_vKeysReleased[i] == vKey) return true;
			}
			return false;
		}

		bool isKeyDown(int vKey)
		{
			if (vKey >= MAX_VIRTUAL_KEYS) return false;
			return m_bKeys[vKey];
		}

		void pollInput()
		{
			//Calculate DX and DY
			//Just do it, okay.
			int x = 0, y = 0;
			SDL_GetMouseState(&x, &y);

			//TODO: Revise solution
			m_deltaMouseX = m_lastMouseX - x;
			m_deltaMouseY = m_lastMouseY - y;
			m_lastMouseX = x;
			m_lastMouseY = y;

			//Clear old states
			m_vKeysPressed.clear();
			m_vKeysReleased.clear();

			//SDL_CHECKS
			SDL_Event event;

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
					m_vKeysPressed.push_back(vKey);
					m_bKeys[vKey] = true;
				}
				else if (event.type == SDL_KEYUP)
				{
					int vKey = event.key.keysym.sym;
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
					LampMouseEvent _event;

					_event.mouseX = event.motion.x;
					_event.mouseY = event.motion.y;
					_event.deltaX = m_deltaMouseX;
					_event.deltaY = m_deltaMouseY;

					for (unsigned int i = 0; i < m_vMouseListeners.size(); i++)
					{
						m_vMouseListeners[i]->onMouseMove(_event);
					}
				}
			}

			//Process input updates

		}

	};
}