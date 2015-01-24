#include "OpenGLHelper.h"
#include "GeniusCaeli.h"

GLfloat vertices[] = {
	//X,   Y,     U,    V
	-1.0f, 1.0f,  0.0f, 1.0f,
	1.0f, 1.0f,  1.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	
	1.0f, 1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f
};

int main(int argc, char** argv){
	
	GLFWwindow* window = initializeWindow(800, 600, "Magic Portal!");
	if(window == nullptr) return -1;
	
	//Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	//Compile shaders
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	buildShaderProgram(vertexShader, fragmentShader, shaderProgram, "vertexShader_base.glsl", "fragmentShader_base.glsl");
	glUseProgram(shaderProgram);
	
	//Vertex data
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);
	
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));

	//MAKE A NEW PERLIN NOISE GENERATOR...
	//and somehow texture be happen?
	
	//Render loop
	do{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window));
	
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	
	//Clean up objects
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	
	
	return 0;
}