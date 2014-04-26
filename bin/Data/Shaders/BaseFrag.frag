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

out vec4 FragColor;

vec3 CalcBumpedNormal()
{
    vec3 Normal = normalize(Norm);
    vec3 Tangent = normalize(Tang);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = texture(NormalMap, UV).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0,1.0,1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}

void main()
{
    vec3 Normal;
    vec4 Color;
    
    if(UseNormalMap == 1)
    {
        Normal = CalcBumpedNormal();
    } else {
        Normal = normalize(Norm);
    }

    if(UseDiffuseMap == 1)
    {
        Color = texture(DiffuseMap, UV) * DiffuseColor;
    } else {
        Color = DiffuseColor;
    }
    FragColor = Color;
}
