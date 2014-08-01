#pragma once
#include "stdafx.h"

namespace LampProject
{

	class LampShaderParser
	{
	private:
		std::string m_shaderSource;
		std::string m_lShaderPath;
		int m_shaderVersion;

		std::vector<LampShader*> m_vShaders;

	public:

		LampShaderParser(std::string pathTolShader);
		~LampShaderParser();

		void setVersion(int version);
		std::vector<LampShader*>& getShaders();
		void addShader(LampShader* pShader);
		bool parse();
	};

}