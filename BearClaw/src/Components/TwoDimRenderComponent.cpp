#include <Components/TwoDimRenderComponent.h>
#include <Scene/Scene.h>
#include <System/Environment.h>
#include <Resource/Shapes.h>

namespace BearClaw {
	TwoDimRenderComponent::TwoDimRenderComponent(BcString Name, string TexName) : Component(Name), RenderNode(Name + "-RenderNode")
	{
		Timer = 0.0f;
		m_Transform = Mat4();
		m_Mesh = new Mesh();
		m_TexName = TexName;
	}

	TwoDimRenderComponent::~TwoDimRenderComponent()
	{

	}

	void TwoDimRenderComponent::OnInit()
	{
		m_Node = m_Owner;
		m_Owner->GetScene()->GetRenderScene()->AddChild(this);
	}

	void TwoDimRenderComponent::InitRenderNode()
	{
		m_Material->SetDiffuseTex(m_TexName);
		i32 w = m_Material->GetDiffuseTexturePtr()->GetWidth();
		i32 h = m_Material->GetDiffuseTexturePtr()->GetHeight();
		Vec3 TopRight = Vec3(w/2, h/2, 0);
		Vec3 TopLeft = Vec3(-w/2, h/2, 0);
		Vec3 BottomLeft = Vec3(-w/2, -h/2, 0);
		Vec3 BottomRight = Vec3(w/2, -h/2, 0);

		VertexList Verts = VertexList();
		Verts.push_back(Vertex(Vec3(TopRight), Vec3(0, 0, -1), Vec2(1, 1)));
		Verts.push_back(Vertex(Vec3(TopLeft), Vec3(0, 0, -1), Vec2(0, 1)));
		Verts.push_back(Vertex(Vec3(BottomLeft), Vec3(0, 0, -1), Vec2(0, 0)));
		Verts.push_back(Vertex(Vec3(BottomRight), Vec3(0, 0, -1), Vec2(1, 0)));

		IndexList Indices = IndexList();
		Indices.push_back(0);
		Indices.push_back(1);
		Indices.push_back(2);

		Indices.push_back(2);
		Indices.push_back(3);
		Indices.push_back(0);

		m_Mesh->LoadMesh(Verts, Indices);
	}

	void TwoDimRenderComponent::OnDeInit()
	{

	}

	void TwoDimRenderComponent::OnEnable()
	{

	}

	void TwoDimRenderComponent::OnDisable()
	{

	}

	void TwoDimRenderComponent::Update(f64 DeltaTime)
	{

	}

	void TwoDimRenderComponent::Render()
	{
		m_Mesh->Render();
	}
}