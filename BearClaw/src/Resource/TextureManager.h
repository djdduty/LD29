#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <Resource/Texture.h>
#include <map>

namespace BearClaw {
typedef std::map<string, StrongTexturePtr> TextureList;

class TextureManager
{
private:
    TextureList m_Textures;

public:
    TextureManager();
    StrongTexturePtr GetTexture(string Path);
    StrongTexturePtr LoadTexture(string Path);
    void RemoveTexture(string name);
    void UpdateTextures();
};
}

#endif