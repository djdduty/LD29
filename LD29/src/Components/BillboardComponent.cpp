#include <BillboardComponent.h>
#include <Resource/Mesh.h>
#include <Scene/Scene.h>

using namespace BearClaw;
namespace LD29 {
BillboardComponent::BillboardComponent(BcString Name, string TexName, Vec2(Size), bool SpriteSheet) : Component(Name), RenderNode(Name + "-RenderNode") {
	m_Transform = Mat4(1.0f);
	m_TexName = TexName;
	m_Size = Size;
	m_SpriteSheet = SpriteSheet;
}

BillboardComponent::~BillboardComponent() {

}

void BillboardComponent::OnInit(){
	m_Node = m_Owner;
	m_Owner->GetScene()->GetRenderScene()->AddChild(this);
}

void BillboardComponent::OnDeInit(){}
void BillboardComponent::OnEnable(){}
void BillboardComponent::OnDisable(){}
void BillboardComponent::Update(f64 DeltaTime){}

void BillboardComponent::InitRenderNode(){
	m_Mesh = new Mesh();
	m_Material->SetDiffuseTex(m_TexName);
	m_Material->SetBillboard(true);
	//pRenderLast = true;

	Vec3 TopRight =		Vec3(m_Size.x / 2,  m_Size.y / 2, 0);
	Vec3 TopLeft =		Vec3(-m_Size.x / 2, m_Size.y / 2, 0);
	Vec3 BottomLeft =	Vec3(-m_Size.x / 2, -m_Size.y / 2, 0);
	Vec3 BottomRight =	Vec3(m_Size.x / 2,  -m_Size.y / 2, 0);

	VertexList Verts = VertexList();
	if (m_SpriteSheet) {
		Verts.push_back(Vertex(Vec3(TopRight), Vec3(0, 0, -1), Vec2(0.25, 0)));
		Verts.push_back(Vertex(Vec3(TopLeft), Vec3(0, 0, -1), Vec2(0, 0)));
		Verts.push_back(Vertex(Vec3(BottomLeft), Vec3(0, 0, -1), Vec2(0, 1)));
		Verts.push_back(Vertex(Vec3(BottomRight), Vec3(0, 0, -1), Vec2(0.25, 1)));
	} else {
		Verts.push_back(Vertex(Vec3(TopRight+Vec3(1,0,0)), Vec3(0, 0, -1), Vec2(1, 0)));
		Verts.push_back(Vertex(Vec3(TopLeft), Vec3(0, 0, -1), Vec2(0, 0)));
		Verts.push_back(Vertex(Vec3(BottomLeft+Vec3(0,-0.4,0)), Vec3(0, 0, -1), Vec2(0, 1)));
		Verts.push_back(Vertex(Vec3(BottomRight+Vec3(1,-0.4,0)), Vec3(0, 0, -1), Vec2(1, 1)));
	}

	IndexList Indices = IndexList();
	Indices.push_back(0);
	Indices.push_back(1);
	Indices.push_back(2);

	Indices.push_back(2);
	Indices.push_back(3);
	Indices.push_back(0);

	m_Mesh->LoadMesh(Verts, Indices);

	m_Material->SetUVAdd(Vec2(0, 0));
}

void BillboardComponent::Render(){
	m_Mesh->Render();
}
}