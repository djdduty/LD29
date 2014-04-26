#version 330

uniform sampler2D DiffuseMap;
uniform vec4 DiffuseColor;

in vec2 UV;
in vec3 pos;

out vec4 FragColor;

void main()
{
    vec4 Color;
   
    Color = texture(DiffuseMap, UV) * DiffuseColor;
    FragColor = Color;
}
