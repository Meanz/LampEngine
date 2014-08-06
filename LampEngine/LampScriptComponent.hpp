#pragma once
#include "stdafx.h"

namespace LampProject
{


	class LampScriptComponent : public LampNodeComponent
	{
	private:
		std::string m_scriptFile;
		LampLua* m_pLua;
	public:

		LampScriptComponent(std::string _scriptFile);
		~LampScriptComponent();

		void onTick();
		void onFrame();

		virtual int type() { return LampNodeComponentType::SCRIPT; }
	};

}