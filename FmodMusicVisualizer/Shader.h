#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shader {
private:
	//load shaders
	string loadVertexShader(const char* vertexPath);
	string loadFragmentShader(const char* fragmentPath);

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	//program ID
	unsigned int ID;

	//activate and use the shader
	void use();

	//uniform utility functions
	void setFloat(const string& name, float value) const; 

};

#endif