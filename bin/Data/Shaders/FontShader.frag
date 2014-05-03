#version 330

uniform sampler2D DiffuseMap;
uniform vec4 DiffuseColor;
uniform vec2 UVAdd;

in vec2 UV;
in vec3 pos;

out vec4 FragColor;

void main()
{
    vec4 Color;
	vec2 Uv = vec2(UV.x + UVAdd.x, UV.y + UVAdd.y);
    Color = texture(DiffuseMap, Uv) * DiffuseColor;
    FragColor = Color;
}
