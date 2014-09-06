#include "stdafx.h"
#include "LampMWMLoader.hpp"
#include "LampAnimation.hpp"
#include "LampSkeletalMesh.hpp"

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
	float x = m_buffer->getFloat();
	float y = m_buffer->getFloat();
	float z = m_buffer->getFloat();
	return vec3(x, y, z);
}

inline vec2 LampMWMLoader::getVec2()
{
	float x = m_buffer->getFloat();
	float y = m_buffer->getFloat();
	return vec2(x, y);
}

LampMesh* LampMWMLoader::loadModel()
{

	//Read file :D
	LampBinaryFileReadResult readResult = readBinaryFile(m_filePath);

	if (!readResult.readComplete)
	{
		return NULL;
	}

	m_buffer = new LampBinaryBuffer(&readResult.bytes);

	if (m_buffer == NULL)
	{
		return NULL;
	}


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

	GLfloat* weights = NULL;
	GLint* boneAssignments = NULL;
	if (hasBoneAssignments)
	{
		//Not sure what this is supposed to mean o.O
		short numBones = m_buffer->getShort();
		for (short i = 0; i < numBones; i++)
		{
			m_buffer->getString();
		}

		//Default
		short weightsPerBone = m_buffer->getShort();
		if (weightsPerBone != 4)
		{
			printf("Not 4! =O %i\n", weightsPerBone);
		}
		//weightsPerBone ignore it, engine defaults to 4
		weights = new GLfloat[numVertices * 4];
		boneAssignments = new GLint[numVertices * 4];

		for (int i = 0; i < numVertices; i++)
		{
			for (int j = 0; j < weightsPerBone; j++)
			{
				if ((i *weightsPerBone + j) > numVertices * 4){
					printf("DAAAANGER!!!!!\n");
				}

				int boneAssignment = m_buffer->getInt();
				float weight = m_buffer->getFloat();

				if (weight < 0.00001)
					weight = 0;

				boneAssignments[(i * weightsPerBone) + j] = boneAssignment;
				weights[(i * weightsPerBone) + j] = weight;
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
	if (hasBoneAssignments)
	{
		pMeshData->weights = weights;
		pMeshData->boneAssignments = boneAssignments;
	}


	return pMesh;
}

void LampMWMLoader::loadMesh()
{

}

struct _bone
{
	string name;
	string parentName;
	vec3 pos;
	vec3 rot;
	float ang;
	_bone* parent;
	vector<_bone> children;
	int index;
};


void assignChildren(vector<_bone>& bones, _bone& bone)
{
	for (unsigned int i = 0; i < bones.size(); i++)
	{
		_bone& child = bones[i];
		if (child.parentName == bone.name)
		{
			child.parent = &bone;
			bone.children.push_back(child);
		}
	}
	for (unsigned int i = 0; i < bone.children.size(); i++)
	{
		assignChildren(bones, bone.children[i]);
	}
}

LampSkeleton* LampMWMLoader::loadSkeleton()
{

	printf("Reading skeletor: %s\n", m_filePath.c_str());

	//Read file :D
	LampBinaryFileReadResult readResult = readBinaryFile(m_filePath);

	if (!readResult.readComplete)
	{
		printf("Unable to read skeletor: %s\n", m_filePath.c_str());
		return NULL;
	}

	m_buffer = new LampBinaryBuffer(&readResult.bytes);

	if (m_buffer == NULL)
	{
		return NULL;
	}

	int numBones = m_buffer->getShort();
	vector<_bone> bones(numBones);

	for (int i = 0; i < numBones; i++)
	{
		_bone bone;

		bone.name = m_buffer->getString();
		bone.parentName = m_buffer->getString();

		bone.pos = getVec3();
		bone.rot = getVec3();
		bone.ang = m_buffer->getFloat();

		bones[i] = bone;
	}

	//Convert the data into our engine format
	LampSkeleton* pSkeleton = new LampSkeleton();

	//Find the top bones, we want to create a hierarchical system for the bones!
	vector<_bone> topBones;
	for (unsigned int i = 0; i < bones.size(); i++)
	{
		if (bones[i].parentName == "")
		{
			topBones.push_back(bones[i]);
		}
	}

	//
	// Establish parent/child relations
	//

	//Assign children
	for (unsigned int i = 0; i < topBones.size(); i++)
	{
		assignChildren(bones, topBones[i]);
	}

	//Index the bones, this is only really for salem, because it uses indexed
	//Bone lists... Gah, they should just refer to them by names >_>

	vector<_bone> _bones = bones;
	vector<_bone> finished;

	int idx = 0;
	while (bones.size() > 0)
	{
		bool didFindParent = false;

		for (unsigned int i = 0; i < bones.size(); i++)
		{
			bool foundParent = false;
			_bone& b = bones[i];
			if (b.parentName == "")
			{
				foundParent = true;
			}
			else
			{
				foundParent = false;
				for (unsigned int j = 0; j < _bones.size(); j++)
				{
					_bone& p = _bones[j];
					if (p.name == b.parentName)
					{
						foundParent = true;
						break;
					}
				}
			}
			if (foundParent)
			{
				b.index = idx++;
				finished.push_back(b);
				didFindParent = true;
				bones.erase(bones.begin() + i);
				break;
			}
		}
		if (!didFindParent)
		{
			assert(false);
		}

	}

	//We have a sorted bone list... 
	//Convert it into lamp bones
	vector<LampBone*> lbones;
	for (unsigned int i = 0; i < finished.size(); i++)
	{
		LampBone* b = new LampBone();
		_bone& f = finished[i];
		b->boneId = i;
		b->parentId = -1;
		for (unsigned int j = 0; j < finished.size(); j++)
		{
			if (finished[j].name == finished[i].parentName)
			{
				b->parentId = j;
			}
		}
		b->boneName = f.name;
		//Create our matrix
		mat4 positionMatrix = glm::translate(mat4(1.0f), f.pos) * glm::mat4_cast(glm::angleAxis(f.ang, f.rot)); //Ignore scaling :D

		b->localTransform = positionMatrix;

		lbones.push_back(b);
	}

	//Second sorting step
	for (unsigned int i = 0; i < lbones.size(); i++)
	{
		if (lbones[i]->parentId != -1)
		{
			lbones[i]->pParent = lbones[lbones[i]->parentId];
		}
	}

	//Third sorting step, assign children to the lamp bones

	pSkeleton->setBones(lbones);

	return pSkeleton;
}

LampAnimation* LampMWMLoader::loadAnimation()
{

	printf("Reading animation: %s\n", m_filePath.c_str());

	//Read file :D
	LampBinaryFileReadResult readResult = readBinaryFile(m_filePath);

	if (!readResult.readComplete)
	{
		printf("Unable to read animation: %s\n", m_filePath.c_str());
		return NULL;
	}

	m_buffer = new LampBinaryBuffer(&readResult.bytes);

	if (m_buffer == NULL)
	{
		return NULL;
	}

	//See comments below
	struct _Frame
	{
		float time;
		vec3 pos;
		float ang;
		vec3 rot;
	};

	//Simple temporary structure for a track
	//Seeing as this structure is not necessarily the engine structure
	//Which is yet to be built, a temporary structure was the way to go
	struct _Track
	{
		string boneName;
		int numFrames;
		vector<_Frame> frames;
	};

	float animationTime = m_buffer->getFloat();
	float animationSpeed = m_buffer->getFloat();

	int numTracks = m_buffer->getShort();
	vector<_Track> tracks(numTracks);

	for (int i = 0; i < numTracks; i++)
	{
		_Track track;
		track.boneName = m_buffer->getString();
		track.numFrames = m_buffer->getShort();
		track.frames.resize(track.numFrames);
		for (int j = 0; j < track.numFrames; j++)
		{
			_Frame f;
			f.time = m_buffer->getFloat();
			f.pos = getVec3();
			f.ang = m_buffer->getFloat();
			f.rot = getVec3();
			track.frames.push_back(f);
		}
		tracks[i] = (track);
	}


	//Convert all this data into a topological sorted array for
	//The internal animation system

	LampAnimation* pAnimation = new LampAnimation();

	string animName = m_filePath.substr(m_filePath.find_last_of('/') + 1);
	animName = animName.substr(0, animName.find('.'));

	pAnimation->name = animName;//Err we really don't have anything to go on here, so let's just take the filename
	pAnimation->speed = animationSpeed;
	pAnimation->time = animationTime;

	//Now do the frames!
	for (unsigned int i = 0; i < tracks.size(); i++)
	{
		LampTrack track;
		for (unsigned int j = 0; j < tracks[i].frames.size(); j++)
		{
			_Frame& _frame = tracks[i].frames[j];
			LampFrame frame;
			frame.pos = tracks[i].frames[j].pos;
			frame.rot = glm::angleAxis(_frame.ang, _frame.rot);
			frame.scale = vec3(1.0f);
			frame.timestamp = _frame.time;
			track.vFrames.push_back(frame);
		}
		pAnimation->vTracks.push_back(track);
	}

	return pAnimation;
}