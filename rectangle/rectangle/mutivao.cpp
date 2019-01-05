#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSrc = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
}

)glsl";
const char *fragmentShaderSrc = R"glsl(
#version 330 core
out vec4 outColor;
void main()
{
	outColor = vec4(1.0f,0.5f,0.2f,1.0f);
}
)glsl";

const char *fragmentYellowShaderSrc = R"glsl(
#version 330 core
out vec4 outColor;
void main()
{
	outColor = vec4(1.0f,1.0f,0.0f,1.0f);
}

)glsl";
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"LearnOpenGL",NULL,NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::string vertexCode = "111";
	vertexCode.c_str();
	//创建顶点着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);
	//创建片段着色器

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);


	int fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentYellowShader, 1, &fragmentYellowShaderSrc, NULL);
	glCompileShader(fragmentYellowShader);

	int yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, fragmentYellowShader);
	glLinkProgram(yellowShaderProgram);


	glDeleteShader(fragmentYellowShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float fristTri[] = {
		-0.9f,-0.5f,0.0f,
		-0.0f,-0.5f,0.0f,
		-0.45f,0.5f,0.0f
	};
	float secondTri[] = {
		0.0f,-0.5f,0.0f,
		0.9f,-0.5f,0.0f,
		0.45f,0.5f,0.0f
	};

	unsigned int VBOs[2] ,VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	//第一个三角形
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fristTri), fristTri, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//第二个三角形

	glad_glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTri), secondTri, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(yellowShaderProgram);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}