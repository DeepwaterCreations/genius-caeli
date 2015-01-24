#version 150 core

in vec2 vTexcoord;

out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor = vec4(0.0, 0.0, 1.0, 1.0); //texture(tex, vTexcoord); 
}
