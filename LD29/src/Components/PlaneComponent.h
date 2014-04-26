#ifndef PLANECOMPONENT_H
#define PLANECOMPONENT_H

#include <Scene/Component.h>
#include <Renderer/RenderNode.h>
#include <Resource/Mesh.h>

using namespace BearClaw;
namespace LD29 {
class PlaneComponent : public Component, public RenderNode
{
private:
	VertexList m_Verts;

protected:
	Mesh* m_Mesh;

public:
	PlaneComponent(BcString Name, VertexList Verts);
	~PlaneComponent();
	void OnInit();
	void OnDeInit();
	void OnEnable();
	void OnDisable();
	void Update(f64 DeltaTime);

	void InitRenderNode();
	void Render();

	//misc
	void CreateVBO();
	void CreateIBO();
};
}

#endif