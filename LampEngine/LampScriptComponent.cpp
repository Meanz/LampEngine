#include "stdafx.h"
#include "LampScriptComponent.hpp"

//
// Export GameObject data!
//

LampScriptComponent::LampScriptComponent(std::string scriptPath) :
m_scriptFile(scriptPath)
{
	//Setup the lua state	
	m_pLua = new LampLua();

	//Compile the in file <- Something we really should do :p

	m_pLua->loadFile(m_scriptFile);
}

LampScriptComponent::~LampScriptComponent()
{
	//Close the lua thingy!
	m_pLua->close();
}

void printLuaThing(LuaState L)
{
	luaL_dofile(L, "./data/lua/debug.lua");
}

void LampScriptComponent::onTick()
{
	lua_getglobal(m_pLua->getState(), "onTick");
	int state = lua_pcall(m_pLua->getState(), 0, 0, 0);
	m_pLua->reportErrors(state);
}

void LampScriptComponent::onFrame()
{
	lua_getglobal(m_pLua->getState(), "onFrame");
	int state = lua_pcall(m_pLua->getState(), 0, 0, 0);
	m_pLua->reportErrors(state);
}