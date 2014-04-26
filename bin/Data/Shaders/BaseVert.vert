#version 330

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;
in vec3 Tangent;

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

out vec2 UV;
out vec3 Norm;
out vec3 Tang;

void main()
{
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Position, 1.0);
    UV = Texcoord;
    Norm = NormalMatrix * Normal;
    Tang = NormalMatrix * Tangent;
}
