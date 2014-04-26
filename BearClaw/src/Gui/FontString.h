#ifndef FONT_STRING_H
#define FONT_STRING_H

#include <System/Environment.h>
#include <Renderer/Material.h>
#include <Resource/Mesh.h>
#include <Gui/FontFile.h>

namespace BearClaw {
class FontString
{
private:
    string m_Content;
    Vec2 m_Position;
    Vec2 m_LastOffset;

    Mesh* m_Mesh;
    Material* m_Material;
    f32 m_Scale;
    
    StrongTexturePtr m_Texture;
    FontFile* m_FontSettings;

    bool m_MeshNeedsUpdate;

public:
    FontString(string Content, Vec2 Pos, FontFile* File, f32 Scale) : m_Content(Content), m_Position(Pos), m_MeshNeedsUpdate(true), m_FontSettings(File), m_LastOffset(Vec2(((Pos.x-(WindowWidth/2))/WindowWidth*2),(Pos.y+(WindowHeight/2)-50)/WindowHeight*2))
    {     
        m_Material = new Material(nullptr);
        m_Material->UseFontShader(true);
        m_Material->SetDiffuseColor(Vec4(0,0,1,1));
        m_Material->SetDiffuseTex(m_FontSettings->GetImagePath());
        m_Texture = m_Material->GetDiffuseTexturePtr();
        m_Mesh = new Mesh();
        m_Scale = Scale;
    }
    
    void AddChar(Byte Code, VertexList* Verts, IndexList* Indices);
	void SetScale(f32 Scale) { m_Scale = Scale; SetContent(m_Content); }
    void SetContent(string Content);
    void UpdateMesh();
    void Render();
};
}

#endif