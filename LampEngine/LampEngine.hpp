#pragma once

#include "LampApplication.hpp"
#include "LampScene.hpp"
#include "LampAssetManager.hpp"
#include "LampWindow.hpp"
#include "LampRenderer.hpp"
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

		//The core loop
		void loop();

	public:

		LampEngine(LampApplication* pApplication, LampConfig config);
		~LampEngine();

		LampRenderer* getRenderer()
		{
			return m_pRenderer;
		}

		LampWindow* getWindow()
		{
			return m_pWindow;
		}

		LampScene* getScene() 
		{
			return m_pScene;
		}

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