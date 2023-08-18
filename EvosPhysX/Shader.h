#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <glad/gl.h>

class Shader
{
public:
	enum Type {
		Default,
		Ortho,
		PrimitiveOrtho,
		Instanced,
		WaveInstanced,
		End
	};
private:
	static std::vector<Shader*> _shaders;
	bool ortho = false;
	bool timeBased = false;
	Type type;
	GLuint programId;

	static void getShaderContent(const char* path, std::string& content);
public:
	static void initialize();
	static void destroy();
	static Shader* load(const char* pathVertex, const char* pathFragment, Type type);
	static Shader* get(Type type = Type::Default);
	static std::vector<Shader*>& getAll() { return _shaders; }

	Shader(Type _type, GLuint _programId): type(_type), programId(_programId) {}
	GLint getUniformLocation(const char* name) {
		return glGetUniformLocation(programId, name);
	}

	void useProgram() {
		glUseProgram(programId);
	}
	bool isOrthoProjection() { return ortho; }
	bool isTimeBased() { return timeBased; }

	void setProjectionIsOrtho(bool isOrtho) { ortho = isOrtho; }
	void setIsTimeBased(bool _isTimeBased) { timeBased = _isTimeBased; }

	Type getType() { return type; }
};
