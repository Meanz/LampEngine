#include "stdafx.h"
#include "LampMesh.hpp"

LampMesh::LampMesh() :
m_meshData(),
m_vboPositions(0), m_vboNormals(0), m_vboUVs(0), m_vboIndices(0), m_vao(0), m_displayList(0),
m_needCompile(false), m_isCompiled(false), m_compileMode(LampMeshCompileMode::COMPILE_VAO)
{
	//Get default material
	m_material = Lamp::getAssetManager().getMaterial("default");
}

LampMesh::~LampMesh()
{
	if (m_isCompiled)
	{
		if (m_vboPositions > 0)
			glDeleteBuffers(1, &m_vboPositions);
		if (m_vboNormals > 0)
			glDeleteBuffers(1, &m_vboNormals);
		if (m_vboNormals > 0)
			glDeleteBuffers(1, &m_vboUVs);
		if (m_vboIndices > 0)
			glDeleteBuffers(1, &m_vboIndices);
		if (m_vao > 0)
			glDeleteVertexArrays(1, &m_vao);
		if (m_displayList > 0)
			glDeleteLists(m_displayList, 1);
	}
}

void LampMesh::setCompileMode(LampMeshCompileMode lmcm)
{
	m_compileMode = lmcm;
}

LampMaterial* LampMesh::getMaterial()
{
	return m_material;
}

void LampMesh::setMaterial(LampMaterial* pMaterial)
{
	m_material = pMaterial;
}

LampMeshData* LampMesh::getMeshData()
{
	return (&m_meshData);
}

bool LampMesh::isCompiled()
{
	return m_isCompiled;
}

void LampMesh::compile()
{

	//Check if we have compiled before, if we have,
	//Destroy old data!
	if (m_isCompiled)
	{
		if (m_vboPositions > 0)
			glDeleteBuffers(1, &m_vboPositions);
		if (m_vboNormals > 0)
			glDeleteBuffers(1, &m_vboNormals);
		if (m_vboNormals > 0)
			glDeleteBuffers(1, &m_vboUVs);
		if (m_vboIndices > 0)
			glDeleteBuffers(1, &m_vboIndices);
		if (m_vao > 0)
			glDeleteVertexArrays(1, &m_vao);
		if (m_displayList > 0)
			glDeleteLists(m_displayList, 1);
	}

	//Generate new data!

	if (m_compileMode == LampMeshCompileMode::COMPILE_LEGACY)
	{
		//No need to do anything yey
	}
	else if (m_compileMode == LampMeshCompileMode::COMPILE_DL)
	{
		m_displayList = glGenLists(1);

		glNewList(m_displayList, GL_COMPILE);
		{
			//We only support triangles because we are bitches :o
			glBegin(GL_TRIANGLES);
			{
				for (int i = 0; i < m_meshData.numIndices; i++)
				{
					int index = m_meshData.indices[i];

					if (m_meshData.uvs > 0)
						glTexCoord2f(m_meshData.uvs[index].x, m_meshData.uvs[index].y);

					if (m_meshData.normals > 0)
						glNormal3f(m_meshData.normals[index].x, m_meshData.normals[index].y, m_meshData.normals[index].z);

					if (m_meshData.positions > 0)
						glVertex3f(m_meshData.positions[index].x, m_meshData.positions[index].y, m_meshData.positions[index].z);

				}
			}
			glEnd();
		}
		glEndList();
	}
	else if (m_compileMode == LampMeshCompileMode::COMPILE_VBO || m_compileMode == LampMeshCompileMode::COMPILE_VAO)
	{

		//Create our vbo's
		if (m_meshData.positions > 0)
		{
			glGenBuffers(1, &m_vboPositions);
			glBindBuffer(GL_ARRAY_BUFFER, m_vboPositions);
			glBufferData(GL_ARRAY_BUFFER, m_meshData.numVertices * sizeof(vec3), m_meshData.positions, GL_STATIC_DRAW);
		}

		if (m_meshData.normals > 0)
		{
			glGenBuffers(1, &m_vboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, m_vboNormals);
			glBufferData(GL_ARRAY_BUFFER, m_meshData.numVertices * sizeof(vec3), m_meshData.normals, GL_STATIC_DRAW);
		}

		if (m_meshData.uvs > 0)
		{
			glGenBuffers(1, &m_vboUVs);
			glBindBuffer(GL_ARRAY_BUFFER, m_vboUVs);
			glBufferData(GL_ARRAY_BUFFER, m_meshData.numVertices * sizeof(vec2), m_meshData.uvs, GL_STATIC_DRAW);
		}

		if (m_meshData.boneAssignments > 0)
		{
			glGenBuffers(1, &m_vboBoneAssignments);
			glBindBuffer(GL_ARRAY_BUFFER, m_vboBoneAssignments);
			glBufferData(GL_ARRAY_BUFFER, m_meshData.numVertices * 4 * sizeof(GLint), m_meshData.boneAssignments, GL_STATIC_DRAW);
		}

		if (m_meshData.weights > 0)
		{
			glGenBuffers(1, &m_vboWeights);
			glBindBuffer(GL_ARRAY_BUFFER, m_vboWeights);
			glBufferData(GL_ARRAY_BUFFER, m_meshData.numVertices * 4 * sizeof(GLfloat), m_meshData.weights, GL_STATIC_DRAW);
		}

		if (m_meshData.indices > 0)
		{
			glGenBuffers(1, &m_vboIndices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshData.numIndices * sizeof(GLuint), m_meshData.indices, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//Only compile with vbo's that's odd!
		//We like them vertex arrays!
		if (m_compileMode == LampMeshCompileMode::COMPILE_VAO)
		{
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			if (m_meshData.positions > 0)
			{
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, m_vboPositions);
				glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vec3), 0);
			}

			if (m_meshData.normals > 0)
			{
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, m_vboNormals);
				glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vec3), 0);
			}

			if (m_meshData.uvs > 0)
			{
				glEnableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, m_vboUVs);
				glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(vec2), 0);
			}

			if (m_meshData.boneAssignments > 0)
			{
				glEnableVertexAttribArray(4);
				glBindBuffer(GL_ARRAY_BUFFER, m_vboBoneAssignments);
				//index, size, type, normalized, stride, pointer
				glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(GLint) * 4, 0);
			}

			if (m_meshData.weights > 0)
			{
				glEnableVertexAttribArray(5);
				glBindBuffer(GL_ARRAY_BUFFER, m_vboWeights);
				//index, size, type, normalized, stride, pointer
				glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(GLfloat) * 4, 0);
			}

			if (m_meshData.indices > 0)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndices);
			}

		}

		glBindVertexArray(0);
	}


	m_needCompile = false;
	m_isCompiled = true;
}

