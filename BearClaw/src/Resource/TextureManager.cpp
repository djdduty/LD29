#include <Resource/TextureManager.h>
#include <System/Environment.h>

namespace BearClaw {
TextureManager::TextureManager()
{

}

StrongTexturePtr TextureManager::GetTexture(string Path)
{
    TextureList::iterator it = m_Textures.find(Path); 
    if (it != m_Textures.end())
    {
        return it->second;
    } else {
        return LoadTexture(Path);
    }

    UpdateTextures();
}

StrongTexturePtr TextureManager::LoadTexture(string Path)
{
    StrongTexturePtr Tex = StrongTexturePtr(new Texture(GL_TEXTURE_2D, Path));
    Tex->Load();
    m_Textures.insert(std::make_pair(Path, Tex));
    return Tex;
}

void TextureManager::RemoveTexture(string Path)
{
    TextureList::iterator it = m_Textures.find(Path); 
    if (it != m_Textures.end())
    {
        it->second->Delete();
        m_Textures.erase(it);
    } 
}

void TextureManager::UpdateTextures()
{
    for(TextureList::iterator it = m_Textures.begin(); it != m_Textures.end(); it++)
    {
        if (it->second.use_count() == 1)
        {
            string path = it->first.c_str();
            BC_LOG("No references for %s",path);
        }
    }
}
}