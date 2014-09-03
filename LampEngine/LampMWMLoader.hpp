#pragma once
#include "stdafx.h"
#include "LampAnimation.hpp"

namespace LampProject
{

	struct LampMWMMaterial
	{
		vec4 diffuseColor;
		vec4 specularColor;
		float specularIntensity;
		std::string diffuseTexture;
	};

	struct LampMWMMesh
	{
		std::vector<vec3> positions;
		std::vector<vec3> normals;
		std::vector<vec2> uvs;
		std::vector<GLuint> indices;
		LampMWMMaterial material;
	};

	class LampMWMLoader
	{

	private:
		LampBinaryBuffer* m_buffer;
		std::string m_filePath;

	public:

		LampMWMLoader(std::string modelFile);
		~LampMWMLoader();


		inline vec3 getVec3();
		inline vec2 getVec2();

		//This one will load mesh, skeleton, animation if there is any :D
		LampMesh* loadModel();

		void loadMesh();
		LampSkeleton* loadSkeleton();
		LampAnimation* loadAnimation();



	};

}