void LampMesh::render()
{

	//Check what mode we are rendering in
	if (m_isCompiled)
	{
		if (m_compileMode == LampMeshCompileMode::COMPILE_LEGACY)
		{
			//We only support triangles because we are bitches :o
			glBegin(GL_TRIANGLES);
			{
				for (int i = 0; i < m_meshData.numIndices; i++)
				{
					int index = m_meshData.indices[i];

					//Does this thing have bone assignments? if so this is a skinned mesh! oh dear!
					if (m_meshData.boneAssignments > 0)
					{
						//Get the skinning matrices
						vector<mat4>& skinningMatrices = m_material->getMatrix4Array("R_Bones");

						mat4 boneTransform(1.0f);
						for (int j = 0; j < 4; j++)
						{
							if (m_meshData.boneAssignments[(index * 4) + j] < 0)
								continue;

							//We need to obtain the skinned matrices somehow :o!?
							boneTransform += skinningMatrices[m_meshData.boneAssignments[(index * 4) + j]] * m_meshData.weights[(index * 4) + j];
						}
						vec4 skinnedPosition = boneTransform * vec4(m_meshData.positions[index].x, m_meshData.positions[index].y, m_meshData.positions[index].z, 1.0f);

						glVertex3v(skinnedPosition);
					}
					else
					{
						if (m_meshData.uvs > 0)
							glTexCoord2f(m_meshData.uvs[index].x, m_meshData.uvs[index].y);

						if (m_meshData.normals > 0)
							glNormal3f(m_meshData.normals[index].x, m_meshData.normals[index].y, m_meshData.normals[index].z);

						if (m_meshData.positions > 0)
							glVertex3f(m_meshData.positions[index].x, m_meshData.positions[index].y, m_meshData.positions[index].z);

					}

				}
			}
			glEnd();
		}
		else if (m_compileMode == LampMeshCompileMode::COMPILE_DL)
		{
			glCallList(m_displayList);
		}
		else if (m_compileMode == LampMeshCompileMode::COMPILE_VBO)
		{
			assert(false);
		}
		else if (m_compileMode == LampMeshCompileMode::COMPILE_VAO)
		{
			//Try to use our shader :p
			LampShaderProgram* pShaderProgram = m_material->getShader();
			if (pShaderProgram != NULL)
			{
				pShaderProgram->use();
				pShaderProgram->updateUniforms(*Lamp::getEngine().getRenderer(), m_material);
			}
			else
			{
				return; //UGH!
			}

			glBindVertexArray(m_vao);
			{
				glDrawElements(GL_TRIANGLES, m_meshData.numIndices, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);

			glUseProgram(0);
		}
	}
	else
	{
		printf("Oops forgot to compile mesh! :D");
	}

}