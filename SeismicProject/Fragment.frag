#version 460 core
out vec4 FragColor;

in vec3 vPos;
in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColor = (texture(texture0, texCoord) * texture(texture1, texCoord));
	//FragColor = vec4(1.0f, 1.0f, 0.5f, 1.0f);
	//FragColor = vec4(texCoord, 1.0f, 1.0f);
}