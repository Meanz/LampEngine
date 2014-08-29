#pragma once

#include "stdafx.h"

namespace LampProject
{

	struct LampBone
	{
		GLuint boneId;
		string boneName;
		mat4 identityMatrix;
		mat4 offsetMatrix;
	};

	class LampSkeleton
	{

	
	private:

		vector<LampBone> m_vBoneList;
		vector<mat4> m_vBoneTransforms;

	public:

		LampSkeleton();
		~LampSkeleton();

	};


	struct LampTrack
	{

	};

	class LampAnimation
	{

	private:
	public:

		string getName();

	};

}