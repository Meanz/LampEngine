#pragma once

#include "stdafx.h"

namespace LampProject
{

	struct LampBone
	{
		GLuint boneId;
		GLuint parentId;
		string boneName;
		mat4 invBindMatrix;
		LampBone* pParent;
		vector<LampBone*> vChildren;

		//This is instance information, should it be here?
		mat4 globalTransform;
		mat4 localTransform;

		LampBone() : pParent(NULL)
		{

		}

		~LampBone()
		{

		}
	};

	class LampSkeleton
	{

	
	private:

		//Indexed list of bones
		vector<LampBone*> m_vBoneList;
		//The list of top bones for hierarchical traversing
		vector<LampBone*> m_vTopBones;

	public:

		LampSkeleton()
		{
			//Calculate inverse bind matrices!

		}
		~LampSkeleton()
		{

		}

		void recurCalcGlobalTransform(LampBone& bone)
		{
			if (bone.pParent != NULL)
			{
				bone.globalTransform = bone.pParent->globalTransform * bone.localTransform;
			}
			else
			{
				bone.globalTransform = bone.localTransform;
			}
			for (unsigned int i = 0; i < bone.vChildren.size(); i++)
			{
				recurCalcGlobalTransform(*bone.vChildren[i]);
			}
		}

		void calcGlobalTransform()
		{
			vector<LampBone*>& bones = m_vTopBones;
			for (unsigned int i = 0; i < bones.size(); i++)
			{
				recurCalcGlobalTransform(*bones[i]);
			}
		}

		vector<LampBone*>& getTopBones()
		{
			return m_vTopBones;
		}

		vector<LampBone*>& getBones()
		{
			return m_vBoneList;
		}

		void setBones(vector<LampBone*>& vBoneList)
		{
			m_vBoneList = vBoneList;

			//Find top bones!
			for (unsigned int i = 0; i < vBoneList.size(); i++)
			{
				if (vBoneList[i]->pParent == NULL)
				{
					m_vTopBones.push_back(vBoneList[i]);
				}
			}

			//Calculate initial transforms
			calcGlobalTransform();

			//Calculate the inverse transforms
			for (unsigned int i = 0; i < m_vBoneList.size(); i++)
			{
				LampBone& bone = *m_vBoneList[i];

				bone.invBindMatrix = glm::inverse(bone.globalTransform);
			}
		}

	};

}