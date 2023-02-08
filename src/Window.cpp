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
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Input.h"
#include "Texture.h"

void Window::Init(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;

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

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, frameBufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}



	glEnable(GL_DEPTH_TEST);
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
			// Front
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Left Bottom = 0
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Right Bottom = 1
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Right Top = 2
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Left Top = 3
			// Back
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Left Bottom = 4
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Right Bottom = 5
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Right Top = 6
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Left Top = 7
			// Left
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Left Bottom = 8
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Right Bottom = 9
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Right Top = 10
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Left Top = 11
			// Right
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Left Bottom = 12
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Right Bottom = 13
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Right Top = 14
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Right Top = 15
			// Top
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Left Bottom = 16
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Right Bottom = 17
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Right Top = 18
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Left Top = 19
			// Bottom
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Left Bottom = 20
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Right Bottom = 21
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Right Top = 22
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Left Bottom = 23
	};

	std::vector<unsigned int> indices = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			4, 5, 1, 1, 0, 4,
			6, 7, 3, 3, 2, 6,
			5, 6, 2, 2, 1, 5,
			7, 4, 0, 0, 3, 7,

			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
	};

	Shader shader("rsc/shaders/vDefault.glsl", "rsc/shaders/fDefault.glsl");
	Mesh mesh(vertices, indices);
	Texture tex("rsc/textures/grass.png");
	Transform trans(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(45.0f, 45.0f, 0.0f), glm::vec3(1.0f));
	Camera cam;

	float aspectRatio = (float) width / (float) height;

	shader.Use();
	shader.SetMat4f("projection", cam.GetProjectionMatrix(45.0f, aspectRatio, 0.1f, 100.0f));
	shader.SetMat4f("view", cam.GetViewMatrix());
	shader.SetMat4f("model", trans.GetModelViewMatrix());
	tex.Use();
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
