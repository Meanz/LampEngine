#include "stdafx.h"
#include "LampMaterial.hpp"


LampMaterial::LampMaterial()
{
	//Initialize all textures to null
	for (unsigned int i = 0; i < MAX_MATERIAL_TEXTURE; i++)
	{
		m_textures[i] = NULL;
	}
}

LampMaterial::~LampMaterial()
{

}

void LampMaterial::setFloat(std::string key, float f)
{
	m_valueMap.m_floatMap[key] = f;
}

void LampMaterial::setInt(std::string key, int i)
{
	m_valueMap.m_intMap[key] = i;
}

void LampMaterial::setBool(std::string key, bool b)
{
	m_valueMap.m_boolMap[key] = b;
}

void LampMaterial::setMatrix4(std::string key, mat4 m)
{
	m_valueMap.m_mat4Map[key] = m;
}

void LampMaterial::setMatrix3(std::string key, mat3 m)
{
	m_valueMap.m_mat3Map[key] = m;
}

void LampMaterial::setVec2(std::string key, vec2 v)
{
	m_valueMap.m_vec2Map[key] = v;
}

void LampMaterial::setVec3(std::string key, vec3 v)
{
	m_valueMap.m_vec3Map[key] = v;
}

void LampMaterial::setVec4(std::string key, vec4 v)
{
	m_valueMap.m_vec4Map[key] = v;
}

float LampMaterial::getFloat(std::string key)
{
	std::map<std::string, float>::iterator iter = m_valueMap.m_floatMap.find(key);
	if (iter != m_valueMap.m_floatMap.end())
	{
		return iter->second;
	}
	else
	{
		return 0.0f; //Return NULL
	}
}

int LampMaterial::getInt(std::string key)
{
	std::map<std::string, int>::iterator iter = m_valueMap.m_intMap.find(key);
	if (iter != m_valueMap.m_intMap.end())
	{
		return iter->second;
	}
	else
	{
		return 0; //Return NULL
	}
}

bool LampMaterial::getBool(std::string key)
{
	std::map<std::string, bool>::iterator iter = m_valueMap.m_boolMap.find(key);
	if (iter != m_valueMap.m_boolMap.end())
	{
		return iter->second;
	}
	else
	{
		return false; //Return NULL
	}
}

mat4 LampMaterial::getMatrix4(std::string key)
{
	std::map<std::string, mat4>::iterator iter = m_valueMap.m_mat4Map.find(key);
	if (iter != m_valueMap.m_mat4Map.end())
	{
		return iter->second;
	}
	else
	{
		return mat4(1.0); //Return NULL
	}
}

mat3 LampMaterial::getMatrix3(std::string key)
{
	std::map<std::string, mat3>::iterator iter = m_valueMap.m_mat3Map.find(key);
	if (iter != m_valueMap.m_mat3Map.end())
	{
		return iter->second;
	}
	else
	{
		return mat3(1.0); //Return NULL
	}
}

vec2 LampMaterial::getVec2(std::string key)
{
	std::map<std::string, vec2>::iterator iter = m_valueMap.m_vec2Map.find(key);
	if (iter != m_valueMap.m_vec2Map.end())
	{
		return iter->second;
	}
	else
	{
		return vec2(0.0); //Return NULL
	}
}

vec3 LampMaterial::getVec3(std::string key)
{
	std::map<std::string, vec3>::iterator iter = m_valueMap.m_vec3Map.find(key);
	if (iter != m_valueMap.m_vec3Map.end())
	{
		return iter->second;
	}
	else
	{
		return vec3(0.0); //Return NULL
	}
}

vec4 LampMaterial::getVec4(std::string key)
{
	std::map<std::string, vec4>::iterator iter = m_valueMap.m_vec4Map.find(key);
	if (iter != m_valueMap.m_vec4Map.end())
	{
		return iter->second;
	}
	else
	{
		return vec4(0.0); //Return NULL
	}
}