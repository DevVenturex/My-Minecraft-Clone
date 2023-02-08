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


	Transform() : position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)) { UpdateModelViewMatrix(); }
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : position(position), rotation(rotation), scale(scale) { UpdateModelViewMatrix(); }

	glm::mat4 GetModelViewMatrix()
	{
		return modelView;
	}

	void SetRotation(float x, float y, float z)
	{
		rotation = glm::vec3(x, y, z);
		UpdateModelViewMatrix();
	}

	void SetPosition(float x, float y, float z)
	{
		position = glm::vec3(x, y, z);
		UpdateModelViewMatrix();
	}

	void SetScale(float x, float y, float z)
	{
		scale = glm::vec3(x, y, z);
		UpdateModelViewMatrix();
	}


	glm::vec3 GetRotation() { return rotation; }
	glm::vec3 GetPosition() { return position; }
	glm::vec3 GetScale() { return scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 modelView;

	void UpdateModelViewMatrix()
	{
		modelView = glm::mat4(1.0f);
		modelView = glm::translate(modelView, position);
		modelView = glm::rotate(modelView, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		modelView = glm::rotate(modelView, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		modelView = glm::rotate(modelView, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelView = glm::scale(modelView, scale);
	}
};


#endif /* TRANSFORM_H_ */
