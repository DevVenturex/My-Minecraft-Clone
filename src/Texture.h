/*
 * Texture.h
 *
 *  Created on: 5 Feb 2023
 *      Author: basti
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <iostream>

class Texture
{
private:
	unsigned int id;
	int width, height, nrChannels;

public:
	Texture(const char* path);
	void Use();
};


#endif /* TEXTURE_H_ */
