#pragma once

#include "stdafx.h"

namespace LampProject
{

	struct LampBone
	{
		GLuint boneId;
		GLuint parentId;
		string boneName;
		mat4 identityMatrix;
		mat4 offsetMatrix;

		//This is instance information, should it be here?
		mat4 globalTransform;
	};

	class LampSkeleton
	{

	
	private:

		vector<LampBone> m_vBoneList;
		vector<mat4> m_vBoneTransforms;

	public:

		LampSkeleton()
		{

		}
		~LampSkeleton()
		{

		}

		void setBones(vector<LampBone> vBoneList)
		{
			m_vBoneList = vBoneList;
		}

	};

}