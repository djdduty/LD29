#ifndef FISTCOMPONENT_H
#define FISTCOMPONENT_H

#include <Scene/Component.h>
#include <Renderer/RenderNode.h>
#include <Resource/Mesh.h>
#include <soloud.h>
#include <soloud_wav.h>

using namespace BearClaw;
namespace LD29 {
class FistComponent : public Component, RenderNode
{
private:
	Mesh* m_Mesh;
	f32 m_PunchTimer;
	SoLoud::Soloud* m_Audio;
	SoLoud::Wav m_PunchSound;

protected:

public:
	FistComponent(BcString Name, SoLoud::Soloud* S);
	~FistComponent();
	void OnInit();
	void OnDeInit();
	void OnEnable();
	void OnDisable();
	void Update(f64 DeltaTime);

	void InitRenderNode();
	void Render();

	void Punch();

	//misc
	void CreateVBO();
	void CreateIBO();
};
}
#endif