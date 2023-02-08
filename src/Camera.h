/*
 * Camera.h
 *
 *  Created on: 3 Feb 2023
 *      Author: basti
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Input.h"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::mat4 viewMatrix;
    float pitch, yaw;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        : position(position), front(front), up(up), pitch(0.0f), yaw(-90.0f)
    {
        UpdateViewMatrix();
    }

    void UpdateViewMatrix()
    {
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front);

        viewMatrix = glm::lookAt(position, position + front, up);
    }

    glm::mat4 GetViewMatrix()
    {
        return viewMatrix;
    }

    glm::mat4 GetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
};

#endif /* CAMERA_H_ */
