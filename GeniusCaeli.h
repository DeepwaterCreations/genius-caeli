#ifndef GENIUSCAELI_H
#define GENIUSCAELI_H

class GeniusCaeli{
private:
	//I'll need to store pregenerated grids. But to make things a tad complicated, I want arbitrary dimensions.
	//So I'll need a way to store such things. 
	//I'll also need a function for pregeneration. I guess I can call it from my noise generating function if I can't find an existing, suitable grid.
	//Or, as another option, I can call it ahead of time if I know I'll need a certain texture later.  
	//Later, I'll want maybe the option to store multiple grids of the same size and specify a particular one. 
	
public:
	//Let's start with a single, 2D function to keep it simple. I can expand from there if I want to.
	
	//Takes: The X and Y coordinates of a point on the texture's surface.
	//Returns: A continuous, psuedorandom value from 0 to 1.
	float Perlin2D(float x, float y);
};

#endif