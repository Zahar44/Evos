#pragma once
#include <vector>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Random.h"

class Font {
public:
	enum Type {
		Default,
		End
	};
	struct Character {
		GLuint		 textureId;  // ID handle of the glyph texture
		glm::ivec2   size;       // Size of glyph
		glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
		FT_Pos		 advance;    // Offset to advance to next glyph
	};
private:
	static std::vector<Font*> fonts;
	static FT_Library library;

	int maxYBearing = 0;
	int maxXBearing = 0;

	std::map<char, Character> characters;
	GLuint vertexArray = 0, vertexBuffer = 0;
	Type type;
	Font(FT_Face& _face, Type _type) : type(_type) {
		initialize(_face);
	};
	void initialize(FT_Face& face);
	static void load(const char* path, Type type);
	static void initializeFreeType();
	static void destroyFreeType();
public:
	static void initialize();
	static void destroy();

	GLuint getVertexArray() {
		return vertexArray;
	};

	GLuint getVertexBuffer() {
		return vertexBuffer;
	};

	Character& getCharacter(char c) {
		return characters[c];
	}

	Type getType() {
		return type;
	}

	int getMaxVerticalBearing() { return maxYBearing; }
	int getMaxHorizontalBearing() { return maxXBearing; }

	static Font* get(Type type = Default) { return fonts[type]; };
};
