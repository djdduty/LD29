#include <Components/PlaneComponent.h>
#include <Scene/Scene.h>
#include <System/Environment.h>
#include <Resource/Shapes.h>

using namespace BearClaw;
namespace LD29 {
	PlaneComponent::PlaneComponent(BcString Name, VertexList Verts) : Component(Name), RenderNode(Name + "-RenderNode")
	{
		m_Verts = Verts;
		m_Transform = Mat4();
		m_Mesh = new Mesh();
	}

	PlaneComponent::~PlaneComponent()
	{

	}

	void PlaneComponent::OnInit()
	{
		m_Node = m_Owner;
		m_Owner->GetScene()->GetRenderScene()->AddChild(this);
	}

	void PlaneComponent::InitRenderNode()
	{
		IndexList Indices = IndexList();
		Indices.push_back(0);
		Indices.push_back(1);
		Indices.push_back(2);

		Indices.push_back(2);
		Indices.push_back(3);
		Indices.push_back(0);

		m_Mesh->LoadMesh(m_Verts, Indices);
	}

	void PlaneComponent::OnDeInit()
	{

	}

	void PlaneComponent::OnEnable()
	{

	}

	void PlaneComponent::OnDisable()
	{

	}

	void PlaneComponent::Update(f64 DeltaTime)
	{

	}

	void PlaneComponent::Render()
	{
		m_Mesh->Render();
	}
}