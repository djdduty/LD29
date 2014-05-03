#version 330

uniform sampler2D DiffuseMap;
uniform int UseDiffuseMap;

uniform sampler2D NormalMap;
uniform int UseNormalMap;

uniform float SpecularPower;
uniform int UseSpecular;

uniform vec4 DiffuseColor;

in vec2 UV;
in vec3 Norm;
in vec3 Tang;
in vec4 WorldPos;

out vec4 FragColor;

void main()
{
    vec3 Normal;
    vec4 Color;
    
    Normal = normalize(Norm);

    if(UseDiffuseMap == 1)
    {
        Color = texture(DiffuseMap, UV) * DiffuseColor;
    } else {
        Color = DiffuseColor;
    }
    FragColor = Color;
}
