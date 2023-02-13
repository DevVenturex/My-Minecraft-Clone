/*
 * Mesh.cpp
 *
 *  Created on: 2 Feb 2023
 *      Author: basti
 */

#include "Mesh.h"

#include <glad/glad.h>

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Render()
{
	if (useTexture)
		texture.Use();

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

