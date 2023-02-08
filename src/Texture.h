/*
 * Texture.h
 *
 *  Created on: 5 Feb 2023
 *      Author: basti
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

class Texture
{
private:
	unsigned int id;
	int width, height, nrChannels;

public:
	Texture() : id(0), width(0), height(0), nrChannels(0) {}

	void LoadTexture(const char* path)
	{
		unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
		if (data)
		{
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
	}
};


#endif /* TEXTURE_H_ */
