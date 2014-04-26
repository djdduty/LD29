#ifndef MESH_H
#define MESH_H

#include <vector>
#include <Utils/Math.h>
#include <System/Environment.h>
#include <System/BcTypes.h>

namespace BearClaw {
class Vertex
{
public:
    Vec3 Pos;
    Vec3 Normal;
    Vec2 UV;
    Vec3 Tangent;
    Vertex(Vec3 Pos, Vec3 Normal, Vec2 UV) : Pos(Pos), Normal(Normal), UV(UV), Tangent(Vec3(0,0,0)){}
    Vertex(Vec3 Pos, Vec3 Normal, Vec2 UV, Vec3 Tangent) : Pos(Pos), Normal(Normal), UV(UV), Tangent(Tangent){}

    void SetTangent(Vec3 T)
    {
        Tangent = T;
    }
};

typedef std::vector<Vertex> VertexList;
typedef std::vector<unsigned int> IndexList;

class Mesh
{
private:
    GLuint m_Vao;
    GLuint m_Vbo;
    GLuint m_Ibo;

public:
    int IndexCount;

    Mesh();
    ~Mesh();

    void LoadMesh(VertexList VList, IndexList IList);
    VertexList CalculateTangents(VertexList VList, IndexList IList);
    void Render();
};
}
#endif