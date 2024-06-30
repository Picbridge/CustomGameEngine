#version 400

in vec3 aPos;
in vec3 aNormal;

out vec3 FragPos;
out vec3 viewDir;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform vec3 viewPos; //Camera position

void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0));
    vec3 norm = mat3(transpose(inverse(model))) * aNormal;
	   // Calculate view direction
   viewDir = normalize(FragPos);//normalize(viewPos - FragPos);
      // Normalize vector3 Normal
   Normal = normalize(norm);

   TexCoords = vec2(aPos.x, aPos.y);

    gl_Position = projection * view * model * vec4(aPos, 1.0);//vec4(FragPos, 1.0);
}