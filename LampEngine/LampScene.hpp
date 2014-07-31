#pragma once

#include "LampGameObject.hpp"
#include "LampCamera.hpp"

namespace LampProject {

	class LampScene
	{

	private:

		LampGameObject* m_pRootNode;
		LampCamera* m_pMainCamera; //This will be constructed in the constructor

	public:

		LampScene();
		~LampScene();

		void setCamera(LampCamera* pCamera);
		LampCamera* getCamera();

		void attach(LampGameObject* child);
		void detatch(LampGameObject* child);

		void onTick(); //called to update the scene
		void onFrame(); //called to render the scene

	};


}