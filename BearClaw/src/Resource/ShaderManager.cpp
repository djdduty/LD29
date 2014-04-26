#include <Resource/ShaderManager.h>
#include <System/Environment.h>

namespace BearClaw {
ShaderManager::ShaderManager()
{

}

void ShaderManager::Init()
{

}

HLShaderWrapper* ShaderManager::GetShader(ShaderFlags Flags)
{
    for(int i = 0; i < m_Shaders.size(); i++)
    {
        HLShaderWrapper* Tmp = m_Shaders[i];
        if(Tmp->CompareFlags(Flags))
            return m_Shaders[i];
    }
    
    BC_LOG("Couldn't find shader!\n");
    return nullptr;
}
}