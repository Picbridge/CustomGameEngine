#version 400
struct Material 
{
	vec3 color;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec3 FragPos;
in vec3 viewDir;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform Material material;
uniform bool hasDiffuse; 
uniform bool hasSpecular; 
uniform float rotAngle; 
uniform mat4 localModel;

vec2 CalculateUV();
vec2 Planar();
vec2 Cylinderical();
vec2 Spherical();
vec2 RotateUV(vec2 uv, mat4 matrix);

void main()
{
	vec4 result = vec4(0, 0, 0, 0);
	vec2 uv = CalculateUV();
	// rotate texture along with the object
	//uv = RotateUV(uv, localModel);
	
	vec4 texColor = vec4(material.color, 1.0);
	
	// apply the existing texture
	if(hasDiffuse)
		texColor *= texture(material.diffuse, uv);
	if(hasSpecular)
		texColor *= texture(material.specular, uv);

	float colorDifference = length(texColor.rgb - vec3(0.0, 1.0, 0.0));

	if(colorDifference < 0.6)
        texColor.a = 0.0;

    result += texColor;
    FragColor = result;
}

vec2 CalculateUV() {
	//vec4 localPos = inverse(localModel) * vec4(FragPos, 1.0);
    vec2 uv = TexCoords;
	uv.x *= 2.5;
	uv.y *= 1.25;

	uv = uv * 0.5 + 0.51;
	uv.y = 1 - uv.y;
    return uv;
}

vec2 Planar()
{
	vec2 uv_planar = FragPos.xy;
	return uv_planar;
}

vec2 Cylinderical()
{
	float r = sqrt(pow(FragPos.x,2)+pow(FragPos.y,2));
	float theta = atan(FragPos.y/FragPos.x);
	vec2 uvreturn;
	uvreturn.x = theta/(2*3.141592);
	uvreturn.y = FragPos.z;
	return uvreturn;
}

vec2 Spherical()
{
	float r = sqrt(pow(FragPos.x, 2) + pow(FragPos.y, 2) + pow(FragPos.z, 2));
	float theta = atan(FragPos.y/FragPos.x);
	float phi = acos(FragPos.z / r);
	vec2 uvreturn;
	uvreturn.x = theta/(2*3.141592);
	uvreturn.y = phi / (3.141592);
	return uvreturn;
}

vec2 RotateUV(vec2 uv, mat4 matrix)
{
    vec2 res;

    mat4 inverseMatrix = inverse(matrix);

    vec4 rotatedUV = vec4(uv.x, uv.y, 0.0f, 1.0f); // Extend UV to vec4
    rotatedUV = inverseMatrix * rotatedUV; 

    res.x = rotatedUV.x;
    res.y = rotatedUV.y;

    return res;
}