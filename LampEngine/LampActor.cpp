#include "stdafx.h"
#include "LampActor.hpp"

LampActor::LampActor() :
m_pMesh(0),
m_pSkeleton(0)
{

}

LampActor::~LampActor()
{

}

void LampActor::setMesh(LampMesh* pMesh)
{
	if (pMesh == NULL) return;
	m_pMesh = pMesh;
}

void LampActor::setSkeleton(LampSkeleton* pSkeleton)
{
	if (pSkeleton == NULL) return;
	m_pSkeleton = pSkeleton;
}

//######################
//# Animation Playback #
//######################
void LampActor::playAnimation(string animationName)
{
	//Find animation, then play it
}

//This allows us to play animations that is not in the repo too!
void LampActor::playAnimation(LampAnimation* pAnimation)
{

}

//##################
//# Animation Repo #
//##################
void LampActor::setAnimations(vector<LampAnimation*> vAnimations)
{
	m_vAnimations = vAnimations;
}

void LampActor::clearAnimations()
{
	m_vAnimations.clear();
}

void LampActor::addAnimation(LampAnimation* pAnimation)
{
	//Do a check if the animation already exists?


	m_vAnimations.push_back(pAnimation);
}

void LampActor::removeAnimation(LampAnimation* pAnimation)
{
	int idx = -1;
	for (unsigned int i = 0; i < m_vAnimations.size(); i++)
	{
		if (m_vAnimations[i] == pAnimation)
		{
			idx = (int)i;
			break;
		}
	}
	if (idx != -1)
	{
		m_vAnimations.erase(m_vAnimations.begin() + idx);
	}
}

LampAnimation* LampActor::getAnimation(string animationName)
{
	for (unsigned int i = 0; i < m_vAnimations.size(); i++)
	{
		if (m_vAnimations[i] == NULL)
			throw new std::runtime_error("[LampActor::getAnimation] Animation in list can't be null.");

		if (m_vAnimations[i]->getName() == animationName)
		{
			return m_vAnimations[i];
		}
	}
	return NULL;
}
