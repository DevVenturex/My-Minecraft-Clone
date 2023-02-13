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
	double lastX = 0.0, lastY = 0.0;
	double xoffset = 0.0, yoffset = 0.0;
	bool firstMouse = true;

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

    void CursorPosCallback(GLFWwindow* window, double xposIn, double yposIn)
    {
    	float xpos = static_cast<float>(xposIn);
    	float ypos = static_cast<float>(yposIn);
    	if (firstMouse)
    	{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

    	xoffset = xpos - lastX;
    	yoffset = lastY - ypos;
    	lastX = xpos;
    	lastY = ypos;
    }

    bool IsKeyPressed(int key)
    {
        return keysPressed[key];
    }

    bool IsMouseButtonPressed(int button)
    {
        return mouseButtonPressed[button];
    }

    double GetOffsetX()
    {
        return xoffset;
    }

    double GetOffsetY()
    {
        return yoffset;
    }

    double GetLastX()
    {
    	return lastX;
    }

    double GetLastY()
    {
    	return lastY;
    }
}

#endif /* INPUT_H_ */
