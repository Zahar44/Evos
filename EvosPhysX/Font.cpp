#include "Font.h"

std::vector<Font*> Font::fonts;
FT_Library Font::library;

void Font::initialize(FT_Face& face)
{
    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        if (face->glyph->bitmap_top > maxYBearing) {
            maxYBearing = face->glyph->bitmap_top;
        }
        if (face->glyph->bitmap_left > maxXBearing) {
            maxXBearing = face->glyph->bitmap_left;
        }

        characters.insert(std::pair<char, Character>(c, character));
    }

    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Font::load(const char* path, Type type)
{
	FT_Face face;
	auto error = FT_New_Face(
		library, path,
		0, &face
	);

	if (error == FT_Err_Unknown_File_Format)
	{
		std::cerr << "Unknown format of font " << path << std::endl;
		return;
	}
	else if (error) {
		std::cerr << "Error during font loading " << path << error << std::endl;
		return;
	}

	fonts[type] = new Font(face, type);
	FT_Done_Face(face);
}

void Font::initializeFreeType()
{
	auto error = FT_Init_FreeType(&library);
	if (error)
	{
		std::cerr << "Error during font library initialization " << error << std::endl;
		assert(false);
	}
}

void Font::destroyFreeType()
{
	FT_Done_FreeType(library);
}

void Font::initialize()
{
	initializeFreeType();

	fonts.resize(Type::End);
	load("font/gomarice_shiratama_dango.ttf", Type::Default);

	destroyFreeType();
}

void Font::destroy()
{
    for (auto& font : fonts) {
        for (auto& ch : font->characters)
            glDeleteTextures(1, &ch.second.textureId);
        delete font;
    }
}
