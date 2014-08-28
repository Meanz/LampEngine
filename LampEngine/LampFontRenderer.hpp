#pragma once

//FreeType Headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

//OpenGL Headers 
#include <windows.h>		//(the GL headers need it)
#include <GL/gl.h>
#include <GL/glu.h>

//Some STL headers
#include <vector>
#include <string>

//Using the STL exception library increases the
//chances that someone else using our code will corretly
//catch any exceptions that we throw.
#include <stdexcept>

namespace LampProject
{
	//Inside of this namespace, give ourselves the ability
	//to write just "vector" instead of "std::vector"
	using std::vector;

	//Ditto for string.
	using std::string;

	//This holds all of the information related to any
	//freetype font that we want to create.  
	struct font_data {
		float h;			///< Holds the height of the font.
		GLuint * textures;	///< Holds the texture id's 
		GLuint list_base;	///< Holds the first display list id

		//The init function will create a font of
		//of the height h from the file fname.
		void init(const char * fname, unsigned int h);

		//Free all the resources assosiated with the font.
		void clean();
	};

	//The flagship function of the library - this thing will print
	//out text at window coordinates x,y, using the font ft_font.
	//The current modelview matrix will also be applied to the text. 
	void print(const font_data &ft_font, float x, float y, const char *fmt, ...);


	class LampFont
	{
	private:
		float m_Height; //Holds the height of the font
		GLuint* m_Textures; //Holds texture ids
		GLuint m_ListBase; //Holds the first display list id

	public:

		LampFont();
		~LampFont();

		bool loadFont(std::string fontPath, unsigned int height);
		void deleteFont();
		void draw(std::string str, float x, float y);

	};
}