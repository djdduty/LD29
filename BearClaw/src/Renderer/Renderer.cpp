#include <Renderer/Renderer.h>
#include <vector>

namespace BearClaw {

RendererInitializer::RendererInitializer()
{
    //Material pass
    //NewSetting("MS.EZ.Enabled", false);
    //NewSetting("MS.EZ.MaxObjectsToDraw", 10);

    //Lighting pass
    NewSetting("LP.SM.Enabled", true);
    NewSetting("LP.SM.PcfEnabled", true);
    NewSetting("LP.SM.BiLinearEnabled", true);
    NewSetting("LP.SM.Resolution", 512);
    NewSetting("LP.SM.MaxShadows", 4);

    NewSetting("LP.MaxPoint", 512);
    NewSetting("LP.MaxSpot", 16);
    NewSetting("LP.MaxTexSpot", 16);
    NewSetting("LP.MaxPointPerTile", 48);
    NewSetting("LP.MaxSpotPerTile", 4);
    NewSetting("LP.MaxTexSpotPerTile", 4);

    //Postprocess pass
    //Hdr
    NewSetting("PPS.HDR.Enabled", true);
    NewSetting("PPS.HDR.Quality", 0.25);
    NewSetting("PPS.HDR.BlurDist", 1.0);
    NewSetting("PPS.HDR.BlueItCount", 2);
    NewSetting("PPS.HDR.Exposure", 4.0);

    //Ssao
    NewSetting("PPS.SSAO.Enabled", true);
	NewSetting("PPS.SSAO.Quality", 0.3);
	NewSetting("PPS.SSAO.blurringIterationsNum", 2);

    //Blur
	NewSetting("PPS.Blur.Enabled", true);
	NewSetting("PPS.Blur.BlurItCount", 2);
	NewSetting("PPS.Blur.SideBlurFactor", 1.0);

    //Misc
	NewSetting("PPS.Enabled", true);
	NewSetting("PPS.sharpen", true);
	NewSetting("PPS.GammaCorrection", true);

	//Shared
	NewSetting("Quality", 1.0);
	NewSetting("LodDistance", 10.0);
	NewSetting("samples", 1);
	NewSetting("TilesXCount", 16);
	NewSetting("TilesYCount", 16);
	NewSetting("MaxTexSize", 1048576);
    NewSetting("Debug.Enabled", false);
}

Renderer::Renderer(RendererInitializer Settings)
{
    m_Settings = Settings;
    m_SceneHasBeenSet = false;
}

Renderer::~Renderer(){}

void Renderer::Init()
{
    SetupShaders();
}

void Renderer::SetupShaders()
{
    ShaderFlags* FlagsDefault = new ShaderFlags();
    FlagsDefault->DefaultShader = true;
    FlagsDefault->HasDiffuseColor = true;
    HLShaderWrapper* Shader = new HLShaderWrapper("Data/Shaders/BaseVert.vert", "Data/Shaders/BaseFrag.frag", FlagsDefault);
    
    Shader->Enable();
    Shader->SetProgramOutput(0, "FragColor");
    Shader->SetVertexAttrib(ShaderProgram::TEXTURE_COORD_ATTRIB, "Texcoord");
    Shader->SetVertexAttrib(ShaderProgram::VERTEX_COORD_ATTRIB, "Position");
    Shader->SetVertexAttrib(ShaderProgram::TANGENT_ATTRIB, "Tangent");
    Shader->SetVertexAttrib(ShaderProgram::NORMAL_ATTRIB, "Normal");

    Shader->LinkProgram();

    Environ->GetShaderManager()->AddShader(Shader);

    /*------------------------------------------------------------------------------------------------------------------------*/

    ShaderFlags* FlagsFont = new ShaderFlags();
    FlagsFont->FontShader = true;
    HLShaderWrapper* ShaderFont = new HLShaderWrapper("Data/Shaders/FontShader.vert", "Data/Shaders/FontShader.frag", FlagsFont);
    
    ShaderFont->Enable();
    ShaderFont->SetProgramOutput(0, "FragColor");
    ShaderFont->SetVertexAttrib(ShaderProgram::TEXTURE_COORD_ATTRIB, "Texcoord");
    ShaderFont->SetVertexAttrib(ShaderProgram::VERTEX_COORD_ATTRIB, "Position");
    ShaderFont->SetVertexAttrib(ShaderProgram::TANGENT_ATTRIB, "Tangent");
    ShaderFont->SetVertexAttrib(ShaderProgram::NORMAL_ATTRIB, "Normal");

    ShaderFont->LinkProgram();

    Environ->GetShaderManager()->AddShader(ShaderFont);
}

void Renderer::Render()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<StrongRenderNodePtr> AfterList = std::vector<StrongRenderNodePtr>();
	std::vector<StrongRenderNodePtr> TwoDList = std::vector<StrongRenderNodePtr>();

    if(m_SceneHasBeenSet)
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        
        for(RenderNodes::iterator it = m_RenderScene->m_Children.begin(); it != m_RenderScene->m_Children.end(); it++)
        {
			if (it->second->IsVisible())
			{
				if (!it->second->pRenderLast && !it->second->GetMaterial()->GetUseFontShader()) {
					it->second->PreRender();
					it->second->Render();
					it->second->PostRender();
				} else {
					if (it->second->GetMaterial()->GetUseFontShader()) TwoDList.push_back(it->second);
					else AfterList.push_back(it->second);
				}
            }
        }

		glClear(GL_DEPTH_BUFFER_BIT);
		for (i32 i = 0; i < AfterList.size(); i++) {
			StrongRenderNodePtr n = AfterList[i];
			if (n->IsVisible()) {
				n->PreRender();
				n->Render();
				n->PostRender();
			}
		}

		for (i32 n = 0; n < TwoDList.size(); n++) {
			glClear(GL_DEPTH_BUFFER_BIT);
			StrongRenderNodePtr r = TwoDList[n];
			if (r->IsVisible()) {
				r->PreRender();
				r->Render();
				r->PostRender();
			}
		}

		AfterList.clear();
		TwoDList.clear();
    }

}
}