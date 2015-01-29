#include "GeniusCaeli.h"

//Seeded, so of course the same seed should always return the same grid. 
void GeniusCaeli::genGrid2D(uint seed){
	//Sounds like having a pre-generated grid and letting the values eventually repeat is a 
	//standard, Ken Perlin-approved approach to make this faster.
	
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

float GeniusCaeli::perlin2D(int s, int t){
	//I'm basing this on the algorithm described at
	//webstaff.itn.liu.se/~stegu/TNM022-2005/perlinnoiselinks/perlin-noise-math-faq.html
	
	//So we've got a whole grid of psuedorandom unit vectors.  
	//Our point x, y lies somewhere within this grid, probably not on an actual intersection. 
	//Imagine it as all happening within a single grid cell, surrounded by 4 vectors. Each vector
	//will have an influence on the value at x,y depending on how directly it points toward x,y. 
	//(We use the dot product to determine this.)
	//To get the value, we average the dot products(?) and maybe we want it to be a weighted average, too.
	
	//This seems easily extensible to arbitrary numbers of dimensions. So that's nice.
		
	//I'm also not so sure this isn't a task for the shader. But that does me no
	//good if I'm trying to be language-agnostic. 
	//(Assuming I'm actually doing that. Am I?)
	
	//Scale the points.
	float x = s * hScale;
	float y = t * vScale;
	
	//Find the grid points.
	glm::vec2 upperLeft(std::floor(x), std::floor(y + 1));  
	glm::vec2 upperRight(std::floor(x + 1), std::floor(y + 1));
	glm::vec2 lowerLeft(std::floor(x), std::floor(y));
	glm::vec2 lowerRight(std::floor(x + 1), std::floor(y));
	
	//Get vectors from the corners of the grid to our chosen point.
	glm::vec2 point(x, y); 
	glm::vec2 posUL = point - upperLeft;
	glm::vec2 posUR = point - upperRight;
	glm::vec2 posLL = point - lowerLeft;
	glm::vec2 posLR = point - lowerRight;
		
	//Use the dot product of the gradient vectors with the point position vectors to determine the influence of each gradient point on the result.
	glm::vec2 gradUL = grid2D[int(upperLeft.x)%255][int(upperLeft.y)%255];
	glm::vec2 gradUR = grid2D[int(upperRight.x)%255][int(upperRight.y)%255];
	glm::vec2 gradLL = grid2D[int(lowerLeft.x)%255][int(lowerLeft.y)%255];
	glm::vec2 gradLR = grid2D[int(lowerRight.x)%255][int(lowerRight.y)%255];
	
	float influenceUL = glm::dot(gradUL, posUL);
	float influenceUR = glm::dot(gradUR, posUR);
	float influenceLL = glm::dot(gradLL, posLL);
	float influenceLR = glm::dot(gradLR, posLR);
	
	//I think the main value of the ease curve is that without it, crossing from one grid cell to another
	//is a sudden discontinuity, because the influence of the far grid points is suddenly swapped for a different set.
	//I want the influence of other grid points to approach zero as we get closer to one particular grid point.
	//Actually, is this a thing I could even do linearly? 
	float weightX = easeCurve(posLL.x); //Getting the gridcell space x coordinate of the point, as opposed to texture space. 
	float topXAvg = influenceUL + weightX * (influenceUR - influenceUL); //At weight 1, this comes out to influenceUR. At 0, it's influenceUL.  
	float bottomXAvg = influenceLL + weightX * (influenceLR - influenceLL);
	float weightY = easeCurve(posLL.y);
	float average = topXAvg + weightY * (bottomXAvg - topXAvg);
	
	//float averageTop = easeCurve(influenceUL, influenceUR); //(influenceUL + influenceUR)/2.0f;
	//float averageBottom = easeCurve(influenceLL, influenceLR); //(influenceLL + influenceLR)/2.0f;
	//float average = easeCurve(averageTop, averageBottom); //(averageTop + averageBottom)/2.0f;
		
	return average;
};

float GeniusCaeli::easeCurve(float x){
	return (3.0f * std::pow(x, 2.0f)) - (2.0f * std::pow(x, 3.0f)); 
};