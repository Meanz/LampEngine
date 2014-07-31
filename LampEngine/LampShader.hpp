#pragma once

#include "stdafx.h"

namespace LampProject
{

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

		std::string getErrorString();
		void setSource(std::string);
		bool compile();

	};

	class LampShaderProgram
	{

	private:
		GLuint m_glId;
		std::vector<LampShader*> m_vShaders;
		bool m_isCompiled;


	public:

		LampShaderProgram();
		~LampShaderProgram();

		void addShader(LampShader* pShader);
		void clearShaders();
		bool compile();
		void use();
		void updateUniforms(LampRenderer& renderer);
	};

}