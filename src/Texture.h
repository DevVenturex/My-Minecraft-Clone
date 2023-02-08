/*
 * Texture.h
 *
 *  Created on: 5 Feb 2023
 *      Author: basti
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

class Texture
{
private:
	unsigned int id;
	int width, height, nrChannels;

public:
	Texture(const char* path)
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	    if (data)
	    {
	    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	    	glGenerateMipmap(GL_TEXTURE_2D);
	    }
	    else
	    {
	        std::cout << "Failed to load texture" << std::endl;
	    }
	    stbi_image_free(data);
	}

	void Use()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
};


#endif /* TEXTURE_H_ */
