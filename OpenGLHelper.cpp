#include "OpenGLHelper.h"

GLFWwindow* initializeWindow(int width, int height, const char* title){
	GLFWwindow* window;
	
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return nullptr;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	
	// Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return nullptr;
	}
	
	return window;
}

GLuint loadTexture(const GLchar* path, GLint textureWrapS, GLint textureWrapT, GLint minFilter, GLint magFilter){
	GLuint texture;
	glGenTextures(1, &texture);
	
	int width, height;
	unsigned char* image;
	
	glBindTexture(GL_TEXTURE_2D, texture);
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	
	return texture;
}

bool loadShader(GLuint& shader, const char* filename){
	std::string shader_str;
	std::ifstream shader_file;
	shader_file.open(filename);
	shader_str.assign(std::istreambuf_iterator<char>(shader_file), std::istreambuf_iterator<char>());
	shader_file.close();
	
	//Make the shader object
	const char* shaderSource = shader_str.c_str();
	glShaderSource(shader, 1, &shaderSource, NULL);
	
	//Compile, and make sure the compilation worked.	
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE){
		//Spit out the first 511 bytes of the compile log to cerr.
		//Note that sometimes this has useful warnings even when compilation succeeded. 
		std::cerr << "SHADER AT " << filename << " COMPILATION FAILURE!" << '\n';
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cerr << buffer << std::endl;
		return false; 
	}
	return true;
}

bool buildShaderProgram(GLuint& vertexShader, GLuint& fragmentShader, GLuint& shaderProgram, const char* vertexSrc, const char* fragmentSrc){
	
	//Vertex Shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if(!loadShader(vertexShader, vertexSrc))
		return false;
	
	//Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if(!loadShader(fragmentShader, fragmentSrc))
		return false;
	
	shaderProgram = glCreateProgram();	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "fColor");
	glLinkProgram(shaderProgram);
	
	return true;
}
