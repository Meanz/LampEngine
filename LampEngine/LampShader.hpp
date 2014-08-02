#pragma once

#include "stdafx.h"

namespace LampProject
{

	struct LampShaderMap
	{
		std::vector<std::string> uniformNames;
		std::vector<std::string> uniformTypes;
		std::map<std::string, GLuint> samplerSlots;
		std::vector<GLint> uniformLocations;

		GLint getSamplerSlot(std::string key)
		{
			std::map<std::string, GLuint>::iterator it = samplerSlots.find(key);
			if (it != samplerSlots.end()) 
			{
				return it->second;
			} 
			else
			{
				return -1; //Not found
			}
		}
	};

	//simple forward declaration
	class LampRenderer;

	enum LampShaderType
	{
		FRAGMENT,
		VERTEX,
		GEOMETRY
	};

	class LampShader
	{

	private:
		//The OpenGL id associated with this shader
		GLuint m_glId;
		//The type of shader
		LampShaderType m_shaderType;
		//The source code of this shader
		std::string m_shaderSource;
		//The last error message, if any
		std::string m_errorString;

	public:

		LampShader(LampShaderType);
		~LampShader();

		//Get the OpenGL Id associated with this shader
		GLuint getGLId();
		//Get the last error message, if any
		std::string getErrorString();
		//Get the source code of this shader
		std::string getSource();
		//Get the type
		LampShaderType getType();
		//Get the type represented as a string
		std::string getTypeString();
		//Set the source code of this shader
		void setSource(std::string);
		//Compile this shader, returns true if successfull
		bool compile();

	};

	class LampShaderProgram
	{

	private:
		//The OpenGL id associated with this shader program
		GLuint m_glId;
		//The list of shaders attached to this program
		std::vector<LampShader*> m_vShaders;
		//Whether this program is compiled or not
		bool m_isCompiled;
		//The last error message, if any
		std::string m_errorString;
		//The uniform mappings for this shader
		LampShaderMap m_shaderMap;


	public:

		LampShaderProgram();
		~LampShaderProgram();

		//Get the OpenGL Id associated with this shader program
		GLuint getGLId();
		//Get the error string if any errors has occured
		std::string getErrorString();
		//Add a shader to this shader program
		void addShader(LampShader* pShader);
		//Clear all shader programs [Note] This will also delete the shaders
		void clearShaders();
		//Compile this shader program with it's associated shaders [Note] This will also delete the shaders
		bool compile(LampShaderMap shaderMap);
		//Use this shader program
		void use();
		//Update the uniforms of this shader program
		void updateUniforms(LampRenderer& renderer, LampMaterial* pMaterial);
	};

}