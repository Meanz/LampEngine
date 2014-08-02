#include "stdafx.h"
#include "LampAssetManager.hpp"
#include "LampTextureLoader.hpp"
#include "LampShaderParser.hpp"

LampAssetManager::LampAssetManager() :
m_texIdCounter(0)
{

	//Create a basic shader program
	//Well, we are not going to do this
	//std::string fragSource = "#version 330\nout vec4 out_color\nvoid main {\nout_color=vec4(1.0, 1.0, 1.0, 1.0);\n}\n";
	//std::string vertSource = "#version 330\nin vec3 position;\nin vec3 normal;\nin vec2 uv;\nuniform mat4 T_projectionView;\nmat4 T_world;\nvoid main()\ngl_Position=(T_projectionView * T_world)*vec4(position, 1.0);\n}\n";


	//Load our default material
	loadMaterial("default", "./data/materials/default.lmaterial");

}

LampAssetManager::~LampAssetManager()
{
	//Destroy all stored assets
	std::map<std::string, LampTexture*>::iterator iter;

	for (iter = m_mTextures.begin(); iter != m_mTextures.end(); iter++)
	{
		delete iter->second; //Delete the texture, which then again will call glDeleteTexture
	}
}

LampMaterial* LampAssetManager::createMaterial(std::string materialId)
{
	//collio!
	return NULL;
}

LampMaterial* LampAssetManager::loadMaterial(std::string materialId, std::string materialPath)
{
	
	//Just create an empty material
	LampMaterial* pMaterial = new LampMaterial();

	m_mMaterials[materialId] = pMaterial;
	return NULL;
}

LampMaterial* LampAssetManager::getMaterial(std::string materialId)
{
	std::map<std::string, LampMaterial*>::iterator iter = m_mMaterials.find(materialId);
	if (iter != m_mMaterials.end())
	{
		return iter->second;
	}
	else
	{
		return NULL; //Return NULL
	}
}

LampTexture* LampAssetManager::getTexture(std::string textureId)
{
	std::map<std::string, LampTexture*>::iterator iter = m_mTextures.find(textureId);
	if (iter != m_mTextures.end())
	{
		return iter->second;
	}
	else
	{
		return NULL; //Return NULL
	}
}

LampTexture* LampAssetManager::loadTexture(std::string textureFilePath)
{
	//Generate id for the texture
	int id;
	for (id = 0; getTexture("tex_" + id) != NULL; id = m_texIdCounter++);

	//Load the texture
	return loadTexture("tex_" + id, textureFilePath);
}

LampTexture* LampAssetManager::loadTexture(std::string textureId, std::string textureFilePath)
{
	//check if there is a texture with that id already
	assert(!getTexture(textureId));

	LampTexture* pTexture = LampTextureLoader::loadTexture(textureFilePath);
	if (pTexture > 0)
	{
		pTexture->m_id = textureId;
		m_mTextures[textureId] = pTexture;
		return pTexture;
	}
	else
	{
		return NULL;
	}

}

LampShaderProgram* LampAssetManager::getShaderProgram(std::string shaderId)
{
	std::map<std::string, LampShaderProgram*>::iterator iter = m_mShaderPrograms.find(shaderId);
	if (iter != m_mShaderPrograms.end())
	{
		return iter->second;
	}
	else
	{
		return NULL; //Return NULL
	}
}

LampShaderProgram* LampAssetManager::loadShaderProgram(std::string shaderId, std::string shaderFilePath)
{
	bool didComplete = false;
	LampShaderParser* pParser = new LampShaderParser(shaderFilePath);
	LampShaderProgram* pShaderProgram = NULL;
	if (pParser->parse())
	{

		//Create our shader program
		pShaderProgram = new LampShaderProgram();

		//Add all the shaders to the shader program
		std::vector<LampShader*> vShaders = pParser->getShaders();
		for (unsigned int i = 0; i < vShaders.size(); i++)
		{
			pShaderProgram->addShader(vShaders[i]);
		}

		//Concatenate all the uniform mappings and send them to the shader program
		//TODO: What this string says

		bool didCompile = pShaderProgram->compile(pParser->getShaderMap());

		//If the compilation was successful continue moving towards the mapping process
		//Otherwise the program will be deleted along with the attached shaders
		if (didCompile)
		{
			//Assign the shader program
			m_mShaderPrograms[shaderId] = pShaderProgram;
		}
		else
		{
			delete pShaderProgram;
			pShaderProgram = NULL;
		}
	}

	//Delete our shader parse
	delete pParser;

	//Return our program, or NULL if it wasn't created correctly
	return pShaderProgram;
}