#pragma once

#include "LampEngine.hpp"
#include "LampLua.hpp"

#include <stdio.h>
#include <iostream>

namespace LampProject {

	//This class basically acts as a static getter for 
	//all the common components of the engine.
	//
	//This is done in order to allow all components to access most parts of the engine
	//While there are up's and down's with this design pattern, it's very strong
	//And does not require some well planned interfacing structure.
	class Lamp {

	private:

		//Instance holder
		//Had to make a copy, since I want to know if 
		//m_pEngine has been initialized or not
		static Lamp& internal_get() {
			static Lamp instance;
			return instance;
		}

		//Reference to our engine
		LampEngine* m_pEngine;
		LampLua* m_pLua;

		Lamp() : m_pEngine(0), m_pLua(0) {};
		Lamp(Lamp const&);
		void operator=(Lamp const&);

	public:

		//Get a reference to the Lamp object
		//This is mostly only used by internal components?
		//TODO: consider whether this should be private or not
		static Lamp& get()
		{
			//You need to initialize before we start doing stuff :o
			assert(internal_get().m_pEngine != 0);
			return internal_get();
		}

		//Initializes the engine and associates the application given with the engine
		//start becomes available, same with stop
		static void initialize(LampApplication* pApplication, LampConfig config)
		{
			assert(internal_get().m_pEngine == 0);
			assert(pApplication > 0);

			//Create our lua object!
			internal_get().m_pLua = new LampLua();

			//Create our engine object
			internal_get().m_pEngine = new LampEngine(pApplication, config);
			internal_get().m_pEngine->postConstructor(); //Will do work!
		}

		//Starts the engine
		static void start()
		{
			getEngine().start(); //Will throw if the engine has not been initialized
		}

		//Stops the engine, clears all resources
		static void stop()
		{
			getEngine().stop(); //Will throw if the engine has not been initialized
		}

		static void onEngineQuit()
		{
			printf("Engine shutdown.");
			
			std::cin.get();

			//Delete engine and lua?
			delete internal_get().m_pLua;
			delete internal_get().m_pEngine;
		}

		static LampLua& getLua() 
		{
			return *get().m_pLua;
		}

		//Get the input object
		static LampInput& getInput()
		{
			return *getEngine().getInput();
		}
		
		//Get the Window
		static LampWindow& getWindow()
		{
			return *getEngine().getWindow();
		}

		//Get the AssetManager
		static LampAssetManager& getAssetManager() {
			return *getEngine().getAssetManager();
		}

		//Get a reference to the scene
		static LampScene& getScene()
		{
			return *getEngine().getScene();
		}

		//Get a reference to the LampEngine
		static LampEngine& getEngine()
		{
			return *get().m_pEngine;
		}

	};

}