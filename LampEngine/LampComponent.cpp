#include "stdafx.h"
#include "LampComponent.hpp"

namespace LampProject
{

	LampComponent::LampComponent() : m_pParent(NULL)
	{

	}

	LampComponent::~LampComponent()
	{
		//We have m_pParent as a pointer, 
		//But!!
		//We are not handling the removal of the pointer here!
		//Here we should parse through all the children, and delete them!

	}

	Area& LampComponent::getArea()
	{
		return m_Area;
	}

	void LampComponent::setArea(Area area)
	{
		m_Area = area;
	}

	LampComponent* LampComponent::getParent()
	{
		return m_pParent;
	}

	void LampComponent::setParent(LampComponent* pParent)
	{
		if (m_pParent != NULL)
		{
			//We need to remove this component from the other parent
			if (m_pParent == pParent)
			{
				//Ergh, we don't need to do anything >.>
				return;
			}

			//Insurance!
			m_pParent->remove(this);

			//Now that our old parent is not tracking us, we can add us to the new parent
			m_pParent = pParent;

		}
		else
		{
			//Okay, our current parent is null, so not much has to be done
			m_pParent = pParent;
		}
	}

	void LampComponent::add(LampComponent* pComponent)
	{
		if (pComponent == NULL) return;
		m_vAddQueue.push_back(pComponent);
	}

	void LampComponent::remove(LampComponent* pComponent)
	{
		if (pComponent == NULL) return;
		m_vRemoveQueue.push_back(pComponent);
	}

	void LampComponent::remove()
	{
		if (m_pParent != NULL)
		{
			m_pParent->remove(this);
		}
	}

	bool LampComponent::has(LampComponent* pComponent)
	{
		for (unsigned int i = 0; i < m_vChildren.size(); i++)
		{
			if (m_vChildren[i] == pComponent)
			{
				return true;
			}
		}
		return false;
	}

	void LampComponent::update()
	{
		//Handle input ?

		//Do remove queue first!
		for (unsigned int i = 0; i < m_vRemoveQueue.size(); i++)
		{
			//Get the index of the thingy in children
			int idx = -1;
			for (unsigned int j = 0; j < m_vChildren.size(); j++)
			{
				if (m_vChildren[j] == m_vRemoveQueue[i])
				{
					idx = j;
					break;
				}
			}
			if (idx != -1)
			{
				m_vChildren.erase(m_vChildren.begin() + idx);
			}
		}
		m_vRemoveQueue.clear();

		//Do the add queue
		for (unsigned int i = 0; i < m_vAddQueue.size(); i++)
		{
			m_vChildren.push_back(m_vAddQueue[i]);
		}
		m_vAddQueue.clear();
	}

	void LampComponent::draw(LampGUIPainter& pPainter)
	{
		//Handling drawing!?
	}
}