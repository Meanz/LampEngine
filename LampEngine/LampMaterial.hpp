#pragma once
#include "stdafx.h"
#include "LampTexture.hpp"

namespace LampProject
{

#define MAX_MATERIAL_TEXTURE 4


	struct LampValueMap
	{
		map<string, float> m_floatMap;
		map<string, int> m_intMap;
		map<string, bool> m_boolMap;
		map<string, mat3> m_mat3Map;
		map<string, mat4> m_mat4Map;
		map<string, vector<mat4>> m_mat4ArrayMap;
		map<string, vec2> m_vec2Map;
		map<string, vec3> m_vec3Map;
		map<string, vec4> m_vec4Map;
		map<string, LampTexture*> m_textures;
	};

	class LampShaderProgram;

	class LampMaterial
	{
	private:
		vec4 m_diffuseColor;
		vec4 m_specularColor;
		float m_specularIntensity;
		LampValueMap m_valueMap;
		LampShaderProgram* m_pShader;
		
	public:

		LampMaterial();
		~LampMaterial();

		LampShaderProgram* getShader();
		void setShader(LampShaderProgram* pShader);

		LampTexture* getTexture(string key);
		void setTexture(string key, LampTexture* pTexture);

		void setFloat(string key, float f);
		void setInt(string key, int i); //sint
		void setBool(string key, bool b);
		
		void setMatrix4(string key, mat4 m);
		void setMatrix4Array(string key, vector<mat4>& m);
		void setMatrix3(string key, mat3 m); //don't think this is needed so leave empty for now

		void setVec2(string key, vec2 v);
		void setVec3(string key, vec3 v);
		void setVec4(string key, vec4 v);
	
		float getFloat(string key);
		int getInt(string key);
		bool getBool(string key);

		mat4 getMatrix4(string key);
		vector<mat4>& getMatrix4Array(string key);
		mat3 getMatrix3(string key);

		vec2 getVec2(string key);
		vec3 getVec3(string key);
		vec4 getVec4(string key);
	};

}