#pragma once
#include "stdafx.h"

namespace LampProject
{
	enum LampImageFormat
	{
		RGB = GL_RGB,
		RGBA = GL_RGBA
	};

	class LampTexture
	{
		//The OpenGL texture id
	private:
		GLuint m_glId;

	public:
		
		//The internal format of this Texture
		LampImageFormat m_Format;
		GLuint m_width;
		GLuint m_height;
		std::string m_id; //The string id of the texture

		LampTexture();
		~LampTexture();

		//Check's if this is a valid texture, basically m_glId > 0
		bool isValid();

		//Get the OpenGL id for this texture
		int getGLId();

		//Generates an opengl texture
		void generateGLId();

		//Bind's this texture to texture unit0
		void bind();
	};

}