#version 460 core
out vec4 FragColor;

in vec3 vPos;
in vec3 vNorm;
in vec2 texCoord;

uniform sampler2D texture0;

uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform uint serverStatus;
uniform uint time;


//NOT NORMALIZING VNORM RIGHT NOW

vec3 calculateAmbient()
{
	return vec3(0.35f, 0.35, 0.35f);
}

vec3 calculateDiffuse()
{
	vec3 posToLightDirVec = normalize(lightPos - vPos);
	vec3 diffuseColour = vec3(1.0f, 1.0f, 1.0f);
	float diffuse = clamp(dot(vNorm, posToLightDirVec ), 0, 1);
	
	vec3 diffuseLight = diffuseColour * diffuse;
	
	return diffuseLight;
}

vec3 calculateSpecular()
{
	vec3 lightToPosDirVec = normalize(vPos - lightPos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, vNorm));
	vec3 posToViewDirVec = normalize(cameraPos - vPos);
	float specularConstant = pow(max(dot(reflectDirVec, posToViewDirVec), 0.0f), 30);
	
	vec3 specularColour = vec3(1.0f, 1.0f, 1.0f) * specularConstant;

	return specularColour;
}

vec3 sinePulse(vec3 col, float speed)
{
	vec3 result = vec3(1.0f, 1.0f, 1.0f);

	float timef = float(time);
	timef /= 1000.0f;

	float factor = clamp(sin(timef * speed), 0.0f, 10000.0f);

	col = col * factor;

	return result + col;
}

void main()
{
	//AMBIENT LIGHT
	vec3 ambientFinal = calculateAmbient();

	//DIFFUSE LIGHT
	vec3 diffuseFinal = calculateDiffuse();

	//SPECULAR LIGHT
	vec3 specularFinal = calculateSpecular();
	//ATTENUATION

	vec3 serverModifier = vec3(1.0f);

	switch(serverStatus)
	{
	case 0:
		serverModifier = vec3(0.35f);
		break;
	case 1:
		serverModifier = sinePulse(vec3(0.25f, 1.0f, 0.125f), 1.5f);
		break;
	case 2:
		serverModifier = sinePulse(vec3(1.0f, 0.05f, 0.125f), 2.5f);
		break;
	}

	FragColor = 
	texture(texture0, texCoord) *
	(vec4(ambientFinal, 1.0f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f)) *
	vec4(serverModifier, 1.0f);
}