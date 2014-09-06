#include "stdafx.h"
#include "LampMaterial.hpp"


LampMaterial::LampMaterial()
{
}

LampMaterial::~LampMaterial()
{

}

LampShaderProgram* LampMaterial::getShader()
{
	return m_pShader;
}

void LampMaterial::setShader(LampShaderProgram* pShader)
{
	m_pShader = pShader;
}

void LampMaterial::setFloat(string key, float f)
{
	m_valueMap.m_floatMap[key] = f;
}

void LampMaterial::setInt(string key, int i)
{
	m_valueMap.m_intMap[key] = i;
}

void LampMaterial::setBool(string key, bool b)
{
	m_valueMap.m_boolMap[key] = b;
}

void LampMaterial::setMatrix4(string key, mat4 m)
{
	m_valueMap.m_mat4Map[key] = m;
}

void LampMaterial::setMatrix3(string key, mat3 m)
{
	m_valueMap.m_mat3Map[key] = m;
}

void LampMaterial::setMatrix4Array(string key, vector<mat4*>& m)
{
	m_valueMap.m_mat4ArrayMap[key] = m;
}

void LampMaterial::setVec2(string key, vec2 v)
{
	m_valueMap.m_vec2Map[key] = v;
}

void LampMaterial::setVec3(string key, vec3 v)
{
	m_valueMap.m_vec3Map[key] = v;
}

void LampMaterial::setVec4(string key, vec4 v)
{
	m_valueMap.m_vec4Map[key] = v;
}

void LampMaterial::setTexture(string key, LampTexture* pTexture)
{
	m_valueMap.m_textures[key] = pTexture;
}

float LampMaterial::getFloat(string key)
{
	map<string, float>::iterator iter = m_valueMap.m_floatMap.find(key);
	if (iter != m_valueMap.m_floatMap.end())
	{
		return iter->second;
	}
	else
	{
		return 0.0f; //Return NULL
	}
}

int LampMaterial::getInt(string key)
{
	map<string, int>::iterator iter = m_valueMap.m_intMap.find(key);
	if (iter != m_valueMap.m_intMap.end())
	{
		return iter->second;
	}
	else
	{
		return 0; //Return NULL
	}
}

bool LampMaterial::getBool(string key)
{
	map<string, bool>::iterator iter = m_valueMap.m_boolMap.find(key);
	if (iter != m_valueMap.m_boolMap.end())
	{
		return iter->second;
	}
	else
	{
		return false; //Return NULL
	}
}

mat4 LampMaterial::getMatrix4(string key)
{
	map<string, mat4>::iterator iter = m_valueMap.m_mat4Map.find(key);
	if (iter != m_valueMap.m_mat4Map.end())
	{
		return iter->second;
	}
	else
	{
		return mat4(1.0); //Return NULL
	}
}

vector<mat4*>& LampMaterial::getMatrix4Array(string key)
{
	map<string, vector<mat4*>>::iterator iter = m_valueMap.m_mat4ArrayMap.find(key);
	if (iter != m_valueMap.m_mat4ArrayMap.end())
	{
		return iter->second;
	}
	else
	{
		vector<mat4*> nullVec;
		return nullVec; //Return NULL
	}
}

mat3 LampMaterial::getMatrix3(string key)
{
	map<string, mat3>::iterator iter = m_valueMap.m_mat3Map.find(key);
	if (iter != m_valueMap.m_mat3Map.end())
	{
		return iter->second;
	}
	else
	{
		return mat3(1.0); //Return NULL
	}
}

vec2 LampMaterial::getVec2(string key)
{
	map<string, vec2>::iterator iter = m_valueMap.m_vec2Map.find(key);
	if (iter != m_valueMap.m_vec2Map.end())
	{
		return iter->second;
	}
	else
	{
		return vec2(0.0); //Return NULL
	}
}

vec3 LampMaterial::getVec3(string key)
{
	map<string, vec3>::iterator iter = m_valueMap.m_vec3Map.find(key);
	if (iter != m_valueMap.m_vec3Map.end())
	{
		return iter->second;
	}
	else
	{
		return vec3(0.0); //Return NULL
	}
}

vec4 LampMaterial::getVec4(string key)
{
	map<string, vec4>::iterator iter = m_valueMap.m_vec4Map.find(key);
	if (iter != m_valueMap.m_vec4Map.end())
	{
		return iter->second;
	}
	else
	{
		return vec4(0.0); //Return NULL
	}
}

LampTexture* LampMaterial::getTexture(string key)
{
	map<string, LampTexture*>::iterator iter = m_valueMap.m_textures.find(key);
	if (iter != m_valueMap.m_textures.end())
	{
		return iter->second;
	}
	else
	{
		return NULL; //Return NULL
	}
}
