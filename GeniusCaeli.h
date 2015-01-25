#ifndef GENIUSCAELI_H
#define GENIUSCAELI_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp> //Ultimately, I want to be independent of this, yeah? But for my immediate purposes, may as well not re-invent the wheel.
#include <glm/gtc/constants.hpp>

#include <functional>
#include <random>

#define GRIDSIZE 256

class GeniusCaeli{
private:
	//I'll need to store pregenerated grids. But to make things a tad complicated, I want arbitrary dimensions.
	//So I'll need a way to store such things. 
	//I'll also need a function for pregeneration. I guess I can call it from my noise generating function if I can't find an existing, suitable grid.
	//Or, as another option, I can call it ahead of time if I know I'll need a certain texture later.  
	//Later, I'll want maybe the option to store multiple grids of the same size and specify a particular one. 
	
	glm::vec2 grid2D[256][256];
	
	void genGrid2D(uint seed);
	
public:
	
	GeniusCaeli(){
		genGrid2D(1);
	}
	
	//Let's start with a single, 2D function to keep it simple. I can expand from there if I want to.
	
	//Takes: The X and Y coordinates of a point on the texture's surface.
	//Returns: A continuous, psuedorandom value from 0 to 1.
	float Perlin2D(float x, float y);
};

#endif