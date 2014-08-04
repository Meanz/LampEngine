#include "stdafx.h"
#include "LampShaderParser.hpp"
///
/// Lua Exports
/// 

static void stackDump(LuaState L) {
	int i = lua_gettop(L);
	while (i) {
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TSTRING:
			printf("String: %d:`%s'\n", i, lua_tostring(L, i));
			break;
		case LUA_TBOOLEAN:
			printf("Boolean: %d: %s\n", i, lua_toboolean(L, i) ? "true" : "false");
			break;
		case LUA_TNUMBER:
			printf("Number: %d: %X\n", i, lua_tonumber(L, i));
			break;
		default: printf("Type: %i - %d: %s\n", t, i, lua_typename(L, t)); break;
		}
		i--;
	}
}

LampShaderParser* getRef(int iPtr)
{
	LampShaderParser* pShaderParser = (LampShaderParser*)iPtr;
	return pShaderParser; //Looks simple enough :o
}

int LUA_setShaderVersion(LuaState L)
{
	LampLua lua = getLua(L);
	int argc = lua.getTop();

	if (argc != 1) {
		//Report error
		luaL_error(L, "Invalid number of arguments for setShaderVersion");
		return -1;
	}

	//Get the number that is on top! :D
	int i = lua.get<int>(-1);
	printf("Version: %d\n", i);
	LampShaderParser* parser = lua.getGlobalPtr<LampShaderParser>("ptrLampShaderParser");
	parser->setVersion(i);

	return 0;
}


void addShader(std::string path, LampShaderType type, LampShaderParser& parser)
{
	LampFileReadResult readResult = readFile(path);
	if (readResult.readComplete)
	{
		LampShader* pShader = new LampShader(type);
		pShader->setSource(readResult.fileContents);
		printf("Read file %s\n", path.c_str());
		parser.addShader(pShader);
	}
	else
	{
		//Report error
		printf("Unable to read file %s\n", path.c_str());
	}
}

int LUA_addFragmentShader(LuaState L)
{
	//Get our lua object
	LampLua lua = getLua(L);

	int argc = lua.getTop();
	printf("argc: addfs %d\n", argc);
	if (argc != 1)
	{
		//Report error
		luaL_error(L, "Invalid number of arguments for getThisDir");
		return -1;
	}

	//Get our string!
	std::string path = lua.get<std::string>(-1); //Top of stack!?

	//Not sure if this makes a copy :o
	LampShaderParser* parser = lua.getGlobalPtr<LampShaderParser>("ptrLampShaderParser");
	addShader(path, LampShaderType::FRAGMENT, *parser);

	return 90;
}

int LUA_addVertexShader(LuaState L)
{
	//Get our lua object
	LampLua lua = getLua(L);

	int argc = lua.getTop();
	printf("argc: addvs %d\n", argc);
	if (argc != 1)
	{
		//Report error
		luaL_error(L, "Invalid number of arguments for getThisDir");
		return -1;
	}

	//Get our string!
	std::string path = lua.get<std::string>(-1); //Top of stack!?
	
	//Not sure if this makes a copy :o
	LampShaderParser* parser = lua.getGlobalPtr<LampShaderParser>("ptrLampShaderParser");
	addShader(path, LampShaderType::VERTEX, *parser);


	return 0;
}


//TODO: Hehe
int LUA_getThisDir(LuaState L)
{
	int argc = lua_gettop(L);
	if (argc > 0)
	{
		//Report error
		luaL_error(L, "Invalid number of arguments for getThisDir");
		return -1; //Not sure if this is the way to go ?
	}

	lua_pushfstring(L, "./data/shaders/");
	return 1;
}

//
// REPORT ERRORS OR 
//
void report_errors(LuaState L, int status)
{
	//Dump stack
	LampLua lua = getLua(L);

	if (status != 0) {
		std::cerr << "Lua Error -- " << lua.getString() << std::endl;
		
		lua.pop();
	}

	//stackDump(L);
}


///
/// End Lua Exports
///

LampShaderParser::LampShaderParser(std::string filePath)
{
	m_lShaderPath = filePath;
}

LampShaderParser::~LampShaderParser()
{

}

LampShaderMap LampShaderParser::getShaderMap()
{
	return m_shaderMap;
}

void LampShaderParser::setVersion(int version)
{
	m_shaderVersion = version;
}

std::vector<LampShader*>& LampShaderParser::getShaders()
{
	return m_vShaders;
}

void LampShaderParser::addShader(LampShader* pShader)
{
	m_vShaders.push_back(pShader);
}

bool LampShaderParser::parse()
{

	//Tell lua to execute the lShader script!
	LampLua lua;

	lua.registerFunction("setShaderVersion", LUA_setShaderVersion);
	lua.registerFunction("addFragmentShader", LUA_addFragmentShader);
	lua.registerFunction("addVertexShader", LUA_addVertexShader);
	lua.registerFunction("getThisDir", LUA_getThisDir);
	lua.setGlobal("ptrLampShaderParser", (int)this);

	//Call the lua file
	int status = lua.doFile(m_lShaderPath);

	//Report any errors
	report_errors(lua.getState(), status);

	//close lua
	lua.close();

	//start parsing the source code!

	//Pre processing

	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		//Do something with the shader
		LampShader& pShader = *m_vShaders[i];

		//Inject version into the source!
		std::string _tempShaderSource = "#version ";
		_tempShaderSource.append(std::to_string(m_shaderVersion));
		_tempShaderSource.append("\n");
		printf("New weird string: %s", _tempShaderSource.c_str());
		_tempShaderSource.append(pShader.getSource());

		//That should do the trick, hehe
		pShader.setSource(_tempShaderSource);
	}

	goto failJmp;
fail: 
	printf("Error parsing shader %s -- %s\n", m_lShaderPath.c_str(),"");
	return false;
failJmp:

	//Post processing
	for (unsigned int i = 0; i < m_vShaders.size(); i++)
	{
		//Do something with the shader
		
		LampShader& pShader = *m_vShaders[i];

		//Process the shader source
		std::string& src = pShader.getSource();

		//convenience
		using namespace std;

		//working source
		std::string wsrc = src;
		string::size_type uniformPos;
		string::size_type idx, idx2; //index that we can work with, temp shit
		int uniformSkipLength = string("uniform").length();

		while ((uniformPos = wsrc.find("uniform")) != string::npos)
		{
			wsrc = wsrc.substr(uniformPos + uniformSkipLength);
			
			//Find the next space
			idx = wsrc.find(" ");
			if (idx == string::npos) goto fail;

			//Find next semicolon
			idx2 = wsrc.find(";");
			if (idx2 == string::npos) goto fail;

			//What's in between is now the uniform type and name!
			std::string uniformTypeName = wsrc.substr(idx + 1, idx2 -1);
			
			idx = uniformTypeName.find(" ");
			if (idx == string::npos) goto fail; //Can't really happen, but let's be sure :D

			std::string uniformType = uniformTypeName.substr(0, idx);
			std::string uniformName = uniformTypeName.substr(idx + 1);

			printf("type: '%s'\n", uniformType.c_str());
			printf("name: '%s'\n", uniformName.c_str());

			//Push uniform name and type to the map, and push -1 for the location just for alloc's sake
			m_shaderMap.uniformNames.push_back(uniformName);
			m_shaderMap.uniformTypes.push_back(uniformType);
			m_shaderMap.uniformLocations.push_back(-1);

		}
	}

	

	//We completed the parsing
	return true;
}