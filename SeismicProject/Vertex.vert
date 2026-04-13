#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec3 vPos;
out vec2 texCoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
        
void main()
{
    vPos = vec4(ModelMatrix * vec4(aPos, 1.0f)).xyz;
    texCoord = aUV;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(aPos, 1.0f);
    //gl_Position = ModelMatrix * vec4(aPos, 1.0f);

}