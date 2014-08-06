#include "stdafx.h"
#include "LampMWMLoader.hpp"

LampMWMLoader::LampMWMLoader(std::string filePath)
{
	m_filePath = filePath;
}

LampMWMLoader::~LampMWMLoader()
{
	//Delete our buffer
	
}

inline vec3 LampMWMLoader::getVec3()
{
	float x = float(m_buffer->getDouble());
	float y = float(m_buffer->getDouble());
	float z = float(m_buffer->getDouble());
	printf("x: %f, y: %f, z: %f \n", x, y, z);
	return vec3(x, y, z);
}

inline vec2 LampMWMLoader::getVec2()
{
	float x = m_buffer->getDouble();
	float y = m_buffer->getDouble();
	return vec2(x,y);
}

LampMesh* LampMWMLoader::loadModel()
{

	//Read file :D
	LampBinaryFileReadResult readResult = readBinaryFile(m_filePath);
	m_buffer = new LampBinaryBuffer(&readResult.bytes);


	short version = m_buffer->getShort();
	
	std::string meshName = m_buffer->getString();
	
	printf("Mesh: %s ... Version: %i\n", meshName.c_str(), version);

	short numVertices = m_buffer->getShort();
	short numIndices = m_buffer->getShort();
	bool hasNormals = m_buffer->getByte() == 1;
	bool hasUVs = m_buffer->getByte() == 1;
	bool hasBoneAssignments = m_buffer->getByte() == 1;


	vec3* positions = new vec3[numVertices];
	vec3* normals = NULL;
	vec2* uvs = NULL;
	
	//Positions
	for (short i = 0; i < numVertices; i++)
	{
		positions[i] = getVec3();
	}

	//Normals
	if (hasNormals)
	{
		normals = new vec3[numVertices];
		for (short i = 0; i < numVertices; i++)
		{
			normals[i] = getVec3();
		}
	}

	//UVs
	if (hasUVs)
	{
		uvs = new vec2[numVertices];
		for (short i = 0; i < numVertices; i++)
		{
			uvs[i] = getVec2();
		}
	}

	//Indices
	uint32_t* indices = new uint32_t[numIndices];
	for (short i = 0; i < numIndices; i++)
	{
		indices[i] = (uint32_t)m_buffer->getShort();
	}

	//Bone assignments
	if (hasBoneAssignments)
	{
		
		short numBones = m_buffer->getShort();

		for (short i = 0; i < numBones; i++)
		{
			//bones[i] = m_buffer->getString();
		}

		//Default
		short weightsPerBone = 4;
		for (short i = 0; i < numVertices; i++)
		{


			for (short j = 0; j < weightsPerBone; j++)
			{
				int boneId = m_buffer->getInt();
				float weight = m_buffer->getDouble();
			}
		}

	}

	LampMesh* pMesh = new LampMesh();
	LampMeshData* pMeshData = pMesh->getMeshData();

	pMeshData->positions = positions;
	pMeshData->normals = normals;
	pMeshData->uvs = uvs;
	pMeshData->indices = indices;
	pMeshData->numVertices = numVertices;
	pMeshData->numIndices = numIndices;

	return pMesh;
}

void LampMWMLoader::loadMesh()
{

}

void LampMWMLoader::loadSkeleton()
{

}

void LampMWMLoader::loadAnimation()
{

}