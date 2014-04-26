#ifndef MATERIAL_H
#define MATERIAL_H

#include <Utils/Math/Vec3.h>
#include <System/Environment.h>
#include <Resource/ShaderManager.h>
#include <Renderer/Utils/HLShaderWrapper.h>
#include <Resource/Texture.h>

namespace BearClaw {
class RenderNode;

class Material
{
private:
    ShaderFlags m_ShaderFlags;
    string m_DiffuseTex;
    string m_NormalTex;
    Vec4 m_DiffuseColor;
    f32 m_Specular;
    bool m_FlagsNeedUpdate;
    bool m_HasNormalMap;
    bool m_HasDiffuseMap;
    bool m_HasSpecular;
    bool m_UseDefaultShader;
    bool m_UseFontShader;

    string m_VertShader;//todo: add setter
    string m_FragShader;//todo: add setter
    HLShaderWrapper* m_Shader;//todo: add shader compile function called by setters for above

    RenderNode* m_Owner;

    StrongTexturePtr m_Texture;
    StrongTexturePtr m_NormalMap;

    GLuint m_ModelViewMatrixLoc;
    GLuint m_ProjectionMatrixLoc;
    GLuint m_NormalMatrixLoc;

    GLuint m_UseDiffuseMapLoc;
    GLuint m_DiffuseMapLoc;

    GLuint m_UseNormalMapLoc;
    GLuint m_NormalMapLoc;

    GLuint m_UseSpecularLoc;
    GLuint m_SpecularLoc;
    
    GLuint m_DiffuseColorLoc;

public:
    Material(RenderNode* Owner);
    Material(RenderNode* Owner, string DiffuseTex);
    Material(RenderNode* Owner, Vec4 DiffuseColor);
    Material(RenderNode* Owner, Vec4 DiffuseColor, string DiffuseTex);
    Material(RenderNode* Owner, Vec4 DiffuseColor, string DiffuseTex, string NormalTex);
    Material(RenderNode* Owner, string DiffuseTex, string NormalTex);
    Material(RenderNode* Owner, f32 Specular);
    Material(RenderNode* Owner, f32 Specular, Vec4 DiffuseColor);
    Material(RenderNode* Owner, f32 Specular, Vec4 DiffuseColor, string DiffuseTex);
    Material(RenderNode* Owner, f32 Specular, Vec4 DiffuseColor, string DiffuseTex, string NormalTex);

    void SetDiffuseTex(string DiffuseTex);
    void SetDiffuseColor(Vec4 DiffuseColor);
    void SetNormalTex(string NormalTex);
    void SetSpecular(f32 Specular);

    void Bind();
    void Update();
    void UpdateShader();
    void PrepareForRender();
    HLShaderWrapper* GetShader();

    void Save(string Path);
    void Load(string Path);

    void UseFontShader(bool Use) {m_UseFontShader = Use; m_UseDefaultShader = !Use; m_FlagsNeedUpdate = true;}
    StrongTexturePtr GetDiffuseTexturePtr() {return m_Texture;}
    void UnBind() {glUseProgram(0);}
};
}

#endif