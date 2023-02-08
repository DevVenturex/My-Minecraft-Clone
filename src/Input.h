/*
 * Input.h
 *
 *  Created on: 5 Feb 2023
 *      Author: basti
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <GLFW/glfw3.h>
#include <vector>

namespace Input
{
	enum Direction
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	bool keysPressed[GLFW_KEY_LAST];
	bool mouseButtonPressed[GLFW_MOUSE_BUTTON_LAST];
	double mouseX, mouseY;

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keysPressed[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keysPressed[key] = false;
		}
	}

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            mouseButtonPressed[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mouseButtonPressed[button] = false;
        }
    }

    void CursorPosCallback(GLFWwindow* window, double x, double y)
    {
        mouseX = x;
        mouseY = y;
    }

    bool IsKeyPressed(int key)
    {
        return keysPressed[key];
    }

    bool IsMouseButtonPressed(int button)
    {
        return mouseButtonPressed[button];
    }

    double GetMouseX()
    {
        return mouseX;
    }

    double GetMouseY()
    {
        return mouseY;
    }
}

#endif /* INPUT_H_ */
