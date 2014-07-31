#pragma once

#include "stdafx.h"

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

namespace LampProject
{

	class LampLua
	{

	private:
		lua_State* m_state;

	public:

		LampLua() 
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

		}

		~LampLua()
		{
			lua_close(m_state);
		}

		void doFile(std::string fileName)
		{
			luaL_dofile(m_state, fileName.c_str());
		}

	};

}