#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <Renderer/Utils/HLShaderWrapper.h>
#include <map>
#include <System/OS/PlatformIncludes.h>

namespace BearClaw {

typedef std::vector<HLShaderWrapper*> ShaderList;

class ShaderManager
{
private:
    ShaderList m_Shaders;

public:
    ShaderManager();
    void Init();
    HLShaderWrapper* GetShader(ShaderFlags Flags);
    void AddShader(HLShaderWrapper* Shader) {m_Shaders.push_back(Shader);}
};
}

#endif