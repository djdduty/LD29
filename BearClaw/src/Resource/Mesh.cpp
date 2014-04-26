#include <Resource/Mesh.h>
#include <Utils/ShaderProgram.h>

namespace BearClaw {
Mesh::Mesh()
{

}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_Vbo);
    glDeleteBuffers(1, &m_Ibo);
}

void Mesh::LoadMesh(VertexList V, IndexList I)
{
    if(V[0].Tangent.x == 0.0 && V[0].Tangent.y == 0.0 && V[0].Tangent.z == 0.0)
    {
        V = CalculateTangents(V, I);
    }

    int VertCount = V.size();
    IndexCount = I.size();

    glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

    glEnableVertexAttribArray(ShaderProgram::VERTEX_COORD_ATTRIB);
    glEnableVertexAttribArray(ShaderProgram::NORMAL_ATTRIB);
    glEnableVertexAttribArray(ShaderProgram::TEXTURE_COORD_ATTRIB);
    glEnableVertexAttribArray(ShaderProgram::TANGENT_ATTRIB);

    glGenBuffers(1, &m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VertCount, &V[0], GL_STATIC_DRAW);
    glVertexAttribPointer(ShaderProgram::VERTEX_COORD_ATTRIB,   3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glVertexAttribPointer(ShaderProgram::NORMAL_ATTRIB,         3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)12);
    glVertexAttribPointer(ShaderProgram::TEXTURE_COORD_ATTRIB,  2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)24);
    glVertexAttribPointer(ShaderProgram::TANGENT_ATTRIB,        3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)32);


    glGenBuffers(1, &m_Ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * IndexCount, &I[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Render()
{
    glBindVertexArray(m_Vao);
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

VertexList Mesh::CalculateTangents(VertexList V, IndexList I)
{
    for (i32 i = 0 ; i < I.size(); i += 3) {
        Vertex v0 = V[I[i+0]];
        Vertex v1 = V[I[i+1]];
        Vertex v2 = V[I[i+2]];
        
        Vec3 Edge1 = v1.Pos - v0.Pos;
        Vec3 Edge2 = v2.Pos - v0.Pos;
        
        f32 DeltaU1 = v1.UV.x - v0.UV.x;
        f32 DeltaV1 = v1.UV.y - v0.UV.y;
        f32 DeltaU2 = v2.UV.x - v0.UV.x;
        f32 DeltaV2 = v2.UV.y - v0.UV.y;
        
        f32 f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);
        
        Vec3 Tangent;
        
        Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
        Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
        Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);
        
        Tangent = Tangent.Normalize();
        
        V[I[i+0]].Tangent += Tangent;
        V[I[i+1]].Tangent += Tangent;
        V[I[i+2]].Tangent += Tangent;
    }

    return V;
}
}