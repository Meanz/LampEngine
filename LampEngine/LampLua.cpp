#include "stdafx.h"

LampLua::LampLua()
{
	m_state = luaL_newstate();

	//Load lua libraries seemingly
	static const luaL_Reg lualibs[] =
	{
		{ "base", luaopen_base },
		{ NULL, NULL }
	};

	//
	const luaL_Reg *lib = lualibs;
	for (; lib->func != NULL; lib++)
	{
		lib->func(m_state);
		lua_settop(m_state, 0);
	}

	//Push global ptr
	//Push globals
	setGlobal("ptrLua", (int)this);
}

LampLua::~LampLua()
{


}

lua_State* LampLua::getState()
{
	return m_state;
}

void LampLua::reportErrors(int status)
{
	if (status != 0) {
		std::cerr << "Lua Error -- " << getString() << std::endl;
		pop();
	}
}

void LampLua::loadFile(std::string fileName)
{
	luaL_loadfile(m_state, fileName.c_str());
	//Priming call
	lua_pcall(m_state, 0, 0, 0);
}

int LampLua::doFile(std::string fileName)
{
	return luaL_dofile(m_state, fileName.c_str());
}

void LampLua::print()
{
	printf("testhehe\n");
}
