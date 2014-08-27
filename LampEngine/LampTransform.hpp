#pragma once
#include "stdafx.h"

namespace LampProject
{

	class LampTransform
	{

	private:

		//
		vec3 position;
		quat rotation;
		vec3 scale;

		//Local transformation matrix ( transform space, model space, w/e )
		mat4 local;
		//Global transformation matrix ( world space ) 
		mat4 global;

		bool hasChanged;

	public:

		//Cool initializer, didn't know they had these = default value things.
		LampTransform(vec3 _position = vec3(), quat _rotation = quat(), vec3 _scale = vec3(1.0f)) :
			position(_position),
			rotation(_rotation),
			scale(_scale),
			local(1.0f),
			global(1.0f),
			hasChanged(true)
		{}

		~LampTransform() {}

		inline void flagChange()
		{
			hasChanged = true;
		}

		//Ge the local transform matrix for this transform
		mat4& getLocal()
		{
			return local;
		}

		//Get the global transform matrix for this Transform
		mat4& getGlobal()
		{
			return global;
		}

		//Pointer version
		//Important, changes done here will not flag has changed
		mat4* getGlobalPtr()
		{
			return &global;
		}

		vec3 getPosition()
		{
			return position;
		}

		void setScale(float x, float y, float z)
		{
			scale.x = x;
			scale.y = y;
			scale.z = z;
			flagChange();
		}

		void setScale(float f)
		{
			scale.x = f;
			scale.y = f;
			scale.z = f;
			flagChange();
		}

		void setPosition(vec3 _position)
		{
			position = _position;
			flagChange();
		}

		//Translate this Transform by the given values
		void translate(float x, float y, float z)
		{
			position.x += x;
			position.y += y;
			position.z += z;
			flagChange();
		}

		//Translate this Transform by the given vector
		void translate(vec3 translation)
		{
			position += translation;
			flagChange();
		}

		//do some weird stuff here
		void rotate(float angle, vec3 axis)
		{
			//Should work, but is it the fastest way?
			//Granted "the fastest" is a bad use of words
			//So, is there any obvious faster ways?
			//I suck at assembly so don't even challenge me here.
			quat newQuat = glm::angleAxis(angle, axis);
			rotation = rotation * newQuat;
			flagChange();
		}

		//Yeah, this won't happen just yet,
		//Besides I've heard it's ultra expensive.
		void extractFrom(mat4 matrix)
		{

		}

		//Calculate the global and local matrix for this transform
		void calculateGlobal(mat4* parent)
		{
			if (!hasChanged)
			{
				return; 
			}

			//Calculate local
			local = glm::mat4_cast(rotation) * glm::translate(mat4(1.0f), position);

			if (parent == NULL)
			{
				global = local;
			}
			else
			{
				global = *parent * local;
			}

			hasChanged = false; //We did update
		}

		//Should this use global or local ?
		//Current position * newPosition
		//Let's use global until anything else is needed, then we can revise.

		//This shoooould work? I dunno really, 
		//We would have to do the operations on each component
		//Eg
		//
		//newT.position = translate(this.position * other.position)
		//newT.rotation = translate(this.rotation * other.rotation)
		//newT.scale = translate(this.scale * other.scale)
		//However those would all be global, need to rethink this!
		//REVISE LATER BRO!
		//TODO: Read this
		//
		//Revised2: 
		//Changed the return type to a matrix
		//Basically the transformation matrix of this one * the other transforms local matrix
		mat4 operator* (LampTransform& other)
		{
			return global * other.local;
		}

		//This should allow us to do some nifty things
		mat4 operator* (mat4 other)
		{
			return global * other;
		}
	};

}