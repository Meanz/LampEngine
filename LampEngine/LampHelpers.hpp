#pragma once

#include "stdafx.h"

namespace LampProject
{
	inline void glVertex3v(vec4 v)
	{
		glVertex3f(v.x, v.y, v.z);
	}

	inline void glVertex4v(vec4 v)
	{
		glVertex4f(v.x, v.y, v.z, v.w);
	}

	inline void glVertex3v(vec3 v)
	{
		glVertex3f(v.x, v.y, v.z);
	}

	inline void glVertex2v(vec2 v)
	{
		glVertex2f(v.x, v.y);
	}

	inline void glTexCoord2v(vec2 v)
	{
		glTexCoord2f(v.x, v.y);
	}

}
