#include <Nodes/ObamaNode.h>
#include <Scene/Scene.h>
#include <Renderer/RenderNode.h>
#include <Utils/Sphere.h>

using namespace BearClaw;
namespace LD29 {
ObamaNode::ObamaNode(BcString Name, Vec3 Pos, f32 Health, uid PlayerID, SoLoud::Soloud * S) : SceneNode(Name) {
	m_Position = Pos;
	m_Health = Health;
	m_Aggresive = false;
	m_AttackTimer = 0;
	m_PlayerID = PlayerID;

	m_IsDead = false;

	m_Audio = S;
	m_DeathSound.load("Data/Sounds/BossDeath.wav");
}

ObamaNode::~ObamaNode() {}

void ObamaNode::OnInit() {
	m_BillboardComponent = new BillboardComponent(m_Name + "_Billboard", "Data/Textures/Obama.png", Vec2(1, 2), true);
	AddComponent(m_BillboardComponent);
}

void ObamaNode::OnDeInit() {}
void ObamaNode::OnEnable() {}
void ObamaNode::OnDisable() {}

void ObamaNode::Attack() {
	StrongNodePtr Player = GetScene()->FindChild(m_PlayerID, true);
	if (SphereOverlapTest(m_Position, 2, Player->GetPosition(), 1)) {
		Player->OnAction(3);
	}
	m_AttackTimer = 2;
}

void ObamaNode::OnUpdate(f64 DeltaTime) {
	m_AttackTimer -= (DeltaTime / 1000);
	m_BillboardComponent->SetTransform(GetTransform());

	if (!m_IsDead) {
		if (m_Aggresive) {
			UpdatePosition(DeltaTime);
			m_BillboardComponent->GetMaterial()->SetUVAdd(Vec2(0.25, 0));
			StrongNodePtr Player = GetScene()->FindChild(m_PlayerID, true);
			if (SphereOverlapTest(m_Position, 2, Player->GetPosition(), 1) && m_AttackTimer <= 0) {
				Attack();
			}
		}
	}

	if (IsDead() && !m_IsDead) {
		m_Audio->play(m_DeathSound);
		m_IsDead = true;
		m_BillboardComponent->SetVisible(false);
		GetScene()->FindChild(m_PlayerID, true)->Action(8);
	}

	if (m_AttackTimer > 1) {
		m_BillboardComponent->GetMaterial()->SetUVAdd(Vec2(0.5, 0));
	}
}

void ObamaNode::UpdatePosition(f64 DeltaTime) {
	StrongNodePtr Player = GetScene()->FindChild(m_PlayerID, true);
	if (Player != nullptr) {
		Vec3 Delta = (Player->GetPosition() - m_Position);
		Delta.y = 0;
		if (Delta.x < 1 && Delta.x > -1) {
			Delta.x = 0;
		}
		if (Delta.z < 1 && Delta.z > -1) {
			Delta.z = 0;
		}
		//Delta.Print();
		if (Delta.x != 0 || Delta.z != 0)
			m_Position += (Delta.Normalize() * (DeltaTime / 800));
	}

	if (m_Position.y <= 1) {
		m_Position.y = 1;
	}
}

bool ObamaNode::IsDead() {
	return m_Health <= 0;
}

Mat4 ObamaNode::GetTransform() {
	Mat4* Ret = new Mat4();
	Ret->Translate(m_Position);
	return *Ret;
}

void ObamaNode::OnAction(i32 type) {
	m_Health -= 10;
	m_Aggresive = true;
}
}