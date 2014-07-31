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

		bool m_centerMouse;
		bool m_ignoreNextMouseMotion;

	public:

		LampInput();

		~LampInput();

		bool isMouseCentered();

		void setCenterMouse(bool centerMouse);

		void resetKeys();

		void addMouseListener(LampMouseListener* pListener);

		void addKeyListener(LampKeyListener* pKeyListener);

		int getMouseX();

		int getMouseY();

		int getMouseDX();

		int getMouseDY();

		bool isKeyPressed(int vKey);

		bool isKeyReleased(int vKey);

		bool isKeyDown(int vKey);

		void pollInput();

	};
}