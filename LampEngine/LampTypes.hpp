#pragma once

//Forward declarations

//Forward declaration due to glm and sdl not being friends
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::quat quat;

#define UNIT_X vec3(1.0f, 0.0f, 0.0f)
#define UNIT_Y vec3(0.0f, 1.0f, 0.0f)
#define UNIT_Z vec3(0.0f, 0.0f, 1.0f)

//Some static colors
#define RED LampColor(1.0f, 0.0f, 0.0f, 1.0f)
#define GREEN LampColor(0.0f, 1.0f, 0.0f, 1.0f)
#define BLUE LampColor(0.0f, 0.0f, 1.0f, 1.0f)

#define WHITE LampColor(1.0f, 1.0f, 1.0f, 1.0f)
#define BLACK LampColor(0.0f, 0.0f, 0.0f, 1.0f)

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

	LampColor()
	{
		components[0] = 0.0f;
		components[1] = 0.0f;
		components[2] = 0.0f;
		components[3] = 1.0f;
	}

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
		components[3] = 1.0f;
	};

};

void applyColor(LampColor& c);

struct Area
{

	int x;
	int y;
	int width;
	int height;

	//Default ctor
	Area()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Area(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {}

	~Area()
	{
		//No pointers? So we don't need this?
	}

};