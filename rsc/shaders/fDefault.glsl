#version 450

in vec4 fColor;
in vec2 fTexCoord;

uniform sampler2D tex;

out vec4 color;

void main(){
	color = texture(tex, fTexCoord) * fColor;
}