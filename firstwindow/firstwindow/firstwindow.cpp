#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

 void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 1000, "First Window", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glViewport(0, 0, 400, 300);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glClearColor(1.0f, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glViewport(0, 0, 400, 300);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	//glViewport(0, 0, 400, 300);

}