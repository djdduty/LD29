#version 330

uniform sampler2D DiffuseMap;
uniform int UseDiffuseMap;

uniform sampler2D NormalMap;
uniform int UseNormalMap;

uniform float SpecularPower;
uniform int UseSpecular;

uniform vec4 DiffuseColor;

uniform vec2 UVAdd;

in vec2 UV;
in vec3 Norm;
in vec3 Tang;
in vec4 WorldPos;

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

vec4 CalcPointLight(vec3 NormalFinal) 
{
	vec3 LightPos = vec3(0,20,0);
	vec3 LightColor = vec3(1,1,1);
	float LightIntensity = 10.0;
	float AmbientIntensity = 0.3;
	float AttenConst = 1.0;
	float AttenLinear = 0.5;
	float AttenExp = 0.5;
	float Atten, Distance;
	
	vec3 LightDir = (WorldPos.xyz - LightPos);
	float NdotL = max(dot(NormalFinal, -LightDir),0);
	vec4 Color, DiffuseColor, AmbientColor;
	Distance = length(LightDir);
	
	if(NdotL > 0.0) {
		Atten = AttenConst + AttenLinear * Distance + AttenExp * Distance * Distance;
		DiffuseColor = vec4(LightColor, 1.0) * LightIntensity * NdotL;
		AmbientColor = vec4(LightColor, 1.0) * AmbientIntensity;
		Color = DiffuseColor + AmbientColor;
		vec4 retv = Color/Atten;
		retv.a = 1.0;
		return retv;
	}
	
	return vec4(AmbientIntensity, AmbientIntensity, AmbientIntensity, 1.0);
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
        Color = texture(DiffuseMap, vec2(UV.x+UVAdd.x, UV.y+UVAdd.y)) * DiffuseColor;
    } else {
        Color = DiffuseColor;
    }
    
    if(Color.a < 0.5) discard;
    FragColor = Color;// * CalcPointLight(Normal);
}
