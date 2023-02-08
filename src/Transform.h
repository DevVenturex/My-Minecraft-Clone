/*
 * Transform.h
 *
 *  Created on: 3 Feb 2023
 *      Author: basti
 */

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	Transform() : m_Position(glm::vec3(0.0f)), m_Rotation(glm::vec3(0.0f)), m_Scale(glm::vec3(1.0f)) {}
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

	glm::mat4 GetModelViewMatrix()
	{
		modelView = glm::mat4(1.0f);
		modelView = glm::translate(modelView, m_Position);
		modelView = glm::rotate(modelView, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		modelView = glm::rotate(modelView, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelView = glm::rotate(modelView, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelView = glm::scale(modelView, m_Scale);
		return modelView;
	}

private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 modelView;
};


#endif /* TRANSFORM_H_ */
