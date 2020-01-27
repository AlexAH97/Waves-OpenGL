
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
float angleZ=0.0f;
glm::mat4 model;
glm::mat4 perspective;
glm::mat4 view;
float vertices[] = {
	//First row
	-0.5f,0.0f,0.5f,
	-0.4f,0.0f,0.5f,
	-0.3f,0.0f,0.5f,
	-0.2f,0.0f,0.5f,
	-0.1f,0.0f,0.5f,
	 0.0f,0.0f,0.5f,
	 0.1f,0.0f,0.5f,
	 0.2f,0.0f,0.5f,
	 0.3f,0.0f,0.5f,
	 0.4f,0.0f,0.5f,
	 0.5f,0.0f,0.5f,

	 //Second row
	-0.5f,0.0f,0.4f,
	-0.4f,0.0f,0.4f,
	-0.3f,0.0f,0.4f,
	-0.2f,0.0f,0.4f,
	-0.1f,0.0f,0.4f,
	 0.0f,0.0f,0.4f,
	 0.1f,0.0f,0.4f,
	 0.2f,0.0f,0.4f,
	 0.3f,0.0f,0.4f,
	 0.4f,0.0f,0.4f,
	 0.5f,0.0f,0.4f,

	 //Thirth row
	-0.5f,0.0f,0.3f,
	-0.4f,0.0f,0.3f,
	-0.3f,0.0f,0.3f,
	-0.2f,0.0f,0.3f,
	-0.1f,0.0f,0.3f,
	 0.0f,0.0f,0.3f,
	 0.1f,0.0f,0.3f,
	 0.2f,0.0f,0.3f,
	 0.3f,0.0f,0.3f,
	 0.4f,0.0f,0.3f,
	 0.5f,0.0f,0.3f,
	 
	 //Fourth row
	-0.5f,0.0f,0.2f,
	-0.4f,0.0f,0.2f,
	-0.3f,0.0f,0.2f,
	-0.2f,0.0f,0.2f,
	-0.1f,0.0f,0.2f,
	 0.0f,0.0f,0.2f,
	 0.1f,0.0f,0.2f,
	 0.2f,0.0f,0.2f,
	 0.3f,0.0f,0.2f,
	 0.4f,0.0f,0.2f,
	 0.5f,0.0f,0.2f,

	 //Fifth row
	-0.5f,0.0f,0.1f,
	-0.4f,0.0f,0.1f,
	-0.3f,0.0f,0.1f,
	-0.2f,0.0f,0.1f,
	-0.1f,0.0f,0.1f,
	 0.0f,0.0f,0.1f,
	 0.1f,0.0f,0.1f,
	 0.2f,0.0f,0.1f,
	 0.3f,0.0f,0.1f,
	 0.4f,0.0f,0.1f,
	 0.5f,0.0f,0.1f,

	 //Sixth row
	-0.5f,0.0f,0.0f,
	-0.4f,0.0f,0.0f,
	-0.3f,0.0f,0.0f,
	-0.2f,0.0f,0.0f,
	-0.1f,0.0f,0.0f,
	 0.0f,0.0f,0.0f,
	 0.1f,0.0f,0.0f,
	 0.2f,0.0f,0.0f,
	 0.3f,0.0f,0.0f,
	 0.4f,0.0f,0.0f,
	 0.5f,0.0f,0.0f,

	 //Seventh row 
	-0.5f,0.0f,-0.1f,
	-0.4f,0.0f,-0.1f,
	-0.3f,0.0f,-0.1f,
	-0.2f,0.0f,-0.1f,
	-0.1f,0.0f,-0.1f,
	 0.0f,0.0f,-0.1f,
	 0.1f,0.0f,-0.1f,
	 0.2f,0.0f,-0.1f,
	 0.3f,0.0f,-0.1f,
	 0.4f,0.0f,-0.1f,
	 0.5f,0.0f,-0.1f,

	 //Eight row 
	-0.5f,0.0f,-0.2f,
	-0.4f,0.0f,-0.2f,
	-0.3f,0.0f,-0.2f,
	-0.2f,0.0f,-0.2f,
	-0.1f,0.0f,-0.2f,
	 0.0f,0.0f,-0.2f,
	 0.1f,0.0f,-0.2f,
	 0.2f,0.0f,-0.2f,
	 0.3f,0.0f,-0.2f,
	 0.4f,0.0f,-0.2f,
	 0.5f,0.0f,-0.2f,

	//Ninth row 
	-0.5f,0.0f,-0.3f,
	-0.4f,0.0f,-0.3f,
	-0.3f,0.0f,-0.3f,
	-0.2f,0.0f,-0.3f,
	-0.1f,0.0f,-0.3f,
	 0.0f,0.0f,-0.3f,
	 0.1f,0.0f,-0.3f,
	 0.2f,0.0f,-0.3f,
	 0.3f,0.0f,-0.3f,
	 0.4f,0.0f,-0.3f,
	 0.5f,0.0f,-0.3f,
	 
	//Tenth row 
	-0.5f,0.0f,-0.4f,
	-0.4f,0.0f,-0.4f,
	-0.3f,0.0f,-0.4f,
	-0.2f,0.0f,-0.4f,
	-0.1f,0.0f,-0.4f,
	 0.0f,0.0f,-0.4f,
	 0.1f,0.0f,-0.4f,
	 0.2f,0.0f,-0.4f,
	 0.3f,0.0f,-0.4f,
	 0.4f,0.0f,-0.4f,
	 0.5f,0.0f,-0.4f,

	//Eleventh row 
	-0.5f,0.0f,-0.5f,
	-0.4f,0.0f,-0.5f,
	-0.3f,0.0f,-0.5f,
	-0.2f,0.0f,-0.5f,
	-0.1f,0.0f,-0.5f,
	 0.0f,0.0f,-0.5f,
	 0.1f,0.0f,-0.5f,
	 0.2f,0.0f,-0.5f,
	 0.3f,0.0f,-0.5f,
	 0.4f,0.0f,-0.5f,
	 0.5f,0.0f,-0.5f,
};

