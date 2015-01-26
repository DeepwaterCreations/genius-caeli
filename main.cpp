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
	GeniusCaeli geniusCaeli;
	
	//I'm going to populate an array and, somehow, hopefully, bring it into an OpenGL texture. I *think* that's a thing I can do.
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	std::vector<float> perlinTexture;
	GLint textureWidth = 256;
	GLint textureHeight = 256;
	for(int i = 0; i < textureHeight; ++i){
		for(int j = 0; j < textureWidth; ++j){
			perlinTexture.push_back(0.0f); //RED
			perlinTexture.push_back(0.0f); //GREEN
			perlinTexture.push_back(geniusCaeli.perlin2D(i, j)); //BLUE
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, perlinTexture.data());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	//Render loop
	while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window)){
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	};
	
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