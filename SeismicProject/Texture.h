#pragma once

#include<glad/glad.h>

#include<vector>
#include<memory>
#include<algorithm>
#include<string>

class Texture
{
public:
	//GL
	Texture(const char* imagePath, GLint internalFormat = GL_RGB, GLenum externalFormat = GL_RGB);
	~Texture();
	
	void Bind();

private:
	GLuint Handle;
	int
		Width,
		Height,
		NumChannels;
	GLint Format;
public:
	//Getter methods
	GLuint GetHandle();
	GLint GetFormat();
};

