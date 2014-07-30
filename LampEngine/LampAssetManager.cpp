#include "stdafx.h"
#include "LampAssetManager.hpp"
#include "LampTextureLoader.hpp"

LampAssetManager::LampAssetManager() :
m_texIdCounter(0)
{

}

LampAssetManager::~LampAssetManager()
{
	//Destroy all stored assets
	std::map<std::string, LampTexture*>::iterator iter;

	for (iter = textures.begin(); iter != textures.end(); iter++)
	{
		delete iter->second; //Delete the texture, which then again will call glDeleteTexture
	}
}

LampTexture* LampAssetManager::getTexture(std::string textureId) 
{
	std::map<std::string, LampTexture*>::iterator iter = textures.find(textureId);
	if (iter != textures.end())
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
	LampTexture* pTexture = LampTextureLoader::loadTexture(textureFilePath);
	if (pTexture > 0) 
	{
		//Generate id for the texture
		int id;
		for (id = 0; getTexture("tex_" + id) != NULL; id = m_texIdCounter++);
		textures["tex_" + id] = pTexture;
		pTexture->m_id = "tex_" + id;
		return pTexture;
	}
	else 
	{
		return NULL;
	}
}

LampTexture* LampAssetManager::loadTexture(std::string textureId, std::string textureFilePath)
{
	//check if there is a texture with that id already
	assert(!getTexture(textureId));

	LampTexture* pTexture = LampTextureLoader::loadTexture(textureFilePath);
	if (pTexture > 0)
	{
		pTexture->m_id = textureId;
		textures[textureId] = pTexture;
		return pTexture;
	}
	else
	{
		return NULL;
	}
	
}