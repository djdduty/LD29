#include <Renderer/Material.h>
#include <Renderer/Renderer.h>
#include <Renderer/RenderNode.h>

namespace BearClaw {
Material::Material(RenderNode* Owner)                                                                       : m_DiffuseColor(Vec4(1,1,1,1)), m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(""),         m_NormalTex(""),        m_Specular(-1.0),     m_HasDiffuseMap(false), m_HasNormalMap(false), m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, string DiffuseTex)                                                    : m_DiffuseColor(Vec4(1,1,1,1)), m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(DiffuseTex), m_NormalTex(""),        m_Specular(-1.0),     m_HasDiffuseMap(true),  m_HasNormalMap(false), m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, string DiffuseTex, string NormalTex)                                  : m_DiffuseColor(Vec4(1,1,1,1)), m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(DiffuseTex), m_NormalTex(NormalTex), m_Specular(-1.0),     m_HasDiffuseMap(true),  m_HasNormalMap(true),  m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, Vec4 DiffuseColor)                                                    : m_DiffuseColor(DiffuseColor),  m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(""),         m_NormalTex(""),        m_Specular(-1.0),     m_HasDiffuseMap(false), m_HasNormalMap(false), m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, Vec4 DiffuseColor, string DiffuseTex)                                 : m_DiffuseColor(DiffuseColor),  m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(DiffuseTex), m_NormalTex(""),        m_Specular(-1.0),     m_HasDiffuseMap(true),  m_HasNormalMap(false), m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, Vec4 DiffuseColor, string DiffuseTex, string NormalTex)               : m_DiffuseColor(DiffuseColor),  m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(DiffuseTex), m_NormalTex(NormalTex), m_Specular(-1.0),     m_HasDiffuseMap(true),  m_HasNormalMap(true),  m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, f32 Specular)                                                         : m_DiffuseColor(Vec4(1,1,1,1)), m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(""),         m_NormalTex(""),        m_Specular(Specular), m_HasDiffuseMap(false), m_HasNormalMap(false), m_HasSpecular(true),  m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, f32 Specular, Vec4 DiffuseColor)                                      : m_DiffuseColor(DiffuseColor),  m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(""),         m_NormalTex(""),        m_Specular(Specular), m_HasDiffuseMap(false), m_HasNormalMap(false), m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, f32 Specular, Vec4 DiffuseColor, string DiffuseTex)                   : m_DiffuseColor(DiffuseColor),  m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(DiffuseTex), m_NormalTex(""),        m_Specular(Specular), m_HasDiffuseMap(true),  m_HasNormalMap(false), m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}
Material::Material(RenderNode* Owner, f32 Specular, Vec4 DiffuseColor, string DiffuseTex, string NormalTex) : m_DiffuseColor(DiffuseColor),  m_IsBillboard(false), m_UVAdd(Vec2(0,0)), m_DiffuseTex(DiffuseTex), m_NormalTex(NormalTex), m_Specular(Specular), m_HasDiffuseMap(true),  m_HasNormalMap(true),  m_HasSpecular(false), m_FlagsNeedUpdate(true), m_Owner(Owner), m_UseDefaultShader(true), m_VertShader(""), m_FragShader(""), m_UseFontShader(false){}

void Material::SetDiffuseTex(string DiffuseTex)
{
    m_DiffuseTex = DiffuseTex;
    
    m_Texture.reset();

    m_HasDiffuseMap = false;
    if(m_DiffuseTex != "")
    {
        m_HasDiffuseMap = true;
        m_Texture = TextureMgr->GetTexture(DiffuseTex);
    }

    m_FlagsNeedUpdate = true;
}

void Material::SetDiffuseColor(Vec4 DiffuseColor)
{
    m_DiffuseColor = DiffuseColor;
}

void Material::SetNormalTex(string NormalTex)
{
    m_NormalTex = NormalTex;

    m_NormalMap.reset();

    m_HasNormalMap = false;
    if(m_NormalTex != "")
    {
        m_HasNormalMap = true;
        m_NormalMap = TextureMgr->GetTexture(NormalTex);
    }

    m_FlagsNeedUpdate = true;
}

void Material::SetSpecular(f32 Specular)
{
    m_Specular = Specular;

    m_HasSpecular = false;
    if(m_Specular != -1.0)
        m_HasSpecular = true;

    m_FlagsNeedUpdate = true;
}

void Material::Bind()
{
    Update();
    m_Shader = ShaderMgr->GetShader(m_ShaderFlags);
    glUseProgram(m_Shader->GetIndex());
}

void Material::Update()
{
    if(m_FlagsNeedUpdate)
    {
        m_ShaderFlags = ShaderFlags();
        
        if(m_UseFontShader)
        {
            m_ShaderFlags.FontShader = true;
            m_UseDefaultShader = false;
        }

        if(m_HasDiffuseMap)
            m_ShaderFlags.HasDiffuseTex = true;
        if(m_HasNormalMap)
            m_ShaderFlags.HasNormalTex = true;
        if(m_HasSpecular)
            m_ShaderFlags.HasSpecular = true;
        if(m_UseDefaultShader)
            m_ShaderFlags.DefaultShader = true;

        UpdateShader();
		m_FlagsNeedUpdate = false;
    }
}

