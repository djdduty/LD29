#ifndef BILLBOARDCOMPONENT_H
#define BILLBOARDCOMPONENT_H

#include <Scene/Component.h>
#include <Renderer/RenderNode.h>
#include <Resource/Mesh.h>

using namespace BearClaw;
namespace LD29{
class BillboardComponent : public Component, public RenderNode
{
private:
	Mesh* m_Mesh;
	string m_TexName;
	Vec2 m_Size;
	bool m_SpriteSheet;

protected:

public:
	BillboardComponent(BcString Name, string TexName, Vec2 Size, bool SpriteSheet);
	~BillboardComponent();
	void OnInit();
	void OnDeInit();
	void OnEnable();
	void OnDisable();
	void Update(f64 DeltaTime);

	void InitRenderNode();
	void Render();

	void SetTransform(Mat4 trans) {
		m_Transform = trans;
	}

	//misc
	void CreateVBO();
	void CreateIBO();
};
}

#endif