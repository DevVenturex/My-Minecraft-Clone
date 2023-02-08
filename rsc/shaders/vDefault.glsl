#version 330 core

layout (location=0) in vec3 aPosition;
layout (location=1) in vec4 aColor;

out vec4 fColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
	fColor = aColor;
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}