#pragma once

namespace LampProject
{

	//Simple interface for the engine to communicate with the client
	class LampApplication {

	public:

		//Called before the main loop is run
		//Allows for loading resources
		virtual void onInit() {};

		//Called to tick ( physics, math .. shit like that ) 
		//Uses a fixed interval x ticks per second
		virtual void onTick() {};

		//Called every frame 
		//deltaTime is in nano resolution
		virtual void onPreFrame() {};
		virtual void onFrame() {};
		virtual void onPostFrame() {};

	};


}
