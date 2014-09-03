#pragma once

#include "stdafx.h"
#include "LampAnimation.hpp"

namespace LampProject
{

	class LampActor : public LampGameObject
	{

	private:
		//The core mesh for the actor, from which the skeleton is attached to
		//
		LampMesh* m_pMesh;

		//The skeleton for this actor
		LampSkeleton* m_pSkeleton;

		//The repository of animations for this actor
		vector<LampAnimation*> m_vAnimations;

	public:
		LampActor();
		~LampActor();

		void setMesh(LampMesh* pMesh);
		void setSkeleton(LampSkeleton* pSkeleton);

		//Animation repo 
		void setAnimations(vector<LampAnimation*> pAnimations);
		void clearAnimations();
		void addAnimation(LampAnimation* pAnimation);
		void removeAnimation(LampAnimation* pAnimation);
		LampAnimation* getAnimation(string animationName);

		//Animation playback
		void playAnimation(string animationName);
		void playAnimation(LampAnimation* pAnimation);
	};

}