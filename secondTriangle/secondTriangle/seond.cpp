#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSrc =
"#version 150 core\n"
"in vec2 position;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(position,0.0,1.0);\n"
"}";

const char *fragmentShaderSrc =
"#version 150 core\n"
"out vec4 outColor;"
"void main()\n"
"{\n"
"	outColor = vec4(1.0,1.0,1.0,1.0);\n"
"}";
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//GLFWwindow *window = NULL;
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//	catch (const std::exception&e)
		//{//
			//std::cout << "Failed to initialize GLAD "   << std::endl;
		//}


	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//加载所有的OpenGL方法指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//1:定义顶点数据
	float vertices[] = {
		0.0f,0.5f,
		0.5f,-0.5f,
		-0.5f,-0.5f
	};

	//2，创建顶点缓冲对象
	GLuint vbo;
	glGenBuffers(1, &vbo);
	//3,绑定缓存对象
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//4:把数据拷贝到当前缓冲
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//5.创建顶点着色器
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	//编译顶点着色器
	glCompileShader(vertexShader);

	//6:片段着色器
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);

	//7：创建编程对象
	GLuint shaderProgam = glCreateProgram();
	glAttachShader(shaderProgam, vertexShader);
	glAttachShader(shaderProgam, fragmentShader);
	glLinkProgram(shaderProgam);
	glUseProgram(shaderProgam);
	//8:解析顶点属性
	GLint posAttrib = glGetAttribLocation(shaderProgam, "position");


	//9:VAO,保存了属性和VBO之间的所有链接
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//这个调用保存了当前绑定的VBO
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgam);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	std::cout << " Screen Change" << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}