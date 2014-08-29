#pragma once

#include "stdafx.h"

namespace LampProject
{

	struct LampBone
	{
		GLuint boneId;
		std::string boneName;
		mat4 identityMatrix;
		mat4 offsetMatrix;
	};

	class LampSkeleton
	{

	
	private:

		std::vector<LampBone> m_vBoneList;
		std::vector<mat4> m_vBoneTransforms;

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

	};

}