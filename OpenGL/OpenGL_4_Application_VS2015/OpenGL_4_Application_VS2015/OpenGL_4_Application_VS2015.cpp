
#define GLEW_STATIC

#include <iostream>
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#define NUM_Z 13
#define NUM_X 13
#define HALF_SIZE_X 5
#define HALF_SIZE_Z 5
int glWindowWidth = 640;
int glWindowHeight = 480;
int retina_width, retina_height;
GLFWwindow* glWindow = NULL;

GLuint VAO, VBO,EBO;

GLuint shaderProgram;
GLuint vertexShader;
GLuint fragmentShader;

int success;
char logInfo[512];
float angle = 0.0f;
glm::mat4 model;
glm::mat4 perspective;
glm::mat4 view;
glm::vec3 vertices[400];

GLuint index[400];
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width , height );
}
void inputMode(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		angle += 0.01;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
std::string readShaderFile(std::string fileName)
{
	std::ifstream shaderFile;
	std::string shaderString;

	//open shader file
	shaderFile.open(fileName);

	std::stringstream shaderStringStream;

	//read shader content into stream
	shaderStringStream << shaderFile.rdbuf();

	//close shader file
	shaderFile.close();

	//convert stream into GLchar array
	shaderString = shaderStringStream.str();
	return shaderString;
}
void initObjects() {
	//Vertex Buffer Objects



	int count = 0;
	int i = 0, j = 0;
	for (j = 0; j <= NUM_Z; j++) {
		for (i = 0; i <= NUM_X; i++) {
			float x = (((float)i / (NUM_X - 1)) * 2 - 1) * HALF_SIZE_X;
			float z = (((float)j / (NUM_Z - 1)) * 2 - 1) * HALF_SIZE_Z;
			vertices[count++] = glm::vec3(x, 0.0f, z);
		}
	}

	GLuint* id = &index[0];
	for (i = 0; i < NUM_Z; i++) {
		for (j = 0; j < NUM_X; j++) {
			int i0 = i * (NUM_X + 1) + j;
			int i1 = i0 + 1;
			int i2 = i0 + (NUM_X + 1);
			int i3 = i2 + 1;
			if ((j + i) % 2) {
				*id++ = i0; *id++ = i2; *id++ = i1;
				*id++ = i1; *id++ = i2; *id++ = i3;
			}
			else {
				*id++ = i0; *id++ = i2; *id++ = i3;
				*id++ = i0; *id++ = i3; *id++ = i1;
			}
		}
	}

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	//Vertex Array Objects
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glBindVertexArray(0);
}
GLuint initShaders() {
	std::string v = readShaderFile("Shaders/shader.vert");
	const GLchar* vertexSource = v.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, logInfo);
		std::cout << logInfo<<std::endl;		
	}

	
	std::string f = readShaderFile("Shaders/shader.frag");
	const GLchar* fragmentSource = f.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, logInfo);
		std::cout << logInfo << std::endl;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;

	

}
void initMatrix() {
	perspective = glm::perspective(45.0f, (GLfloat)glWindowWidth / glWindowHeight, 0.f, 1000.f);
	view = glm::lookAt(glm::vec3(0.0f, 4.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glWindow = glfwCreateWindow(glWindowWidth, glWindowHeight, "FirstWindow", NULL, NULL);
	if (glWindow == NULL)
	{
		return -1;
	}
	glfwMakeContextCurrent(glWindow);
	glfwSetFramebufferSizeCallback(glWindow, framebuffer_size_callback);
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	GLuint shaderProgram=initShaders();
	initObjects();
	initMatrix();
	int modelLoc = glGetUniformLocation(shaderProgram, "model");
	while (!glfwWindowShouldClose(glWindow))
	{
		inputMode(glWindow);

		
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		float time = glfwGetTime()*2;

		glUseProgram(shaderProgram);
		
		model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
		glUniform1f(glGetUniformLocation(shaderProgram, "time"), time);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 550, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(glWindow);
		glfwPollEvents();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glfwTerminate();
	//close GL context and any other GLFW resources
	

	return 0;
}
