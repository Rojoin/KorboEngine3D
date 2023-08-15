#include "renderer.h"

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