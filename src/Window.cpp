/*
 * Window.cpp
 *
 *  Created on: 2 Feb 2023
 *      Author: basti
 */

#include "Window.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Mesh.h"

void Window::Init(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);

	m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if(!m_Window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glfwSetFramebufferSizeCallback(m_Window, frameBufferSizeCallback);
}

void Window::Update()
{
	if (!m_Window) return;

	// Delta time
	double newTime = glfwGetTime();
	deltaTime = newTime - currentTime;
	currentTime = newTime;
	framecount++;

	// Render logic
	glClearColor(0.25, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	std::vector<Vertex> vertices = {
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
		{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},
		{glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)},
		{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)},
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	Shader shader("rsc/shaders/vDefault.glsl", "rsc/shaders/fDefault.glsl");
	Mesh mesh(vertices, indices);

	shader.Use();
	mesh.Render();

	// Update logic
	if (currentTime - fps >= 1.0)
	{
		fps = currentTime;
		std::cout << "FPS: " << framecount << std::endl;
		framecount = 0;
	}

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool Window::ShouldClose()
{
	return m_Window ? glfwWindowShouldClose(m_Window) : true;
}

void Window::Terminate()
{
	glfwTerminate();
}
