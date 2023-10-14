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
enum class ShaderUsed
{
	Shapes,
	Sprites
};
class Shader
{
public:
	Shader();
	~Shader();
	static ShaderProgramSource ParseShader(const string& filepath,ShaderUsed shaderUsed);
	static int CreateShader(const std::string& vertexShader, const std::string& fragmentshader);
	static GLuint CompileShader(const GLuint type, const std::string& source);
	static void SetVec2(const std::string& name, float x, float y,unsigned int ID)  { glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); }
	static void SetVec3(const std::string& name, float x, float y, float z,unsigned int ID)  { glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); }
	static void SetVec4(const std::string& name, float x, float y, float z, float w,unsigned int ID)  { glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); }
private:

};