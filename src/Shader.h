/*
 * Shader.h
 *
 *  Created on: 2 Feb 2023
 *      Author: basti
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();
	void Detach();
	void SetBool(const std::string &name, bool value);
	void SetInt(const std::string &name, int value);
	void SetFloat(const std::string &name, float value);
	void SetMat4f(const std::string &name, const glm::mat4 &value);
private:
	unsigned int m_Program;
};


#endif /* SHADER_H_ */
