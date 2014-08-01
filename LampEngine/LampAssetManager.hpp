#pragma once

#include <vector>
#include <map>
#include "LampTexture.hpp"
#include "LampShader.hpp"

namespace LampProject
{

	class LampAssetManager
	{

	private:
		int m_texIdCounter;

		std::map<std::string, LampTexture*> m_mTextures;
		std::map<std::string, LampShaderProgram*> m_mShaderPrograms;

	public:

		LampAssetManager();
		~LampAssetManager();

		//Get the texture with the specified id
		//Returns 0 if the texture was not found
		LampTexture* getTexture(std::string);

		//Load's a texture from the given file path
		LampTexture* loadTexture(std::string textureFilePath);

		//Load's a texture from the given file path and stores it with the given id
		LampTexture* loadTexture(std::string textureId, std::string textureFilePath);

		//Get the shader program with the specified id
		//Returns NULL if the shader program was not found
		LampShaderProgram* getShaderProgram(std::string shaderId);

		//Load a shader program from the given .lshader file
		LampShaderProgram* loadShaderProgram(std::string shaderId, std::string shaderProgramPath);

	};

}