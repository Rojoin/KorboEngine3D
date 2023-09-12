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
	static void SetVec3(const std::string& name, float x, float y, float z,unsigned int ID)  { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z,1.0f); }
	static void SetVec4(const std::string& name, float x, float y, float z, float w,unsigned int ID)  { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
private:

};