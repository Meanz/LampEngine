#pragma once

#include "stdafx.h"

namespace LampProject
{

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
		GLuint m_glId;
		LampShaderType m_shaderType;
		std::string m_shaderSource;
		std::string m_errorString;

	public:

		LampShader(LampShaderType);
		~LampShader();

		int getGLId();
		std::string getErrorString();
		std::string getSource();
		LampShaderType getType();
		std::string getTypeString();
		void setSource(std::string);
		bool compile();

	};

	class LampShaderProgram
	{

	private:
		GLuint m_glId;
		std::vector<LampShader*> m_vShaders;
		bool m_isCompiled;
		std::string m_errorString;


	public:

		LampShaderProgram();
		~LampShaderProgram();

		std::string getErrorString();
		void addShader(LampShader* pShader);
		void clearShaders();
		bool compile();
		void use();
		void updateUniforms(LampRenderer& renderer);
	};

}