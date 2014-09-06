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
		vector<mat4> m_vSkinningMatrices;

	public:
		LampSkeletalMeshRenderer(LampMesh* pMesh, LampSkeleton* pSkeleton) : m_pMesh(pMesh), m_pSkeleton(pSkeleton)
		{
			m_vSkinningMatrices.resize(pSkeleton->getBones().size());
		}

		~LampSkeletalMeshRenderer()
		{

		}

		void calculateSkinningMatrices()
		{
			for (unsigned int i = 0; i < m_pSkeleton->getBones().size(); i++)
			{
				mat4& invBindMatrix = m_pSkeleton->getBones()[i]->invBindMatrix;
				mat4& globalTransform = m_pSkeleton->getBones()[i]->globalTransform;
				m_vSkinningMatrices[i] = invBindMatrix * globalTransform;
			}
		}

		void onFrame()
		{
			if (m_pSkeleton == NULL)
			{
				printf("Skeleton is null\n");
				return;
			}

			if (!m_pMesh->isCompiled())
			{
				m_pMesh->compile();
			}

			//Temp global transform calculation1
			m_pSkeleton->calcGlobalTransform();

			//Calculate skinning matrices!
			calculateSkinningMatrices();

			//Send the matrices to the shader

			//Until we figure out something more clever
			m_pMesh->getMaterial()->setMatrix4Array("R_Bones", m_vSkinningMatrices);


			m_pMesh->render();
		}

		virtual int type() { return LampNodeComponentType::MESH_RENDERER; };
	};
}