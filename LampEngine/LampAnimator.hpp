#pragma once

#include "stdafx.h"
#include "LampSkeleton.hpp"
#include "LampAnimation.hpp"

namespace LampProject
{


	class LampAnimator : public LampNodeComponent
	{
	private:
		//The skeleton this animator is 
		LampSkeleton* m_pSkeleton;
		LampAnimation* m_pAnimation;
		float m_CurrentTime;

	public:

		LampAnimator() : m_pSkeleton(0), m_pAnimation(0)
		{

		}

		void playAnimation(LampAnimation* pAnimation)
		{

		}

		virtual void onFrame()
		{
			//Are we playing any animation
			if (m_pAnimation != NULL)
			{
				float nt = m_CurrentTime + (float)Lamp::getEngine().getFrameTime();
				nt = fmod(nt, m_pAnimation->time);
				m_CurrentTime = nt;

				if (m_CurrentTime > m_pAnimation->time)
				{
					for (unsigned int trackNo = 0; trackNo < m_pAnimation->vTracks.size(); trackNo++)
					{
						LampTrack& track = m_pAnimation->vTracks[trackNo];
						LampBone* bone = m_pSkeleton->findBone(track.boneName);
						if (bone != NULL)
						{
							LampFrame* currentFrame;
							LampFrame* nextFrame;
							float currentTime, nextTime;
							int iCurrentFrame, iNextFrame = track.vFrames.size();

							while (true)
							{
								int frameId = iCurrentFrame + ((iNextFrame - iCurrentFrame) >> 1);
								currentTime = track.vFrames[frameId].timestamp;
								nextTime = (frameId < track.vFrames.size() - 1) ? (track.vFrames[frameId + 1].timestamp) : m_pAnimation->time;
								if (currentTime > m_CurrentTime)
								{
									iNextFrame = frameId;
								}
								else if (nextTime < m_CurrentTime)
								{
									iCurrentFrame = frameId + 1;
								}
								else
								{
									currentFrame = &track.vFrames[frameId];
									nextFrame = &(track.vFrames[(frameId + 1) % track.vFrames.size()]);
								}
							}

							float deltaTime = (currentFrame->timestamp - nextFrame->timestamp);


						}
					}
				}
			}
		}

		virtual int type() { return LampNodeComponentType::ANIMATOR; };

	};

}