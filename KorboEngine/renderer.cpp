#include "renderer.h"
#include "vertex.h"

Renderer::Renderer(Window* window, GLbitfield mask)
{
	this->GLFWW = window;
	this->mask = mask;
	cout << "Renderer Created" << endl;
}

Renderer::Renderer(Window* window)
{
	this->GLFWW = window;
	this->mask = GL_COLOR_BUFFER_BIT;
	cout << "Renderer Created" << endl;
}

Renderer::~Renderer()
{
	cout << "Renderer Deleted" << endl;
}

void Renderer::RenderScreen()
{
	/* Render here */
	glClear(mask);
	Vertex vertex[3] = { Vertex::Vertex() , Vertex::Vertex() , Vertex::Vertex() };

	vertex[0].pos = { -0.5f,0.5f };
	vertex[1].pos = { 0.0f,0.5f };
	vertex[2].pos = { 0.5f,-0.5f };

	unsigned int buffer;
//TODO:AGREGAR FUNCION DE GLBUFFER
	/* Swap front and back buffers */
	glfwSwapBuffers(GLFWW->getWindow());

	/* Poll for and process events */
	glfwPollEvents();
}

void Renderer::SetWindow(Window* window)
{
	GLFWW = window;
}
void Renderer::Setbitfield(GLbitfield mask)
{
	this->mask = mask;
}

GLbitfield Renderer::Getbitfield()
{
	return this->mask;
}