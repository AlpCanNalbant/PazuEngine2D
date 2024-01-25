VERTEX

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 texCoord;

void main()
{
	texCoord = aTexCoord;

	gl_Position = proj * view * model * vec4(aPos, 1.0);
}

FRAGMENT

#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform vec3 color;
uniform sampler2D diff;
uniform bool noTex;

void main()
{
	if(!noTex)
	{
		FragColor = texture(diff, texCoord) * vec4(color, 1.0);
	}
	else
	{
		FragColor = vec4(color, 1.0);
	}
}
