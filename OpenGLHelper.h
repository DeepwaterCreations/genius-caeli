#ifndef OPENGLHELPER
#define OPENGLHELPER

#include <fstream>
#include <iostream>
#include <algorithm>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <SOIL/SOIL.h>

//COMPILE WITH -lGL -lGLEW -lglfw -lSOIL !

//Sets up the display window.
//Returns a pointer to the window.
GLFWwindow* initializeWindow(int width, int height, const char* title);

//Loads an image from the filesystem into a texture, through SOIL.
//Returns the id of a texture loaded from the image at /filename/.
GLuint loadTexture(const char* filename, GLint textureWrapS = GL_CLAMP_TO_EDGE, GLint textureWrapT = GL_CLAMP_TO_EDGE, GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR);

//Loads shaders, compiles them, and links them into a program. vertexSrc and fragmentSrc are filenames of glsl files.
//Returns false if the file was not read or the shader failed to compile.
//Also prints shader compilation errors to stderr. 
bool buildShaderProgram(GLuint& vertexShader, GLuint& fragmentShader, GLuint& shaderProgram, const char* vertexSrc, const char* fragmentSrc);


#endif