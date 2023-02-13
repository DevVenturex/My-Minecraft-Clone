#version 450

layout (location=0) in vec3 aPosition;
layout (location=1) in vec4 aColor;
layout (location=2) in vec2 aTexCoord;

out vec4 fColor;
out vec2 fTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){
	fColor = aColor;
	fTexCoord = aTexCoord;
	gl_Position = projection * view * model * vec4(aPosition, 1.0);
}