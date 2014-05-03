#include <Renderer/Utils/HLShaderWrapper.h>
#include <System/Environment.h>

namespace BearClaw {
HLShaderWrapper::HLShaderWrapper(std::string VSFilePath, std::string FSFilePath, ShaderFlags* Flags)
{
    m_ShaderProgram = new ShaderProgram();
    m_ShaderProgram->init();

    m_ShaderProgram->loadShader(ShaderProgram::VERTEX_SHADER, VSFilePath);
    m_ShaderProgram->loadShader(ShaderProgram::FRAGMENT_SHADER, FSFilePath);

    m_Flags = Flags;
    
    if(m_ShaderProgram->getAllInfoLogs().size() > 0)
    {
        BC_LOG("\n");
        BC_LOG(m_ShaderProgram->getAllInfoLogs().c_str());
    }
}

HLShaderWrapper::~HLShaderWrapper()
{
    delete m_ShaderProgram;
}

void HLShaderWrapper::LinkProgram()
{
    m_ShaderProgram->prepareProgram();
}

void HLShaderWrapper::Enable()
{
    glUseProgram(m_ShaderProgram->getProgramIndex());
}

GLint HLShaderWrapper::GetUniformLocation(const char *UniformName)
{
    return glGetUniformLocation(m_ShaderProgram->getProgramIndex(), UniformName);
}

void HLShaderWrapper::SetVertexAttrib(ShaderProgram::AttribType Type, string Name)
{
    m_ShaderProgram->setVertexAttribName(Type, Name);
}

GLint HLShaderWrapper::GetProgramParam(GLint param)
{
    GLint ret;
    glGetProgramiv(m_ShaderProgram->getProgramIndex(), param, &ret);
    return ret;
}

void HLShaderWrapper::SetProgramOutput(int Index, string Name)
{
    m_ShaderProgram->setProgramOutput(Index, Name);
}

bool HLShaderWrapper::CompareFlags(ShaderFlags Other)
{
    if ((Other.HasDiffuseTex == m_Flags->HasDiffuseTex && Other.HasNormalTex == m_Flags->HasNormalTex && Other.TranslucencyShader == m_Flags->TranslucencyShader)
        || (Other.DefaultShader      == m_Flags->DefaultShader
        && Other.FontShader         == m_Flags->FontShader
        && Other.LightingShader     == m_Flags->LightingShader))
        return true;
    else
        return false;
}
}
