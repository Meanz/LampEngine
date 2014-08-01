#pragma once

#include "LampApplication.hpp"
#include "LampAssetManager.hpp"
#include "LampScene.hpp"
#include "LampWindow.hpp"
#include "LampRenderer.hpp"
#include "LampInput.hpp"
#include "SDLWrapper.h"
#include "stdafx.h"

namespace LampProject {
	
	//This is the class that handles all the magic
	//Magic goes here
	class LampEngine
	{

	private:
		//The application that the engine is forwarding calls to
		SDLWrapper* m_pWrapper;
		LampConfig m_config;
		LampApplication* m_pApplication;
		LampScene* m_pScene;
		LampWindow* m_pWindow;
		LampAssetManager* m_pAssetManager;
		LampRenderer* m_pRenderer;
		LampInput* m_pInput;

		//Whether the engine is running or not
		bool m_isRunning;

		//The core loop
		void loop();

	public:

		LampEngine(LampApplication* pApplication, LampConfig config);
		~LampEngine();

		void postConstructor();

		//Get the input class
		LampInput* getInput()
		{
			return m_pInput;
		}

		//Get the renderer for this engine
		LampRenderer* getRenderer()
		{
			return m_pRenderer;
		}

		//Get the window for this engine
		LampWindow* getWindow()
		{
			return m_pWindow;
		}

		//Get the scene for this engine
		LampScene* getScene() 
		{
			return m_pScene;
		}

		//Get the asset manager for this engine
		LampAssetManager* getAssetManager() 
		{
			return m_pAssetManager;
		}

		//Starts the engine
		void start();

		//Stops the engine and frees all resources
		void stop();

	};

}