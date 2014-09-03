#pragma once

#include "stdafx.h"
#include "LampSkeleton.hpp"

namespace LampProject
{
	class LampSkeletalMeshRenderer : public LampNodeComponent
	{

	private:
		LampMesh* m_pMesh;
		LampSkeleton* m_pSkeleton;

	public:
		LampSkeletalMeshRenderer(LampMesh* pMesh, LampSkeleton* pSkeleton) : m_pMesh(pMesh), m_pSkeleton(pSkeleton)
		{
			
		}

		~LampSkeletalMeshRenderer()
		{

		}

		void onFrame()
		{
			if (!m_pMesh->isCompiled())
			{
				m_pMesh->compile();
			}
			m_pMesh->render();
		}

		virtual int type() { return LampNodeComponentType::MESH_RENDERER; };
	};
}