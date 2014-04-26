#ifndef HIGH_LEVEL_SHADER_PROGRAM_H
#define HIGH_LEVEL_SHADER_PROGRAM_H
/*
 *
 *ATTENTION: This is a higher level shader wrapper, I probably should rename it to prevent confusion....
 *
 */

#include <Utils/ShaderProgram.h>

namespace BearClaw {
class ShaderFlags
{
public:
    bool HasDiffuseTex;
    bool HasNormalTex;
    bool HasDiffuseColor;
    bool HasSpecular;
    bool DefaultShader;
    bool FontShader;
    bool LightingShader;
    bool TranslucencyShader;

    ShaderFlags() : 
        HasDiffuseTex(false), 
        HasNormalTex(false), 
        HasDiffuseColor(false), 
        HasSpecular(false), 
        DefaultShader(false), 
        FontShader(false), 
        LightingShader(false), 
        TranslucencyShader(false)
    {}
};

class HLShaderWrapper
{
private:

protected:
    GLint GetProgramParam(GLint param);
    ShaderProgram* m_ShaderProgram;
    ShaderFlags* m_Flags;

public:
    HLShaderWrapper(std::string VSFilePath, std::string FSFilePath, ShaderFlags* Flags);
    ~HLShaderWrapper();
    GLint GetUniformLocation(const char* UniformName);
    ShaderProgram* GetShaderProgram() {return m_ShaderProgram;}
    GLuint GetIndex() {return m_ShaderProgram->getProgramIndex();}
    void LinkProgram();
    void Enable();
    void SetVertexAttrib(ShaderProgram::AttribType Type, std::string Name);
    void SetProgramOutput(int Index, std::string Name);
    void SetShaderFlags(ShaderFlags* Flags) {m_Flags = Flags;}
    ShaderFlags* GetShaderFlags() {return m_Flags;}
    bool CompareFlags(ShaderFlags Other);
};
}

#endif
