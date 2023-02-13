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
//#include "Texture.h"

void Window::Init(int width, int height, const char* title)
{
	this->width = width;
	this->height = height;

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
	glfwSetKeyCallback(m_Window, Input::KeyCallback);
	glfwSetCursorPosCallback(m_Window, Input::CursorPosCallback);

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}



	glEnable(GL_DEPTH_TEST);
}

void Window::Update()
{

	std::vector<Vertex> vertices = {
			// ================================================================================================================
			// Front
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Left Top = 0
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // Left Bottom = 1
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // Right Bottom = 2
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // Right Top = 3
			// Back
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Right Top = 4
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // Left Top = 5
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // Right Bottom = 6
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // Left Bottom = 7
			// ================================================================================================================

			// For text coords in top face
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // 4
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // 5
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // 0
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f)}, // 3

			// For text coords in right face
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // 3
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // 2

			// For text coords in left face
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // 0
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // 1

			// For text coords in bottom face
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // 6
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // 7
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // 1
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.5f)}, // 2
	};

	std::vector<unsigned int> indices = {
            // Front face
            0, 1, 3, 3, 1, 2,
            // Top Face
            8, 10, 11, 9, 8, 11,
            // Right face
            12, 13, 7, 5, 12, 7,
            // Left face
            14, 15, 6, 4, 14, 6,
            // Bottom face
            16, 18, 19, 17, 16, 19,
            // Back face
            4, 6, 7, 5, 4, 7,
	};

	Shader shader("rsc/shaders/vDefault.glsl", "rsc/shaders/fDefault.glsl");
	Mesh mesh(vertices, indices, "rsc/textures/grass.png");
	Transform trans(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	Camera cam(glm::vec3(0.0f, 2.0f, 5.0f));



	while (!ShouldClose())
	{
		if (!m_Window) return;

		// Delta time
		double newTime = glfwGetTime();
		deltaTime = newTime - currentTime;
		currentTime = newTime;
		framecount++;

		// Input
		if (Input::IsKeyPressed(GLFW_KEY_W))
			cam.ProcessKeyboard(Input::Direction::FORWARD, deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_S))
			cam.ProcessKeyboard(Input::Direction::BACKWARD, deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_A))
			cam.ProcessKeyboard(Input::Direction::LEFT, deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_D))
			cam.ProcessKeyboard(Input::Direction::RIGHT, deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_SPACE))
			cam.ProcessKeyboard(Input::Direction::Up, deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
			cam.ProcessKeyboard(Input::Direction::Down, deltaTime);

		cam.ProcessMouseMovement((float) Input::GetOffsetX(), (float) Input::GetOffsetY(), true);

		// Render logic
		glClearColor(0.25, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float aspectRatio = (float) width / (float) height;

		glm::mat4 projMatrix = cam.GetProjectionMatrix(45.0f, aspectRatio, 0.1f, 100.0f);

		shader.Use();
		shader.SetMat4f("projection", projMatrix);
		shader.SetMat4f("view", cam.GetViewMatrix());
		shader.SetMat4f("model", trans.GetModelViewMatrix());
		mesh.Render();

		trans.SetRotation(trans.GetRotation().x, trans.GetRotation().y, trans.GetRotation().z);



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
}

bool Window::ShouldClose()
{
	return m_Window ? glfwWindowShouldClose(m_Window) : true;
}

void Window::Terminate()
{
	glfwTerminate();
}
