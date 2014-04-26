#ifndef BC_TEXTURE_H
#define BC_TEXTURE_H

#include <System/OS/PlatformIncludes.h>
#include <Utils/BcString.h>
#include <string>

namespace BearClaw {
class Texture
{
private:
    std::string         m_FileName;
    GLenum              m_TextureTarget;
    GLuint              m_Texture;
    unsigned m_Width,   m_Height;
    //std::vector<uByte>  m_Image;

public:
    Texture(GLenum TextureTarget, const std::string &FileName);
    bool Load();
    void Bind(GLenum TextureUnit);
    GLuint GetGlTexture();
    unsigned GetWidth() {return m_Width;}
    unsigned GetHeight() {return m_Height;}
    void Delete();
};

typedef shared_ptr<Texture> StrongTexturePtr;
typedef weak_ptr<Texture> WeakTexturePtr;
}

#endif