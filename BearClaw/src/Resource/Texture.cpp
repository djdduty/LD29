#include <Resource/Texture.h>
#include <Utils/PngLoader.h>
#include <System/Environment.h>
#include <src/SOIL.h>

namespace BearClaw {
Texture::Texture(GLenum TextureTarget, const std::string &FileName)
{
    m_TextureTarget = TextureTarget;
    m_FileName = FileName;
}

bool Texture::Load()
{
	int Index = m_FileName.find(".");
	if(m_FileName.substr(Index) == ".png")
	{
		std::vector<uByte> Image;
		unsigned error = lodepng::decode(Image, m_Width, m_Height, m_FileName);
		if(error != 0)
		{
		  BC_LOG("Error %u : %s\n", error, lodepng_error_text(error));
		  return false;
		}

		size_t u2 = 1; while(u2 < m_Width) u2 *= 2;
		size_t v2 = 1; while(v2 < m_Height) v2 *= 2;
		double u3 = (double)m_Width / u2;
		double v3 = (double)m_Height / v2;

		std::vector<unsigned char> image2(u2 * v2 * 4);
		for(size_t y = 0; y < m_Height; y++)
		for(size_t x = 0; x < m_Width; x++)
		for(size_t c = 0; c < 4; c++)
		{
		    image2[4 * u2 * y + 4 * x + c] = Image[4 * m_Width * y + 4 * x + c];
		}

		GLfloat fLargest;
		glGetFloatv(GL_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

		m_Width = u2;
		m_Height = v2;
	} else {
		m_Texture = SOIL_load_OGL_texture
		(
			m_FileName.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		if( 0 == m_Texture )
		{
			BC_LOG("image loading error: '%s'\n", SOIL_last_result());
		}

        glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(GL_TEXTURE0+TextureUnit);
    glBindTexture(m_TextureTarget, m_Texture);
}

void Texture::Delete()
{
    glDeleteTextures(1, &m_Texture);
}
}