int index[] = {
	//First row
	0,1,11,
	1,12,11,

	1,2,12,
	2,12,13,

	2,3,13,
	3,13,14,

	3,4,14,
	4,14,15,

	4,5,15,
	5,15,16,

	5,6,16,
	6,16,17,

	6,7,17,
	7,17,18,

	7,8,18,
	8,18,19,

	8,9,19,
	9,19,20,

	9,10,20,
	10,20,21,

	//Second row
	11,12,22,
	12,22,23,

	12,13,23,
	13,23,24,

	13,14,24,
	14,24,25,

	14,15,25,
	15,25,26,

	15,16,26,
	16,26,27,

	16,17,27,
	17,27,28,

	17,18,28,
	18,28,29,

	18,19,29,
	19,29,30,

	19,20,30,
	20,30,31,

	20,21,31,
	21,31,32,

	//Thirth row
	22,23,33,
	23,33,34,

	23,24,34,
	24,34,35,

	24,25,35,
	25,35,36,

	25,26,36,
	26,36,37,

	26,27,37,
	27,37,38,

	27,28,38,
	28,38,39,

	28,29,39,
	29,39,40,

	29,30,40,
	30,40,41,

	30,31,41,
	31,41,42,

	31,32,42,
	32,42,43,

	//Fourth row
	33,34,44,
	34,44,45,

	34,35,45,
	35,45,46,

	35,36,46,
	36,46,47,

	36,37,47,
	37,47,48,

	37,38,48,
	38,48,49,

	38,39,49,
	39,49,50,

	39,40,50,
	40,50,51,

	40,41,51,
	41,51,52,

	41,42,52,
	42,52,53,

	42,43,53,
	43,53,54,

	//Fifth row
	44,45,55,
	45,55,56,

	45,46,56,
	46,56,57,

	46,47,57,
	47,57,58,

	47,48,58,
	48,58,59,

	48,49,59,
	49,59,60,

	49,50,60,
	50,60,61,

	50,51,61,
	51,61,62,

	51,52,62,
	52,62,63,

	52,53,63,
	53,63,64,

	53,54,64,
	54,64,65,

	//Sixth
	55,56,66,
	56,66,67,

	56,57,67,
	57,67,68,

	57,58,68,
	58,68,69,

	58,59,69,
	59,69,70,

	59,60,70,
	60,70,71,

	60,61,71,
	61,71,72,

	61,62,72,
	62,72,73,

	62,63,73,
	63,73,74,

	63,64,74,
	64,74,75,

	64,65,75,
	65,75,76,

	//Seventh row
	66,67,77,
	67,77,78,

	67,68,78,
	68,78,79,

	68,69,79,
	69,79,80,

	69,70,80,
	70,80,81,

	70,71,81,
	71,81,82,

	71,72,82,
	72,82,83,

	72,73,83,
	73,83,84,

	73,74,84,
	74,84,85,

	74,75,85,
	75,85,86,

	75,76,86,
	76,86,87,

	//Eighth
	77,78,88,
	78,88,89,

	78,79,89,
	79,89,90,

	79,80,90,
	80,90,91,

	80,81,91,
	81,91,92,

	81,82,92,
	82,92,93,

	82,83,93,
	83,93,94,

	83,84,94,
	84,94,95,

	84,85,95,
	85,95,96,

	85,86,96,
	86,96,97,

	86,87,97,
	87,97,98,

	//Ninth
	
	88,89,99,
	89,99,100,

	89,90,100,
	90,100,101,

	90,91,101,
	91,101,102,

	91,92,102,
	92,92,103,

	92,93,103,
	93,103,104,

	93,94,104,
	94,104,105,

	94,95,105,
	95,105,106,

	95,96,106,
	96,106,107,

	96,97,107,
	97,107,108,

	97,98,108,
	98,108,109,

	//Tenth row
	99,100,110,
	100,110,111,

	100,101,111,
	101,111,112,

	101,102,112,
	102,112,113,

	102,103,113,
	103,113,114,

	103,104,114,
	104,114,115,

	104,105,115,
	105,115,116,

	105,106,116,
	106,116,117,

	106,107,117,
	107,117,118,

	107,108,118,
	108,118,119,

	108,109,119,
	109,119,120

};
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
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		angleZ += 0.01;
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
	view = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
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
		float time = glfwGetTime();

		glUseProgram(shaderProgram);
		
		model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(angleZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(shaderProgram, "time"), time);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(index), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(glWindow);
		glfwPollEvents();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glfwTerminate();
	//close GL context and any other GLFW resources
	

	return 0;
}
