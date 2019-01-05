#ifndef  SHADER_H
#define  SHADER_H


#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;
class Shader {
public:
	// the Program Id
	unsigned int ID;
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;


		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			//open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			//read file's buffer content into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//关闭文件句柄
			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();




		}
		catch (std::ifstream::failure e) {
			std::cout << "打开文件失败" << std::endl;
		}

		const char *vShaderCode = vertexCode.c_str();
		const char *fShaderCode = fragmentCode.c_str();

		//编译shader
		unsigned int vertex, fragment;
		//vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//create shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		//delete the shaders as they're linked into our program
		//and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void use() {
		glUseProgram(ID);
	}
	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);

	}
	void setInt(const std::string &name, int value)const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

	}
	void setFloat(const std::string &name, float value)const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
private :
	void checkCompileErrors(unsigned int shader, string type){
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				cout << "Error Shader_compilation_error of type: " << type << infoLog << "\n -- --------------------------------------------------- -- " << endl;
			}
		}else{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				cout << "error :: program_linking_error of type :" << type << "\n" << "\n -- --------------------------------------------------- -- " << endl;
			}
			
		}

	}
};
#endif // ! SHADER_H