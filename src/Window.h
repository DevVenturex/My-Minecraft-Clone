/*
 * Window.h
 *
 *  Created on: 2 Feb 2023
 *      Author: basti
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Block.h"

class Window {
private:
	GLFWwindow* m_Window;
	double currentTime = glfwGetTime();
	double deltaTime = 0.0;
	int framecount = 0;
	double fps = 0.0;

public:
	int width, height;
	Window() : m_Window(nullptr) {}

	void Init(int width, int height, const char* title);
	void Update();
	bool ShouldClose();
	void Terminate();

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		win->width = width;
		win->height = height;
		glViewport(0, 0, width, height);
	}
};

#endif /* WINDOW_H_ */
