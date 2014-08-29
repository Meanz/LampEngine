#pragma once
#include "stdafx.h"
#include "LampSkeleton.hpp"

namespace LampProject
{



	struct LampModel
	{
		//The mesh of this model
		LampMesh* pMesh;
		//The skeleton reference for this model
		LampSkeleton* pSkeleton;
		//List of animations contained in this model
		std::vector<LampAnimation*> vAnimations;
	};

}