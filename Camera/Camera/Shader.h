

#ifndef SHARDER_H
#define SHARDER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
class Shader
{
public:
	unsigned int ID;
	Shader(const char *vertexPath, const char *fragmentPath)
	{
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		vShaderFile.exceptions(ifstream::failbit || ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit || ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			stringstream vShaderStream, fShaderStream;

			//���ļ�buffer��������ݶ��� stringstream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (ifstream::failure e)
		{
			cout << "�ļ���д���󡣡���" << endl;
		}

		const char *vShaderCode = vertexCode.c_str();
		const char *fShaderCode = fragmentCode.c_str();

		//����������ɫ��

		unsigned int vertex, fragment;
		//vertexShader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		//fragmenShader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		//shader program

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		//��Ϊ�Ѿ���shader���ӵ��� program����Կ���ɾ����
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void use() {
		glUseProgram(ID);
	}

	void setBool(const string &name, bool value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, (int)value);
	}

	void setInt(const string &name, int value) const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	}

	void setFloat(const string &name, float value)const {
		GLint location = glGetUniformLocation(ID, name.c_str());
		glUniform1f(location, value);
	}

	//void setVec2(const string &name)
private:
	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
#endif // SHARDER_H
