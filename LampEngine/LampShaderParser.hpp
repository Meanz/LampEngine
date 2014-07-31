#pragma once
#include "stdafx.h"

namespace LampProject
{

	class LampShaderParser
	{
	private:
		std::string m_shaderSource;
		std::string m_lShaderPath;

	public:

		LampShaderParser(std::string pathTolShader);
		~LampShaderParser();

		bool parse();
	};

}