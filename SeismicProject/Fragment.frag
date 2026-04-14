#version 460 core
out vec4 FragColor;

in vec3 vPos;
in vec3 vNorm;
in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightPos;
uniform vec3 cameraPos;


void main()
{
	//AMBIENT LIGHT
	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);

	//DIFFUSE LIGHT
	vec3 posToLightDirVec = normalize(lightPos - vPos);
	vec3 diffuseColour = vec3(1.0f, 1.0f, 1.0f);
	float diffuse = clamp(dot(normalize(vNorm), posToLightDirVec ), 0, 1);
	
	vec3 diffuseLight = diffuseColour * diffuse;

	//SPECULAR LIGHT
	vec3 lightToPosDirVec = normalize(vPos - lightPos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vNorm)));
	vec3 posToViewDirVec = normalize(cameraPos - vPos);
	float specularConstant = pow(max(dot(reflectDirVec, posToViewDirVec), 0.0f), 30);
	
	vec3 specularColour = vec3(1.0f, 1.0f, 1.0f) * specularConstant;

	//ATTENUATION


	FragColor = 
	texture(texture0, texCoord) *
	(vec4(ambientLight, 1.0f) + vec4(diffuseLight, 1.0f) + vec4(specularColour, 1.0f));

	//FragColor = texture(texture0, texCoord)	;
}