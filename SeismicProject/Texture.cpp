#include "Texture.h"

#include<exception>

//STB_IMAGE CANNOT BE DEFINED IN A HEADER. ONLY IN CPP FILES. GREAT.
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>


Texture::Texture(const char* imagePath)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(imagePath, &Width, &Height, &NumChannels, 0);
	glGenTextures(1, &Handle);
	glBindTexture(GL_TEXTURE_2D, Handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//throw new std::exception("Image Not Loaded");
	}


	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}

Texture::~Texture()
{
	glDeleteTextures(1, &Handle);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, Handle);
}

GLuint Texture::GetHandle()
{
	return Handle;
}