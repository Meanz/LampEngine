#pragma once

#include "LampGameObject.hpp"
#include "LampCamera.hpp"
#include "LampGUI.hpp"

namespace LampProject {

	class LampScene
	{

	private:

		LampGameObject* m_pRootNode;
		LampCamera* m_pMainCamera; //This will be constructed in the constructor
		LampGUI* m_pGUI;

	public:

		LampScene();
		~LampScene();

		void setCamera(LampCamera* pCamera);
		LampCamera* getCamera();
		LampGameObject* getRoot();
		LampGUI* getGUI();

		void attach(LampGameObject* child);
		void detatch(LampGameObject* child);

		void onTick(); //called to update the scene
		void onFrame(); //called to render the scene

	};


}