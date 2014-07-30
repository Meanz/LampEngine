#pragma once
#include "stdafx.h"
#include <vector>
#include "LampMesh.hpp"
#include <typeinfo>

namespace LampProject {

	enum LampNodeComponentType
	{
		BASE = 0,
		MESH_RENDERER = 1
	};

	class LampNodeComponent
	{
	public:
		virtual void onTick() {};
		virtual void onFrame() {};
		virtual int type() { return LampNodeComponentType::BASE; };
	};

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
			m_pMesh->render();
		}

		virtual int type() { return LampNodeComponentType::MESH_RENDERER; };
	};

	class LampGameObject {

	private:
		std::vector<LampGameObject*> m_vChildren;
		std::vector<LampNodeComponent*> m_vComponents;
		LampGameObject* m_pParent;
		LampTransform m_transform;

	public:

		LampGameObject();
		~LampGameObject();

		void addComponent(LampNodeComponent* component);
		void removeComponent(LampNodeComponent* component);
		void removeComponent(LampNodeComponentType type);

		void attach(LampGameObject* child);
		void detach(LampGameObject* child);
		void detach();

		//Internal functions for ticking/rendering
		void doTick();
		void doFrame();

		//These are here so each node type can hook on to these events
		virtual void onTick() {};
		virtual void onFrame() {};

	};

}