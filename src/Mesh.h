/*
 * Mesh.h
 *
 *  Created on: 2 Feb 2023
 *      Author: basti
 */

#ifndef MESH_H_
#define MESH_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoord;
};

class Mesh {
public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	~Mesh();

	void Render();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
};

#endif /* MESH_H_ */
