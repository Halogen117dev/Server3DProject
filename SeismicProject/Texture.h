#pragma once

#include<glad/glad.h>

#include<vector>
#include<memory>
#include<algorithm>
#include<string>

class Texture
{
public:
	Texture(const char* imagePath);
	~Texture();
	
	void Bind();

private:
	GLuint Handle;
	int
		Width,
		Height,
		NumChannels;

public:
	//Getter methods
	GLuint GetHandle();
};

