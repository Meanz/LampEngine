#pragma once

#include "stdafx.h"
#include "LampSkeleton.hpp"

namespace LampProject
{

	//
	//A simple structure for holding a keyframe of an animation
	//
	struct LampFrame
	{
		float timestamp;
		vec3 pos;
		quat rot;
		vec3 scale;
	};

	//
	// Holds the frames of a bone
	//
	struct LampTrack
	{
		string boneName; //A reference to the bone we are modifying
		int boneId; //A reference to the bone we are modifying
		vector<LampFrame> vFrames; //The list of frames in this track
	};


	//
	// Describes an animation
	//
	struct LampAnimation
	{
		string name; //The name of this animation
		float time; //The length of this animation
		float speed; //The initial speed of this animation
		vector<LampTrack> vTracks; //The list of tracks in this animation
	};

	//
	// Handles the animation of a skeleton
	//
	class LampAnimator
	{
	private:
		LampSkeleton* pSkeleton;
		LampAnimation* pAnimation;

	public:

		void playAnimation(LampAnimation* pAnimation);

		//This will update the skeleton
		void doTick()
		{

			//Time ticks

			//Update each track of the animation
			for (unsigned int i = 0; i < pAnimation->vTracks.size(); i++)
			{
				LampTrack& track = pAnimation->vTracks[i];

				//Simple error test
				if (track.vFrames.size() == 0)
				{
					throw new std::runtime_error("No frames in track! BOGUS!");
				}

				//What frame are we on?
				unsigned int frameId = 0, nextFrameId = 0;

				//Do fancy compjutations here
				LampFrame& frame = track.vFrames[frameId];
				LampFrame& nextFrame = track.vFrames[nextFrameId];

				//Do interpolation between this frame and next frame

			}

		}

	};
}