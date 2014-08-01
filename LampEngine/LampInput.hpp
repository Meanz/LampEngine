#pragma once
#include "stdafx.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

namespace LampProject
{
	//Enum for mouse buttons
	enum LampMouseButton
	{
		MB_LMB = 0,
		MB_RMB = 1,
		MB_MIDDLE = 2,
		MB_KEY1 = 3,
		MB_KEY2 = 4
	};

	//General mouse event
	struct LampMouseEvent
	{
		int mouseX;
		int mouseY;
		int deltaX;
		int deltaY;
	};

	//A structure for mouse click events
	struct LampMouseClickEvent : public LampMouseEvent
	{
		LampMouseButton button; //The button that was pressed
		bool pressed; //Whether the button was pressed or released
	};

	//A structure for key events
	struct LampKeyEvent
	{
		char keyCode;
		int keyIdThingy;
		std::string keyToStr;
	};

	//
	// A simple mouse listener interface
	//
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

	//
	// a simple key listener interface
	//
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

		//Check if the mouse is centered
		bool isMouseCentered();

		//Toggle whether to center mouse or not, will also hide the mouse on true
		void setCenterMouse(bool centerMouse);

		//Internal function for setting all key pressed to false
		void resetKeys();

		//Add a mouse listener
		void addMouseListener(LampMouseListener* pListener);

		//Add a key listener
		void addKeyListener(LampKeyListener* pKeyListener);

		//Get the mouse x position
		int getMouseX();

		//Get the mouse y position
		int getMouseY();

		//Get the mouse delta x position
		int getMouseDX();

		//Get the mouse delta y position
		int getMouseDY();

		//Check whether the given virtual key was pressed this frame
		bool isKeyPressed(int vKey);

		//Check whether the given virtual key was released this frame
		bool isKeyReleased(int vKey);

		//Check whether a key is being held down/pressed
		bool isKeyDown(int vKey);

		//Internal function used for polling the mouse/keyboard status
		void pollInput();

	};
}