#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GL/glew.h"

using namespace std;

struct ShaderProgramSource
{
	string vertexSource;
	string fragmentSource;
};

class Shader
{
public:
	Shader();
	~Shader();
	static ShaderProgramSource ParseShader(const string& filepath);
	static int CreateShader(const std::string& vertexShader, const std::string& fragmentshader);
	static GLuint CompileShader(const GLuint type, const std::string& source);
private:

};