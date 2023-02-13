/*
 * Camera.h
 *
 *  Created on: 3 Feb 2023
 *      Author: basti
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.5f;
const float ZOOM        =  45.0f;

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 worldUp;
    glm::vec3 right;
    glm::mat4 viewMatrix;
    float pitch, yaw;

    float mouseSensitivity;
    float speed;

    Camera() : position(glm::vec3(0.0f, 0.0f, 0.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), pitch(PITCH), yaw(YAW), mouseSensitivity(SENSITIVITY), speed(SPEED)
    {
    	worldUp = up;
        UpdateViewMatrix();
    }

    Camera(glm::vec3 position) : position(position), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), pitch(PITCH), yaw(YAW), mouseSensitivity(SENSITIVITY), speed(SPEED)
    {
    	worldUp = up;
    	UpdateViewMatrix();
    }

    void ProcessKeyboard(Input::Direction direction, float deltaTime)
    {
    	float velocity = speed * deltaTime;
    	if (direction == Input::Direction::FORWARD)
    		position += front * velocity;
    	if (direction == Input::Direction::BACKWARD)
    		position -= front * velocity;
    	if (direction == Input::Direction::LEFT)
    		position -= right * velocity;
    	if (direction == Input::Direction::RIGHT)
    		position += right * velocity;

    	UpdateViewMatrix();
    }

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
    	xoffset *= mouseSensitivity;
    	yoffset *= mouseSensitivity;

    	yaw += xoffset;
    	pitch += yoffset;

    	if (constrainPitch)
    	{
    		if (pitch > 89.0f)
    			pitch = 89.0f;
    		if (pitch < -89.0f)
    			pitch = -89.0f;
    	}

    	UpdateViewMatrix();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 GetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

private:
    void UpdateViewMatrix()
    {
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

#endif /* CAMERA_H_ */
