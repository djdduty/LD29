#include <Components/TestRenderComponent.h>
#include <Scene/Scene.h>
#include <System/Environment.h>
#include <Resource/Shapes.h>

namespace BearClaw {
TestRenderComponent::TestRenderComponent(BcString Name) : Component(Name), RenderNode(Name + "-RenderNode")
{
    Timer = 0.0f;
    m_Transform = Mat4();
    M = new Mesh();
}

TestRenderComponent::~TestRenderComponent()
{

}

void TestRenderComponent::OnInit()
{
    m_Node = m_Owner;
    m_Owner->GetScene()->GetRenderScene()->AddChild(this);
}

void TestRenderComponent::InitRenderNode()
{
	VertexList Verts = VertexList();
	Verts = GetSphereVerts(0.5, 32, 64);
	IndexList Indices = IndexList();
	Indices = GetSphereIndices(32, 64);

    M->LoadMesh(Verts, Indices);
}

void TestRenderComponent::OnDeInit()
{

}

void TestRenderComponent::OnEnable()
{

}

void TestRenderComponent::OnDisable()
{

}

void TestRenderComponent::Update(f64 DeltaTime)
{

}

void TestRenderComponent::Render()
{
    M->Render();
}
}