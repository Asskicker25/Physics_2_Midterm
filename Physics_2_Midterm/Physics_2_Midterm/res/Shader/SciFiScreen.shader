#vertex

#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 vertexColor;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 VertexColor;

uniform vec3 textureTiling;  //x, y

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 inverseModel;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1);
	TexCoord = vec2(texCoord.x * textureTiling.x, 1.0 - texCoord.y * textureTiling.y);

	vec4 worlNormal = inverseModel * vec4(normal, 1.0f);
	Normal = normalize(worlNormal.xyz);
	//Normal = normal;
	
	FragPos = vec3(model * vec4(position, 1.0f));
	VertexColor = vertexColor;
};


#fragment

#version 330 core


out vec4 color;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 VertexColor;

uniform sampler2D texture_diffuse;

uniform float flickerValue;
uniform float iTime;
uniform bool staticApply;

float noise(vec2 pos, float evolve) {
    
    float e = fract((evolve*0.01));
    
    // Coordinates
    float cx  = pos.x*e;
    float cy  = pos.y*e;
    
    return fract(23.0*fract(2.0/fract(fract(cx*2.4/cy*23.0+pow(abs(cy/22.4),3.3))*fract(cx*evolve/pow(abs(cy),0.050)))));
}

void main()
{
	vec2 diffuseUV = TexCoord;
	diffuseUV.y -= flickerValue;
	vec4 texColor = texture(texture_diffuse, diffuseUV);

  	vec3 staticColor = vec3(noise(TexCoord,iTime));

	vec3 result;

	if(staticApply)
	{
	 	result = texColor.rgb - staticColor.rgb;
	}
	else
	{
	 	result = texColor.rgb ;
	}

	color = vec4(result, 1.0);
	
}
