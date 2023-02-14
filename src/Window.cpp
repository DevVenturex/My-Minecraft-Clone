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
#include "Camera.h"
#include "Input.h"
#include "Block.h"

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
	Shader shader("rsc/shaders/vDefault.glsl", "rsc/shaders/fDefault.glsl");
	Camera cam(glm::vec3(0.0f, 2.0f, 5.0f));
	std::vector<Block> blocks = {};

	for (int x = 0; x < 5; x++)
	{
		for (int z = 0; z < 5; z++)
		{
			Block b(x, 0, z, BlockType::GRASS_BLOCK);
			blocks.push_back(b);
		}
	}

	bool cursor = false;
	bool wireframe = false;

	while (!ShouldClose())
	{
		if (!m_Window) return;

		// Delta time
		double newTime = glfwGetTime();
		deltaTime = newTime - currentTime;
		currentTime = newTime;
		framecount++;

		if (Input::IsKeyJustPressed(GLFW_KEY_ESCAPE))
		{
			if (cursor)
			{
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				cursor = false;
			}
			else
			{
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				cursor = true;
			}
		}

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

		for (Block b : blocks)
		{
			shader.SetMat4f("model", b.GetTransform().GetModelViewMatrix());
			b.Update(deltaTime);
			b.Render();
		}

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
