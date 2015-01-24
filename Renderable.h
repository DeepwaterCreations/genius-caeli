#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable{
private:

public:
	
	Renderable(){}
	
	//Call this to render the object.
	void render(GLFWwindow* window) = 0;

};

#endif