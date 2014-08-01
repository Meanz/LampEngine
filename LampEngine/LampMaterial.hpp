#pragma once
#include "stdafx.h"
#include "LampTexture.hpp"

namespace LampProject
{

#define MAX_MATERIAL_TEXTURE 4

	struct LampValueMap
	{
		std::map<std::string, float> m_floatMap;
		std::map<std::string, int> m_intMap;
		std::map<std::string, bool> m_boolMap;
		std::map<std::string, mat3> m_mat3Map;
		std::map<std::string, mat4> m_mat4Map;
		std::map<std::string, vec2> m_vec2Map;
		std::map<std::string, vec3> m_vec3Map;
		std::map<std::string, vec4> m_vec4Map;
	};

	class LampMaterial
	{
	private:
		vec4 m_diffuseColor;
		vec4 m_specularColor;
		float m_specularIntensity;
		LampTexture* m_textures[MAX_MATERIAL_TEXTURE]; //Max 4 textures per material, we will change this later
		LampValueMap m_valueMap;
		
	public:

		LampMaterial();
		~LampMaterial();

		void setFloat(std::string key, float f);
		void setInt(std::string key, int i); //sint
		void setBool(std::string key, bool b);
		
		void setMatrix4(std::string key, mat4 m);
		void setMatrix3(std::string key, mat3 m); //don't think this is needed so leave empty for now

		void setVec2(std::string key, vec2 v);
		void setVec3(std::string key, vec3 v);
		void setVec4(std::string key, vec4 v);
	
		float getFloat(std::string key);
		int getInt(std::string key);
		bool getBool(std::string key);

		mat4 getMatrix4(std::string key);
		mat3 getMatrix3(std::string key);

		vec2 getVec2(std::string key);
		vec3 getVec3(std::string key);
		vec4 getVec4(std::string key);
	};

}