#include "GeniusCaeli.h"

//Seeded, so of course the same seed should always return the same grid. 
void GeniusCaeli::genGrid2D(uint seed){
	std::uniform_real_distribution<float> distribution(0.0f, 2*glm::pi<float>()); //2pi - also known as Tau. 
	auto random = std::bind(distribution, std::default_random_engine(seed));
	
	for(int i = 0; i < GRIDSIZE; i++){
		for(int j = 0; j < GRIDSIZE; j++){
			//Pick a random number of radians between 0 and tau.  
			float angle = random();
			grid2D[i][j] = glm::vec2(cos(angle), sin(angle));
		}
	}
};

float GeniusCaeli::perlin2D(int x, int y){
	//I'm basing this on the algorithm described at
	//webstaff.itn.liu.se/~stegu/TNM022-2005/perlinnoiselinks/perlin-noise-math-faq.html
	
	//So we've got a whole grid of psuedorandom unit vectors.  
	//Our point x, y lies somewhere within this grid, probably not on an actual intersection. 
	//Imagine it as all happening within a single grid cell, surrounded by 4 vectors. Each vector
	//will have an influence on the value at x,y depending on how directly it points toward x,y. 
	//(We use the dot product to determine this.)
	//To get the value, we average the dot products(?) and maybe we want it to be a weighted average, too.
	
	//This seems easily extensible to arbitrary numbers of dimensions. So that's nice.
	
	//I'm not really sure how best to generate the vectors, though. Pick one value and then
	//use the Pythagorean theorem to get the other? Is that reasonable? Seems like there might
	//be a faster approach. Also, that's not so extensible if I do it that way.
	
	//Sounds like having a pre-generated grid and letting the values eventually repeat is a 
	//standard, Ken Perlin-approved approach to make this faster.
	
	//I'm also not so sure this isn't a task for the shader. But that does me no
	//good if I'm trying to be language-agnostic. 
	
	return (grid2D[x%255][y%255]).x;
};