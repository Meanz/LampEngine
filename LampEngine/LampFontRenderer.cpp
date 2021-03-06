#include "stdafx.h"
#include "LampFontRenderer.hpp"

namespace LampProject {

	///This function gets the first power of 2 >= the
	///int that we pass it.
	inline int next_p2(int a)
	{
		int rval = 1;
		while (rval < a) rval <<= 1;
		return rval;
	}

	///Create a display list coresponding to the give character.
	void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint * tex_base) {

		//The first thing we do is get FreeType to render our character
		//into a bitmap.  This actually requires a couple of FreeType commands:

		//Load the Glyph for our character.
		if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
			throw std::runtime_error("FT_Load_Glyph failed");

		//Move the face's glyph into a Glyph object.
		FT_Glyph glyph;
		if (FT_Get_Glyph(face->glyph, &glyph))
			throw std::runtime_error("FT_Get_Glyph failed");

		//Convert the glyph to a bitmap.
		FT_Glyph_To_Bitmap(&glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL, 0, 1);
		FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

		//This reference will make accessing the bitmap easier
		FT_Bitmap& bitmap = bitmap_glyph->bitmap;

		//Use our helper function to get the widths of
		//the bitmap data that we will need in order to create
		//our texture.
		int width = next_p2(bitmap.width);
		int height = next_p2(bitmap.rows);

		//Allocate memory for the texture data.
		GLubyte* expanded_data = new GLubyte[2 * width * height];

		//Here we fill in the data for the expanded bitmap.
		//Notice that we are using two channel bitmap (one for
		//luminocity and one for alpha), but we assign
		//both luminocity and alpha to the value that we
		//find in the FreeType bitmap. 
		//We use the ?: operator so that value which we use
		//will be 0 if we are in the padding zone, and whatever
		//is the the Freetype bitmap otherwise.
		for (int j = height - 1; j >= 0; j--) {
			for (int i = 0; i < width; i++){
				expanded_data[2 * (i + j*width)] = expanded_data[2 * (i + j*width) + 1] =
					(i >= bitmap.width || j >= bitmap.rows) ?
					0 : bitmap.buffer[i + bitmap.width*j];
			}
		}


		//Now we just setup some texture paramaters.
		glBindTexture(GL_TEXTURE_2D, tex_base[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//Here we actually create the texture itself, notice
		//that we are using GL_LUMINANCE_ALPHA to indicate that
		//we are using 2 channel data.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
			0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

		//With the texture created, we don't need to expanded data anymore
		delete[] expanded_data;

		//So now we can create the display list
		glNewList(list_base + ch, GL_COMPILE);

		glBindTexture(GL_TEXTURE_2D, tex_base[ch]);

		glPushMatrix();

		//first we need to move over a little so that
		//the character has the right amount of space
		//between it and the one before it.
		glTranslatef(GLfloat(bitmap_glyph->left), 0, 0);

		//Now we move down a little in the case that the
		//bitmap extends past the bottom of the line 
		//(this is only true for characters like 'g' or 'y'.
		glTranslatef(0, GLfloat(bitmap_glyph->top - bitmap.rows), 0);

		//Now we need to account for the fact that many of
		//our textures are filled with empty padding space.
		//We figure what portion of the texture is used by 
		//the actual character and store that information in 
		//the x and y variables, then when we draw the
		//quad, we will only reference the parts of the texture
		//that we contain the character itself.
		float x = (float) bitmap.width / (float) width;
		float y = (float) bitmap.rows / (float) height;

		//Here we draw the texturemaped quads.
		//The bitmap that we got from FreeType was not 
		//oriented quite like we would like it to be,
		//so we need to link the texture to the quad
		//so that the result will be properly aligned.
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(0, GLfloat(bitmap.rows));
		glTexCoord2d(0, y); glVertex2f(0, 0);
		glTexCoord2d(x, y); glVertex2f(GLfloat(bitmap.width), 0);
		glTexCoord2d(x, 0); glVertex2f(GLfloat(bitmap.width), GLfloat(bitmap.rows));
		glEnd();
		glPopMatrix();
		glTranslatef(GLfloat(face->glyph->advance.x >> 6), 0, 0);


		//increment the raster position as if we were a bitmap font.
		//(only needed if you want to calculate text length)
		//glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

		//Finnish the display list
		glEndList();
	}

	void font_data::clean() {
		glDeleteLists(list_base, 128);
		glDeleteTextures(128, textures);
		delete[] textures;
	}

	LampFont::LampFont()
	{

	}

	LampFont::~LampFont()
	{

	}

	bool LampFont::loadFont(std::string fontPath, unsigned int height)
	{
		//Allocate some memory to store the texture ids.
		m_Textures = new GLuint[128];

		this->m_Height = float(height);

		//Create and initilize a freetype font library.
		FT_Library library;
		if (FT_Init_FreeType(&library))
			throw std::runtime_error("FT_Init_FreeType failed");

		//The object in which Freetype holds information on a given
		//font is called a "face".
		FT_Face face;

		//This is where we load in the font information from the file.
		//Of all the places where the code might die, this is the most likely,
		//as FT_New_Face will die if the font file does not exist or is somehow broken.
		if (FT_New_Face(library, fontPath.c_str(), 0, &face))
			throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

		//For some twisted reason, Freetype measures font size
		//in terms of 1/64ths of pixels.  Thus, to make a font
		//h pixels high, we need to request a size of h*64.
		//(h << 6 is just a prettier way of writting h*64)
		FT_Set_Char_Size(face, height << 6, height << 6, 96, 96);

		//Here we ask opengl to allocate resources for
		//all the textures and displays lists which we
		//are about to create.  
		m_ListBase = glGenLists(128);
		glGenTextures(128, m_Textures);

		//This is where we actually create each of the fonts display lists.
		for (unsigned char i = 0; i < 128; i++)
			make_dlist(face, i, m_ListBase, m_Textures);

		//We don't need the face information now that the display
		//lists have been created, so we free the assosiated resources.
		FT_Done_Face(face);

		//Ditto for the library.
		FT_Done_FreeType(library);

		return true;
	}

	void LampFont::deleteFont()
	{

	}

	void LampFont::draw(std::string str, float x, float y)
	{
		GLuint font = m_ListBase;
		float h = m_Height / .63f;						//We make the height about 1.5* that of

		//glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
		//glMatrixMode(GL_MODELVIEW);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//This is where the text display actually happens.
		//For each line of text we reset the modelview matrix
		//so that the line's text will start in the correct position.
		//Notice that we need to reset the matrix, rather than just translating
		//down by h. This is because when each character is
		//draw it modifies the current matrix so that the next character
		//will be drawn immediatly after it.  
		glListBase(font);
		glPushMatrix();
		{
			glTranslatef(x, y + h, 0);
			glScalef(1.0f, -1.0f, 1.0f);
			//  The commented out raster position stuff can be useful if you need to
			//  know the length of the text that you are creating.
			//  If you decide to use it make sure to also uncomment the glBitmap command
			//  in make_dlist().
			//	glRasterPos2f(0,0);
			glCallLists(str.length(), GL_UNSIGNED_BYTE, str.c_str());
			//	float rpos[4];
			//	glGetFloatv(GL_CURRENT_RASTER_POSITION ,rpos);
			//	float len=x-rpos[0];
		}
		glPopMatrix();
		glDisable(GL_BLEND);
		//glPopAttrib();
	}

}
