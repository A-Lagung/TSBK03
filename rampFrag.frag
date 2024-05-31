#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform vec3 viewPos;

uniform vec3 LightPos;
uniform vec3 LightColor;
uniform vec3 SpecularColor;
uniform float LightStrength;


void main()
{
	//vec3 lightColor = vec3(1.0, 1.0, 1.0);
	//float ambientStrength = 0.5;
	vec3 ambient = LightStrength * LightColor;

	//vec3 lightPos = vec3(1.0, 1.0, -5.0);

	vec3 norm = normalize(Normal + texture(texture2, TexCoord).xyz);
	vec3 lightDir = normalize(LightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * LightColor;

	float specularStrength = 1.5f;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * vec3(texture(texture3, TexCoord)) * spec * SpecularColor;

	vec3 result = (ambient + diffuse + specular) * texture(texture1, TexCoord).xyz;
	FragColor = vec4(result, 1.0);
}