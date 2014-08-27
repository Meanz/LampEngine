#include "stdafx.h"
#include "LampGameObject.hpp"


LampGameObject::LampGameObject() :
m_pParent(0)
{

}

LampGameObject::~LampGameObject()
{

}

LampTransform* LampGameObject::getTransform()
{
	return &m_transform;
}

void LampGameObject::addComponent(LampNodeComponent* component)
{
	assert(component != NULL); //This would be silly :o

	//TODO: Check if component is already here

	m_vComponents.push_back(component);
}

void LampGameObject::removeComponent(LampNodeComponent* component)
{
	//Search for this component and then remove it
	int idx = -1;
	for (unsigned int i = 0; i < m_vComponents.size(); i++)
	{
		if (m_vComponents[i] == component)
		{
			idx = i;
			break;
		}
	}
	if (idx != -1)
	{
		m_vComponents.erase(m_vComponents.begin() + idx);
	}
}

void LampGameObject::removeComponent(LampNodeComponentType type)
{
	std::vector<LampNodeComponent*> toRemove;
	for (unsigned int i = 0; i < m_vComponents.size(); i++)
	{
		if (m_vComponents[i]->type() == type)
		{
			toRemove.push_back(m_vComponents[i]);
		}
	}
	for (unsigned int i = 0; i < toRemove.size(); i++)
	{
		int idx = -1;
		for (unsigned int j = 0; j < m_vComponents.size(); j++)
		{
			if (m_vComponents[j] == toRemove[i])
			{
				idx = j;
				break;
			}
		}
		if (idx != -1) 
		{
			m_vComponents.erase(m_vComponents.begin() + idx);
		}
	}
}

void LampGameObject::attach(LampGameObject* child)
{
	//Check if this child is already attached to this parent
	if (child->m_pParent == this)
	{
		//We got some serious trouble here.
		//TODO: Add some kind of error reporting system
		return;
	}

	child->m_pParent = this;
	m_vChildren.push_back(child);
}

void LampGameObject::detach(LampGameObject* child)
{
	int idx = -1;
	for (unsigned int i = 0; i < m_vChildren.size(); i++)
	{
		if (m_vChildren[i] == child)
		{
			//Is this safe :o?
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		//Perform error reporting
		//YES WE GOOD AT EXPLAINING SHIT
		printf("Tried to remove a child node from a node, but the child node was not attached to the node it was trying to remove itself from.");
		return;
	}
	m_vChildren.erase(m_vChildren.begin() + idx);

	child->m_pParent = NULL;
}

void LampGameObject::detach()
{
	if (m_pParent != NULL)
	{
		m_pParent->detach(this);
	}
	for (unsigned int i = 0; i < m_vChildren.size(); i++)
	{
		m_vChildren[i]->m_pParent = NULL; //Set parent to NULL, do some reporting here maybe? 
		//Eg: node->notify(); 
	}
}

void LampGameObject::doTick()
{

	//Do culling in tick? 
	//Yes please, less culling calls

	//Update our transform

	//Get parent transform matrix
	mat4* ptrParentMatrix = NULL;
	if (m_pParent != NULL)
	{
		ptrParentMatrix = m_transform.getGlobalPtr();
	}
	m_transform.calculateGlobal(ptrParentMatrix);

	//Call our on tick function
	onTick();

	//Tell all our components that this game object is being ticked
	for (unsigned int i = 0; i < m_vComponents.size(); i++)
	{
		m_vComponents[i]->onTick();
	}

	//Give the message to all our children
	for (unsigned int i = 0; i < m_vChildren.size(); i++)
	{
		m_vChildren[i]->doTick();
	}

}

void LampGameObject::doFrame()
{

	//if is culled return;
	//Give the renderer our transform
	Lamp::getEngine().getRenderer()->setTransform(&m_transform);

	//Call our on frame function
	onFrame();

	//Tell all our components that this game object is ready to be drawn or whatever
	for (unsigned int i = 0; i < m_vComponents.size(); i++)
	{
		m_vComponents[i]->onFrame();
	}

	//Give the message to all our children
	for (unsigned int i = 0; i < m_vChildren.size(); i++)
	{
		m_vChildren[i]->doFrame();
	}

}