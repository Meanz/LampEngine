#pragma once

#include "stdafx.h"

namespace LampProject
{

	enum LampMeshCompileMode
	{
		COMPILE_LEGACY = 0,
		COMPILE_DL = 1,
		COMPILE_VBO = 2,
		COMPILE_VAO = 3
	};

	struct LampMeshData
	{
		vec3* positions;
		vec3* normals;
		vec2* uvs;
		uint32_t* indices;
		int numIndices;
		int numVertices;

		LampMeshData() :
			positions(0),
			normals(0),
			uvs(0),
			indices(0),
			numIndices(0),
			numVertices(0)
		{}

		~LampMeshData()
		{
			/*
			if (positions > 0)
				delete[] positions;
			if (normals > 0)
				delete[] normals;
			if (uvs > 0)
				delete[] uvs;
			if (indices > 0)
				delete[] indices;*/
		}
	};

	class LampMesh
	{

	private:
		//Whether we need to compile or not
		//if this is flagged, the Mesh will be compiled the next frame
		//by the GL thread
		bool m_needCompile;
		//A flag used to check if we can render this object
		//Also used to determine if we have to delete already existing VBO's
		//If the data changes
		//TODO: Allow dynamic change of the data without destroying old buffers
		bool m_isCompiled;

		//The method we are compiling and rendering this Mesh with
		LampMeshCompileMode m_compileMode;

		//VBO id's
		GLuint m_vboPositions, m_vboNormals, m_vboUVs, m_vboIndices;

		//VAO id
		GLuint m_vao;

		//Display List id
		GLuint m_displayList;

		//The mesh data
		LampMeshData m_meshData;

		//The material for the mesh
		LampMaterial* m_material;


	public:
		LampMesh();
		~LampMesh();

		//Get the mesh data associated with this mesh
		LampMeshData* getMeshData();

		//Set the way this mesh is to be compiled
		void setCompileMode(LampMeshCompileMode compileMode);

		//Get the way we are rendering and compiling this mesh with
		LampMeshCompileMode getCompileMode();

		//Mark this mesh as updated, this will compile the mesh the next time it's drawn
		void markAsUpdated();

		//Compiles this mesh
		void compile();

		//Renders this mesh
		void render();
	};


}