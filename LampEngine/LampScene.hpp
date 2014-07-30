#pragma once

#include "LampGameObject.hpp"

namespace LampProject {

	class LampScene
	{

	private:

		LampGameObject* m_pRootNode;

	public:

		LampScene();
		~LampScene();

		void attach(LampGameObject* child);
		void detatch(LampGameObject* child);

		void onTick(); //called to update the scene
		void onFrame(); //called to render the scene

	};


}