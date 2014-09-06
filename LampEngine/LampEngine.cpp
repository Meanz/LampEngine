#include "stdafx.h"
#include "LampEngine.hpp"

LampEngine::LampEngine(LampApplication* pApplication, LampConfig config) :
m_pApplication(pApplication),
m_config(config),
m_isRunning(false),
m_pAssetManager(0),
m_pRenderer(0),
m_pScene(0),
m_pInput(0),
m_pWindow(0),
m_FPS(0),
m_UPS(0)
{
	//Create our SDLWrapper
	SDLConfig _config;

	//Copy configuration contents
	_config.width = m_config.width;
	_config.height = m_config.height;
	_config.title = m_config.title;

	m_pWrapper = new SDLWrapper(_config);
}

//Cuz we have to, rite?
void LampEngine::postConstructor()
{
	//Initialization order is important
	//These components depend on each other!
	m_pWindow = (new LampWindow(m_config.width, m_config.height, m_config.title, m_pWrapper->getWindow()));
	m_pAssetManager = (new LampAssetManager());
	m_pRenderer = (new LampRenderer());
	m_pScene = (new LampScene());
	m_pInput = (new LampInput());

	//Try to access our init lua!
	Lamp::get().getLua().doFile("./data/lua/init.lua");
}

LampEngine::~LampEngine()
{
	//Destroy the SDLWrapper in the end
	//SDLWrapper.destroy();

	//Delete the asset manager, which in turn will delete the assets
	delete m_pAssetManager;
	delete m_pWindow;
	delete m_pRenderer;
	delete m_pScene;
	delete m_pInput;
	delete m_pWrapper;

	Lamp::onEngineQuit();
}

float LampEngine::getFrameTime()
{
	return m_FrameTime;
}

int LampEngine::getFPS()
{
	return m_FPS;
}

int LampEngine::getUPS()
{
	return m_UPS;
}

void LampEngine::start()
{
	m_isRunning = true;
	//SDLWrapper.startLoop(this);

	if (m_pWrapper->init())
	{

		//
		//Initialize default shader
		Lamp::getAssetManager().loadShaderProgram("default", "./data/shaders/test.lshader");
		Lamp::getAssetManager().loadShaderProgram("skinned", "./data/shaders/skinned.lshader");

		LampMaterial* pMaterial = Lamp::getAssetManager().getMaterial("default");
		pMaterial->setShader(Lamp::getAssetManager().getShaderProgram("default"));

		pMaterial = Lamp::getAssetManager().createMaterial("skinned");
		pMaterial->setShader(Lamp::getAssetManager().getShaderProgram("skinned"));

		//Send preInit event!
		m_pApplication->onInit();


		//
		loop(); //Start the loop!
	}

}

void LampEngine::stop()
{
	m_isRunning = false;
}

void LampEngine::loop()
{

	//Event handler
	//SDL_Event e;

	//Enable text input
	//SDL_StartTextInput();

	const int TICKS_PER_SECOND = m_config.targetUpdatesPerSecond;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND; //Reverse
	const int MAX_FRAME_SKIP = 100;

	DWORD64 nextTick = GetTickCount64();
	DWORD64 lastFPSTick = GetTickCount64();

	int tempFPS = 0;
	int tempUPS = 0;

	DWORD64 lastFrame = GetTickCount64();

	//While application is running
	int loops;
	while (m_isRunning)
	{

		if (SDL_GetTicks() - lastFPSTick > 1000)
		{
			m_FPS = tempFPS;
			m_UPS = tempUPS;
			tempFPS = 0;
			tempUPS = 0;
			lastFPSTick = SDL_GetTicks();
		}

		loops = 0;
		while (GetTickCount64() > nextTick && loops < MAX_FRAME_SKIP)
		{
			//Send updates to the scene and all the components that requires it
			m_pScene->onTick();
			m_pApplication->onTick();

			nextTick += SKIP_TICKS;
			loops++;
			tempUPS++;
		}

		//check if the game has frozen
		if (loops == MAX_FRAME_SKIP)
		{
			//Game has frozen? 
			//Tell someone about this.
		}

		//What is the time since last frame?
		m_FrameTime = GetTickCount64() - lastFrame;
		lastFrame = GetTickCount64();

		//Poll input
		m_pInput->pollInput();

		//Tell the application that we are about to draw a frame
		m_pApplication->onPreFrame();

		//Tell the scene we are rendering
		m_pRenderer->render(m_pScene->getRoot());

		//Tell the application that a frame is happening
		m_pApplication->onFrame();

		//Tell the application that a frame is ready to be sent to the screen 
		m_pApplication->onPostFrame();

		//Update screen
		m_pWrapper->swapBuffers();

		tempFPS++;
	}

	//Disable text input
	//SDL_StopTextInput();


	//Free resources and close SDL
	//close();
}