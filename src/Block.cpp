/*
 * Block.cpp
 *
 *  Created on: 14 Feb 2023
 *      Author: basti
 */

#include "Block.h"

const char* TEXTURE_PATH = "rsc/textures/grass.png";

Block::Block(int x, int y, int z, BlockType type)
{
	this->mesh = new Mesh(vertices, indices);
	this->transform = new Transform(glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)), glm::vec3(0.0f), glm::vec3(1.0f));
	this->texture = new Texture(TEXTURE_PATH);
}

void Block::Update(double deltaTime)
{

}

void Block::Render()
{
	texture->Use();
	mesh->Render();
}
