#pragma once

#include "stdafx.h"
#include "LampSkeleton.hpp"

namespace LampProject
{
	class LampMeshRenderer : public LampNodeComponent
	{

	private:
		LampMesh* m_pMesh;
		LampSkeleton* m_pSkeleton;

	public:
		LampMeshRenderer(LampMesh* pMesh, LampSkeleton* pSkeleton) : m_pMesh(pMesh), m_pSkeleton(pSkeleton)
		{

		}

		void onFrame()
		{
			m_pMesh->render();
		}

		virtual int type() { return LampNodeComponentType::MESH_RENDERER; };
	};
}