void Material::UpdateShader()
{
    m_Shader = ShaderMgr->GetShader(m_ShaderFlags);
    if(!m_UseFontShader)
    {
        m_ModelViewMatrixLoc = m_Shader->GetUniformLocation("ModelViewMatrix");
        m_ProjectionMatrixLoc = m_Shader->GetUniformLocation("ProjectionMatrix");
        m_NormalMatrixLoc = m_Shader->GetUniformLocation("NormalMatrix");

        m_DiffuseMapLoc = m_Shader->GetUniformLocation("DiffuseMap");

        m_UseNormalMapLoc = m_Shader->GetUniformLocation("UseNormalMap");
		m_NormalMapLoc = m_Shader->GetUniformLocation("NormalMap");

		m_UseSpecularLoc = m_Shader->GetUniformLocation("UseSpecular");
		m_SpecularLoc = m_Shader->GetUniformLocation("SpecularPower");
	}

	m_UVMultLoc = m_Shader->GetUniformLocation("UVAdd");
    m_UseDiffuseMapLoc = m_Shader->GetUniformLocation("UseDiffuseMap");
    m_DiffuseColorLoc = m_Shader->GetUniformLocation("DiffuseColor");
}

void Material::PrepareForRender()
{
    if(m_Shader != nullptr)
        m_Shader->Enable();

    if(!m_UseFontShader)
    {
        Mat4 Model = m_Owner->GetTransform();
        Mat4 View = RenderSingleton->GetRenderScene()->GetActiveCamera()->GetTransform();

        Mat4 Projection = RenderSingleton->GetRenderScene()->GetActiveCamera()->GetProjection();

        Mat4 ModelView = Model * View;
		if (m_IsBillboard) {
			Vec3 MPos = m_Owner->GetNode()->GetPosition();
			Vec3 CamPos = RenderSingleton->GetRenderScene()->GetActiveCamera()->GetPosition();
			Vec3 look = (MPos + CamPos).Normalize();
			Vec3 up = Vec3(0, 1, 0);
			Vec3 right = look.Cross(up);
			Mat4 m2 = Mat4(1.0f);
			m2.m[0][0] = right.x; m2.m[1][0] = up.x; m2.m[2][0] = look.x; m2.m[3][0] = MPos.x;
			m2.m[0][1] = right.y; m2.m[1][1] = up.y; m2.m[2][1] = look.y; m2.m[3][1] = MPos.y;
			m2.m[0][2] = right.z; m2.m[1][2] = up.z; m2.m[2][2] = look.z; m2.m[3][2] = MPos.z;
			ModelView = m2 * View;
		}

        Mat3 NormalMatrix = Mat3(Model, true);
        
        glUniformMatrix4fv(m_ModelViewMatrixLoc, 1, GL_FALSE, &ModelView.m[0][0]);
        glUniformMatrix4fv(m_ProjectionMatrixLoc, 1, GL_FALSE, &Projection.m[0][0]);
        glUniformMatrix3fv(m_NormalMatrixLoc, 1, GL_FALSE, &NormalMatrix.m[0][0]);

        /*Diffuse Map*/
        if(m_HasDiffuseMap)
        {
            m_Texture->Bind(0);
            glUniform1i(m_DiffuseMapLoc,0);
            glUniform1i(m_UseDiffuseMapLoc,1);
        } else {    
            glUniform1i(m_UseDiffuseMapLoc,0);
        }
        /**/

        /*Normal Map*/
        if(m_HasNormalMap)
        {
            m_NormalMap->Bind(1);
            glUniform1i(m_NormalMapLoc,1);
            glUniform1i(m_UseNormalMapLoc,1);
        } else {
            glUniform1i(m_UseNormalMapLoc,0);
        }
        /**/

        /*Specular Component*/
        if(m_HasSpecular)
        {
            glUniform1f(m_SpecularLoc,m_Specular);
            glUniform1i(m_UseSpecularLoc,1);
        } else {
            glUniform1i(m_UseSpecularLoc,0);
        }
        /**/
    } else {
        //todo: ortho
        m_Texture->Bind(0);
        glUniform1i(m_DiffuseMapLoc,0);
    }


	glUniform2f(m_UVMultLoc, m_UVAdd.x, m_UVAdd.y);
    glUniform4f(m_DiffuseColorLoc,m_DiffuseColor.x, m_DiffuseColor.y, m_DiffuseColor.z, m_DiffuseColor.w);
}

HLShaderWrapper* Material::GetShader()
{
    return m_Shader;
}

void Material::Save(string Path)
{}

void Material::Load(string Path)
{}
}
