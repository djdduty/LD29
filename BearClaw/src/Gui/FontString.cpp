#include <Gui/FontString.h>

namespace BearClaw {
void FontString::SetContent(string Content)
{
    m_Content = Content;
    m_LastOffset = Vec2(((m_Position.x-(WindowWidth/2))/WindowWidth*2),(m_Position.y+(WindowHeight/2)-50)/WindowHeight*2);
    m_MeshNeedsUpdate = true;
}

void FontString::UpdateMesh()
{
    if(m_MeshNeedsUpdate)
    {
        VertexList Vertices;
        IndexList Indices;

        for(int i = 0; i < m_Content.size(); i++)
        {
            AddChar(m_Content[i], &Vertices, &Indices);
        }

        m_Mesh->LoadMesh(Vertices, Indices);
        m_MeshNeedsUpdate = false;
    }
}

void FontString::AddChar(Byte Code, VertexList* Verts, IndexList* Indices)
{
    FontEntry Entry = m_FontSettings->GetEntry(Code);

    if(Entry.Code != 0)
    {
        f32 tx = Entry.x / m_Texture->GetWidth();
        f32 ty = Entry.y / m_Texture->GetHeight();
        f32 tw = Entry.width / m_Texture->GetWidth();
        f32 th = Entry.height / m_Texture->GetHeight();

        f32 width = Entry.width/WindowWidth * m_Scale;
        f32 height = Entry.height/WindowHeight * m_Scale;

        f32 offx = m_LastOffset.x;
        f32 offy = m_LastOffset.y;

        if(Code == '=' || Code == '\"' || Code == '\'' || Code == '+')
            offy += (Entry.yoffset*m_Scale*0.4)/WindowHeight;
        if(Code == '-')
            offy += (Entry.yoffset * m_Scale * 0.8)/WindowHeight;
        if(Code == '*' || Code == ':')
            offy += (Entry.height * m_Scale * 0.25)/WindowHeight;
        if(Code == 'p' || Code == 'q' || Code == 'y' || Code == 'j' || Code == 'g')
            offy -= (Entry.height * m_Scale * 0.25)/WindowHeight;
        if(Code == 'Q' || Code == '3' || Code == '5' || Code == '7' || Code == '9')
            offy -= (Entry.height * m_Scale * 0.15)/WindowHeight;

        Vertex v1 = Vertex(Vec3(offx,       offy,        -1),  Vec3(0), Vec2(tx, ty+th),    Vec3(1));
        Vertex v2 = Vertex(Vec3(offx+width, offy,        -1),  Vec3(0), Vec2(tx+tw, ty+th), Vec3(1));
        Vertex v3 = Vertex(Vec3(offx,       offy+height, -1),  Vec3(0), Vec2(tx, ty),       Vec3(1));
        Vertex v4 = Vertex(Vec3(offx+width, offy+height, -1),  Vec3(0), Vec2(tx+tw, ty),    Vec3(1));
        int indoff = Verts->size();
        Verts->push_back(v1);
        Verts->push_back(v2);
        Verts->push_back(v3);
        Verts->push_back(v4);

        Indices->push_back(indoff+0);Indices->push_back(indoff+1);Indices->push_back(indoff+2);
        Indices->push_back(indoff+1);Indices->push_back(indoff+3);Indices->push_back(indoff+2);

        f32 Offset;
        if(Code == 32)
        {
            Offset = 30.0/WindowWidth * m_Scale;
        } else {
            Offset = 10.0/WindowWidth*m_Scale;
        }

        m_LastOffset.x += width+Offset;
    }
}

void FontString::Render()
{
    if(m_MeshNeedsUpdate)
        UpdateMesh();

    m_Material->Bind();
    m_Material->PrepareForRender();
    m_Mesh->Render();
    m_Material->UnBind();
}
}