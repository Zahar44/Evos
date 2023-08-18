#include "Shader.h"

std::vector<Shader*> Shader::_shaders;

void Shader::getShaderContent(const char* path, std::string& content)
{
	std::ifstream infile(path);
	if (!infile) {
		std::cerr << "Can't open " << path << std::endl;
		assert(false);
	}

	std::string line;

	while (std::getline(infile, line)) {
		content += line + "\n";
	}
	infile.close();
}

void Shader::initialize()
{
	_shaders.resize(Shader::Type::End);

	_shaders[Type::Default]			= load("default.vert", "default.frag", Type::Default);
	_shaders[Type::Ortho]			= load("ortho.vert", "ortho.frag", Type::Ortho);
	_shaders[Type::PrimitiveOrtho]	= load("primitive-ortho.vert", "primitive-ortho.frag", Type::PrimitiveOrtho);
	_shaders[Type::Instanced]		= load("default-instanced.vert", "default.frag", Type::Instanced);
	_shaders[Type::WaveInstanced]	= load("wave-instanced.vert", "default.frag", Type::WaveInstanced);

	_shaders[Type::Ortho]->setProjectionIsOrtho(true);
	_shaders[Type::PrimitiveOrtho]->setProjectionIsOrtho(true);
	_shaders[Type::WaveInstanced]->setIsTimeBased(true);
}

void Shader::destroy()
{
	for (auto& shader : _shaders) {
		delete shader;
	}

	_shaders.clear();
}

Shader* Shader::load(const char* pathVertex, const char* pathFragment, Type type)
{
	std::string vertex, fragment;
	getShaderContent(pathVertex, vertex);
	getShaderContent(pathFragment, fragment);
	const char* vertexp = vertex.c_str();
	const char* fragmentp = fragment.c_str();

	auto vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexp, NULL);
	glCompileShader(vertexShaderId);

	int success;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		assert(false);
	}

	auto fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentp, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		assert(false);
	}

	auto shaderId = glCreateProgram();
	glAttachShader(shaderId, vertexShaderId);
	glAttachShader(shaderId, fragmentShaderId);
	glLinkProgram(shaderId);

	glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK\n" << infoLog << std::endl;
		assert(false);
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return new Shader(type, shaderId);
}

Shader* Shader::get(Type type)
{
	for (auto& s : _shaders) {
		if (s->getType() == type) return s;
	}
	assert(false);
}
