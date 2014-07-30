#pragma once

//Forward declarations

//Forward declaration due to glm and sdl not being friends
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::quat quat;

//Some static colors
#define RED LampColor(1.0f, 0.0f, 0.0f)
#define GREEN LampColor(0.0f, 1.0f, 0.0f)
#define BLUE LampColor(0.0f, 0.0f, 1.0f)

#define WHITE LampColor(1.0f, 1.0f, 1.0f)
#define BLACK LampColor(0.0f, 0.0f, 0.0f)

union LampColor
{

	struct
	{
		float r;
		float g;
		float b;
		float a;
	};

	struct
	{
		float components[4];
	};

	LampColor(float r, float g, float b, float a)
	{
		components[0] = r;
		components[1] = g;
		components[2] = b;
		components[3] = a;
	};

	LampColor(float r, float g, float b)
	{
		components[0] = r;
		components[1] = g;
		components[2] = b;
		components[3] = 0.0f;
	};

};
