#version 330

in vec3 Position;
in vec3 Normal;
in vec2 Texcoord;
in vec3 Tangent;

uniform mat4 ProjectionMatrix;

out vec2 UV;
out vec3 pos;

void main()
{
    gl_Position = vec4(Position, 1.0);
    UV = Texcoord;
    pos = Position;
}
