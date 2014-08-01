#pragma once

#include "stdafx.h"

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

namespace LampProject
{

	//Forward decl
	class LampLua;

	//Simple defines for ease
#define LuaState lua_State*

	//Get the global lua object
	//This is really just for convenience
	//But it doesn't add much overhead tho
	//Then again, we should look into a way of not adding any overhead!
	//Huehuehue
	static inline LampLua& getLua(LuaState L)
	{
		lua_getglobal(L, "ptrLua");
		int iPtr = (int)lua_tonumber(L, -1);
		lua_pop(L, 1);
		return *(LampLua*)iPtr;
	}

	//
	// Our Lua Bindings Class
	//
	class LampLua
	{

	private:
		LuaState m_state;

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
		}

		void close()
		{
			lua_close(m_state);
		}

		lua_State* getState()
		{
			return m_state;
		}

		int doFile(std::string fileName)
		{
			return luaL_dofile(m_state, fileName.c_str());
		}

		void print()
		{
			printf("testhehe\n");
		}

		//##################
		//# Util functions #
		//##################

		//define cuz we be lazy yo

		//Register a c function
		inline void registerFunction(std::string name, lua_CFunction func)
		{
			lua_register(m_state, name.c_str(), func);
		}

		//Clear x amount of things on the stack
		inline void pop(int x = 1)
		{
			lua_pop(m_state, x);
		}

		//Get an integer from the given stack location, or if not given the top 
		inline int getInt(int stackLocation = -1)
		{
			return lua_tointeger(m_state, stackLocation);
		}

		//Put an integer on the top of the stack
		inline void pushInt(int i)
		{
			lua_pushinteger(m_state, i);
		}

		//Get a number from the given stack location, or if not given the top
		inline lua_Number getNumber(int stackLocation = -1)
		{
			return lua_tonumber(m_state, stackLocation);
		}

		//Yay we finally get to use templated, not even sure if that's necessary, but w / e
		//Push a number to the stack
		template<typename T>
		inline void pushNumber(T number)
		{
			lua_pushnumber(m_state, number);
		}

		//Get a string from the top of the stack, or if not given the top 
		inline std::string getString(int stackLocation = -1)
		{
			return lua_tostring(m_state, stackLocation);
		}

		//Put a string on the top of the stack
		inline void pushString(std::string str)
		{
			lua_pushstring(m_state, str.c_str());
		}

		//Get a boolean from the top of the stack
		inline bool getBool(int stackLocation = -1)
		{
			return lua_toboolean(m_state, stackLocation) > 0 ? true : false;
		}

		//Push a bool to the top of the stack
		inline void pushBool(bool b)
		{
			lua_pushboolean(m_state, b);
		}

		//Get the top index of the stack
		inline int getTop() { return lua_gettop(m_state); }

		//#######
		//# GET #
		//#######

		//Testing more!
		template<typename T> inline T get(int stackLocation) { assert(false); } //Not supported yet

		//Get a number
		template<> inline int get(int stackLocation) { return (int)getNumber(stackLocation); }
		template<> inline float get(int stackLocation) { return (float)getNumber(stackLocation); }
		template<> inline double get(int stackLocation) { return (double)getNumber(stackLocation); }

		//Get a boolean
		template<> inline bool get(int stackLocation) { return (bool)getBool(stackLocation); }

		//Get a string
		template<> inline std::string get(int stackLocation) { return (std::string)getString(stackLocation); }

		//#######
		//# SET #
		//#######
		template<typename T> inline void push(T value) { assert(false); } //Not supported yet

		//Push a number
		template<> inline void push(int i) { pushNumber(i); }
		template<> inline void push(float f) { pushNumber(f); }
		template<> inline void push(double d) { pushNumber(d);  }

		//Push a boolean
		template<> inline void push(bool b) { pushBool(b); }

		//Push a string
		template<> inline void push(std::string s) { pushString(s);  }

		//##########
		//# GLOBAL #
		//##########

		//Global set's
		inline void setGlobal(std::string name)
		{
			lua_setglobal(m_state, name.c_str());
		}

		//Get a global value
		template<typename T>
		inline T getGlobal(std::string name)
		{
			lua_getglobal(m_state, name.c_str());
			T t = get<T>(-1);
			pop();
			return t;
		}

		//Get a global ptr
		template<typename T>
		inline T* getGlobalPtr(std::string name)
		{
			int iPtr = getGlobal<int>(name);
			return (T*)iPtr;
		}

		//Set a global value
		template<typename T>
		inline void setGlobal(std::string name, T value) 
		{
			push(value);
			setGlobal(name);
		}

	};


}