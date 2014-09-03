#pragma once

#include "stdafx.h"
#include <sstream>

namespace LampProject
{

	class LampOBJLoader
	{

	private:
		string m_Path;


	public:

		LampOBJLoader(string path) : m_Path(path)
		{

		}

		~LampOBJLoader()
		{

		}

		std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim)) {
				elems.push_back(item);
			}
			return elems;
		}


		std::vector<std::string> split(const std::string &s, char delim) {
			std::vector<std::string> elems;
			split(s, delim, elems);
			return elems;
		}

		inline vec3 parseVec3(string line)
		{
			//x y z
			float x, y, z;
			vector<string> splits = split(line, ' ');

			//Could do a whitespace check here, but we don't care.
			x = std::stof(splits[1].c_str());
			y = std::stof(splits[2].c_str());
			z = std::stof(splits[3].c_str());
			return vec3(x, y, z);
		}

		inline vec2 parseVec2(string line)
		{
			//x y z
			float x, y;
			vector<string> splits = split(line, ' ');

			//Could do a whitespace check here, but we don't care.
			x = std::stof(splits[1].c_str());
			y = std::stof(splits[2].c_str());
			return vec2(x, y);
		}

		LampMesh* loadMesh()
		{

			LampFileReadResult lfrr = readFile(m_Path);
			if (!lfrr.readComplete)
			{
				printf("Error reading OBJ file %s\n", m_Path.c_str());
				return NULL;
			}

			//This will read and parse the obj file!
			string workingStr = lfrr.fileContents;
			vector<string> lines;

			while (true) // SCARY =D
			{
				//Find next new line!
				int nextNewLine = workingStr.find("\n");

				if (nextNewLine == string::npos)
				{
					break; //BREAK!!
				}

				//Otherwise!
				string line = workingStr.substr(0, nextNewLine);
				workingStr = workingStr.substr(nextNewLine + 1);
				lines.push_back(line);
			}

			struct objface
			{
				int v1, n1, t1;
				int v2, n2, t2;
				int v3, n3, t3;
			};

			//Create a vector of lines
			vector<vec3> vertices;
			vector<vec3> normals;
			vector<vec2> uvs;
			vector<objface> faces;

			for (unsigned int i = 0; i < lines.size(); i++)
			{
				string& line = lines[i];

				if (line.find("v ") != string::npos)
				{
					//Vertex-Position
					vertices.push_back(parseVec3(line.substr(line.find("v ") + 1)));
				}
				else if (line.find("vn ") != string::npos)
				{
					//Vertex-Normal
					normals.push_back(parseVec3(line.substr(line.find("vn ") + 1)));
				}
				else if (line.find("vt ") != string::npos)
				{
					//Vertex-UV
					uvs.push_back(parseVec2(line.substr(line.find("vt ") + 1)));
				}
				else if (line.find("f ") != string::npos)
				{
					//Face
					string d = line.substr(2);
					vector<string> splits = split(d, ' ');

					objface f;
					vector<string> f1 = split(splits[0], '/');
					f.v1 = atoi(f1[0].c_str());
					f.t1 = atoi(f1[1].c_str());
					f.n1 = atoi(f1[2].c_str());

					vector<string> f2 = split(splits[1], '/');
					f.v2 = atoi(f2[0].c_str());
					f.t2 = atoi(f2[1].c_str());
					f.n2 = atoi(f2[2].c_str());

					vector<string> f3 = split(splits[2], '/');
					f.v3 = atoi(f3[0].c_str());
					f.t3 = atoi(f3[1].c_str());
					f.n3 = atoi(f3[2].c_str());

					faces.push_back(f);
				}
			}


			//Resort faces!
			vec3* newVertices = new vec3[faces.size() * 3];
			vec3* newNormals = new vec3[faces.size() * 3];
			vec2* newUvs = new vec2[faces.size() * 3];
			
			int off = 0;
			for (unsigned int i = 0; i < faces.size(); i++)
			{
				
				objface& f = faces[i];

				//Push back each one! :D
				//This makes duplicate vertices and all that, but we don't really care. 
				//We can do compression at a later stage using some filtering pipeline

				//v1
				vec3 v1 = vertices[f.v1 - 1];
				vec3 n1 = normals[f.n1 - 1];
				vec2 t1 = uvs[f.t1 - 1];

				newVertices[off] = v1;
				newNormals[off] = n1;
				newUvs[off] = t1;
				off++;

				//v2
				vec3 v2 = vertices[f.v2 - 1];
				vec3 n2 = normals[f.n2 - 1];
				vec2 t2 = uvs[f.t2 - 1];


				newVertices[off] = v2;
				newNormals[off] = n2;
				newUvs[off] = t2;
				off++;

				//v3
				vec3 v3 = vertices[f.v3- 1];
				vec3 n3 = normals[f.n3 - 1];
				vec2 t3 = uvs[f.t3 - 1];


				newVertices[off] = v3;
				newNormals[off] = n3;
				newUvs[off] = t3;
				off++;
			}

			//Construct a linearly forward index buffer
			uint32_t* indices = new uint32_t[faces.size() * 3];
			for (unsigned int i = 0; i < faces.size() * 3; i++)
			{
				uint32_t theint = (uint32_t)i;
				indices[i] = theint;
			}

			LampMesh* pMesh = new LampMesh();
			LampMeshData* pMeshData = pMesh->getMeshData();

			pMeshData->positions = newVertices;
			pMeshData->normals = newNormals;
			pMeshData->uvs = newUvs;
			pMeshData->indices = indices;
			pMeshData->numVertices = faces.size() * 3;
			pMeshData->numIndices = faces.size() * 3;

			return pMesh;
		}
	};

}