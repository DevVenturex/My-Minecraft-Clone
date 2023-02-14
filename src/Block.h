/*
 * Block.h
 *
 *  Created on: 14 Feb 2023
 *      Author: basti
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <glm/glm.hpp>
#include <vector>

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

enum BlockType
{
	GRASS_BLOCK, STONE, DIRT, PLANKS, WOOD, LEAVE, SAND
};

class Block {
public:


	Block(int x, int y, int z, BlockType type);

	void Update(double deltaTime);
	void Render();

private:
	bool hasGravity = false;
	Mesh* mesh;
	Transform* transform;

	std::vector<Vertex> vertices = {
			// ================================================================================================================
			// Front
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Left Top = 0
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // Left Bottom = 1
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // Right Bottom = 2
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // Right Top = 3
			// Back
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Right Top = 4
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // Left Top = 5
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // Right Bottom = 6
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // Left Bottom = 7
			// ================================================================================================================

			// For text coords in top face
			{glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // 4
			{glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // 5
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // 0
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f)}, // 3

			// For text coords in right face
			{glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // 3
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.5f)}, // 2

			// For text coords in left face
			{glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // 0
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // 1

			// For text coords in bottom face
			{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f)}, // 6
			{glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // 7
			{glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.5f)}, // 1
			{glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.5f)}, // 2
	};

	std::vector<unsigned int> indices = {
            // Front face
            0, 1, 3, 3, 1, 2,
            // Top Face
            8, 10, 11, 9, 8, 11,
            // Right face
            12, 13, 7, 5, 12, 7,
            // Left face
            14, 15, 6, 4, 14, 6,
            // Bottom face
            16, 18, 19, 17, 16, 19,
            // Back face
            4, 6, 7, 5, 4, 7,
	};
};

#endif /* BLOCK_H_ */
