#include "stdafx.h"
#include "LampTypes.hpp"

void applyColor(LampColor& c)
{
	glColor4f(c.r, c.g, c.b, c.a);
}