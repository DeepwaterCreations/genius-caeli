#version 150 core

in vec2 vTexcoord;

out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor = texture(tex, vTexcoord); 
}
