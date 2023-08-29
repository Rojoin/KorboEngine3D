#include "shader.h"

Shader::Shader()
{
	cout << "Shader Created" << endl;
}

Shader::~Shader()
{
	cout << "Shader Deleted" << endl;
}

GLuint Shader::CompileShader(const GLuint type, const std::string& source)
{

	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{

		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)alloca(lenght * sizeof(char)); // esto lo hace con alloca para asignarlo en el stack dinamicamente

		glGetShaderInfoLog(id, lenght, &lenght, message);

		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << endl;
		cout << message << endl;

		glDeleteShader(id);
		return 0;
	}

	return id;

}



int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentshader)
{
	GLuint program = glCreateProgram(); // unsigned int of GL
	GLuint vertex_S = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fragment_S = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

	//Link shaders to program
	glAttachShader(program, vertex_S);
	glAttachShader(program, fragment_S);
	glLinkProgram(program);


	glValidateProgram(program);

	//Deleted because they are already linked to the program
	glDeleteShader(vertex_S);
	glDeleteShader(fragment_S);

	return program;
}

ShaderProgramSource Shader::ParseShader(const string& filepath)
{
	ifstream inputStream(filepath);
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	string line;
	stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(inputStream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str() , ss[1].str() };
}