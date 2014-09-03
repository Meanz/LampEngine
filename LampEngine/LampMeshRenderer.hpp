#pragma once

#include "stdafx.h"

namespace LampProject
{
	class LampMeshRenderer : public LampNodeComponent
	{

	private:
		LampMesh* m_pMesh;

	public:
		LampMeshRenderer(LampMesh* mesh) : m_pMesh(mesh)
		{

		}

		void onFrame()
		{
			if (m_pMesh == NULL)
			{
				//Nothing to do
				return;
			}
			if (!m_pMesh->isCompiled())
			{
				m_pMesh->compile();
			}
			m_pMesh->render();
		}

		virtual int type() { return LampNodeComponentType::MESH_RENDERER; };
	};
}