#include <Components/FistComponent.h>
#include <Scene/Scene.h>
#include <System/InputManager.h>
#include <Nodes/NPCNode.h>
#include <Utils/Sphere.h>

using namespace BearClaw;
namespace LD29 {
FistComponent* FistPtr;
void FistMouseDownCB(Mouse_Button Button, Action_Type Action) {
	if (Button == MOUSE_BUTTON_1 && Action == BC_PRESSED) {
		FistPtr->Punch();
	}
	//BC_LOG("Click :3");
}

FistComponent::FistComponent(BcString Name, SoLoud::Soloud* S) : Component(Name), RenderNode(Name + "-RenderNode")
{
	m_Transform = Mat4();
	m_Mesh = new Mesh();
	pRenderLast = true;
	m_PunchTimer = 0;

	m_Audio = S;
	m_PunchSound.load("Data/Sounds/Punch.wav");
}

FistComponent::~FistComponent() {}

void FistComponent::OnInit() {
	FistPtr = this;
	m_Node = m_Owner;
	m_Owner->GetScene()->GetRenderScene()->AddChild(this);
	InputMgr->AddMouseButtonCB(FistMouseDownCB);
}

void FistComponent::InitRenderNode() {
	m_Material->SetDiffuseTex("Data/Textures/FIST.png");
	m_Material->UseFontShader(true);//This is really just an overall 2D shader...
	m_Material->UpdateShader();
	Vec3 TopRight = Vec3(0.8, 0.2, 0);
	Vec3 TopLeft = Vec3(-0.2, 0.2, 0);
	Vec3 BottomLeft = Vec3(-0.2, -1, 0);
	Vec3 BottomRight = Vec3(0.8, -1, 0);

	VertexList Verts = VertexList();
	Verts.push_back(Vertex(Vec3(TopRight), Vec3(0, 0, -1), Vec2(1, 0)));
	Verts.push_back(Vertex(Vec3(TopLeft), Vec3(0, 0, -1), Vec2(0.5, 0)));
	Verts.push_back(Vertex(Vec3(BottomLeft), Vec3(0, 0, -1), Vec2(0.5, 1)));
	Verts.push_back(Vertex(Vec3(BottomRight), Vec3(0, 0, -1), Vec2(1, 1)));

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

void FistComponent::OnDeInit() {
	InputMgr->RemoveMouseButtonCB(FistMouseDownCB);
}

void FistComponent::OnEnable() {}
void FistComponent::OnDisable() {
	InputMgr->RemoveMouseButtonCB(FistMouseDownCB);
}

void FistComponent::Update(f64 DeltaTime) {
	m_PunchTimer -= DeltaTime / 1000;
	if (m_PunchTimer < 0.2)
		m_Material->SetUVAdd(Vec2(0, 0));
}

void FistComponent::Punch() {
	if (m_PunchTimer <= 0) {
		m_Material->SetUVAdd(Vec2(-0.5, 0));
		m_PunchTimer = 0.5;
		m_Audio->play(m_PunchSound);
		BC_LOG("FALCON PUNCH!\n");

		// subtract health from all AINodes in the proximity (reach on PlayerNode)
		SceneNodes Nodes = m_Owner->GetScene()->GetChildren();
		for (SceneNodes::iterator it = Nodes.begin(); it != Nodes.end(); it++) {
			if (SphereOverlapTest(m_Owner->GetPosition(), 2, it->second->GetPosition(), 1)) {
				it->second->Action(1);
			}
		}

	}
}

void FistComponent::Render() {
	m_Mesh->Render();
}
}