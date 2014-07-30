#pragma once

#include "stdafx.h"

namespace LampProject
{


	class LampTextureLoader
	{

	public:

		static LampTexture* loadTexture(std::string filePath)
		{
			SDL_Surface* surface = IMG_Load(filePath.c_str());
			if (surface == NULL)
			{
				printf("Could not load texture %s \n" , filePath.c_str());
				return 0;
			}
			else
			{
				LampTexture* texture = new LampTexture();
				texture->generateGLId();
				texture->m_width = surface->w;
				texture->m_height = surface->h;

				if (!texture->isValid())
				{
					SDL_FreeSurface(surface);
					delete texture;
				}

				if (surface->format->format == SDL_PIXELFORMAT_RGB24
					|| surface->format->format == SDL_PIXELFORMAT_RGB332
					|| surface->format->format == SDL_PIXELFORMAT_RGB444
					|| surface->format->format == SDL_PIXELFORMAT_RGB555
					|| surface->format->format == SDL_PIXELFORMAT_RGB565
					|| surface->format->format == SDL_PIXELFORMAT_RGB888)
				{
					texture->m_Format = LampImageFormat::RGB;
				}
				else if (surface->format->format == SDL_PIXELFORMAT_RGBA4444
					|| surface->format->format == SDL_PIXELFORMAT_RGBA5551
					|| surface->format->format == SDL_PIXELFORMAT_RGBA8888)
				{
					texture->m_Format = LampImageFormat::RGBA;
				}
				else {
					printf("The fuck, pixel format is not recognized?\n");
					SDL_FreeSurface(surface);
					delete texture;
					return NULL;
				}

				//Temp way of doing it :p
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, texture->getGLId());
				glTexImage2D(GL_TEXTURE_2D, 0, texture->m_Format, texture->m_width, texture->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				SDL_FreeSurface(surface);
				return texture;
			}
		}

	};

}