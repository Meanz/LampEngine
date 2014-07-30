#include "stdafx.h"
#include "LampEngine.hpp"

LampEngine::LampEngine(LampApplication* pApplication, LampConfig config) :
m_pApplication(pApplication),
m_config(config),
m_pAssetManager(new LampAssetManager()),
m_pWindow(new LampWindow(config.width, config.height, config.title)),
m_pRenderer(new LampRenderer())
{
	//Create our SDLWrapper
	SDLConfig _config;

	//Copy configuration contents
	_config.width = m_config.width;
	_config.height = m_config.height;
	_config.title = m_config.title;

	m_pWrapper = new SDLWrapper(_config);
}

LampEngine::~LampEngine()
{
	//Delete the asset manager, which in turn will delete the assets
	delete m_pAssetManager;
	delete m_pWindow;
	delete m_pRenderer;
}

void LampEngine::start()
{
	//SDLWrapper.startLoop(this);

	if (m_pWrapper->init())
	{
		//Send preInit event!
		m_pApplication->onInit();

		loop(); //Start the loop!
	}

}

void LampEngine::stop()
{

	//Destroy the SDLWrapper in the end
	//SDLWrapper.destroy();
}

void LampEngine::loop()
{
	//Main loop flag
	bool quit = false;

	//Event handler
	//SDL_Event e;

	//Enable text input
	//SDL_StartTextInput();

	const int TICKS_PER_SECOND = m_config.targetUpdatesPerSecond;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAME_SKIP = 100;
	
	DWORD64 nextTick = GetTickCount64();

	//While application is running
	int loops;
	while (!quit)
	{

		loops = 0;
		while (GetTickCount64() > nextTick && loops < MAX_FRAME_SKIP)
		{
			//Send updates to the scene and all the components that requires it
			//m_pScene->onTick();
			m_pApplication->onTick();

			nextTick += SKIP_TICKS;
			loops++;
		}

		//check if the game has frozen
		if (loops == MAX_FRAME_SKIP) 
		{
			//Game has frozen? 
			//Tell someone about this.
		}

		
		//Tell the application that we are about to draw a frame
		m_pApplication->onPreFrame();

		//Tell the renderer we are rendering!
		m_pRenderer->render();

		//Tell the scene we are rendering


		//Tell the application that a frame is happening
		m_pApplication->onFrame();


		//Tell the application that a frame is ready to be sent to the screen 
		m_pApplication->onPostFrame();

		//Update screen
		m_pWrapper->swapBuffers();
	}

	//Disable text input
	//SDL_StopTextInput();


	//Free resources and close SDL
	//close();
}