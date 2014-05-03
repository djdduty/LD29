#include <Nodes/NPCNode.h>
#include <Scene/Scene.h>
#include <Renderer/RenderNode.h>
#include <Utils/Sphere.h>

using namespace BearClaw;
namespace LD29 {
NPCNode::NPCNode(BcString Name, Vec3 Pos, f32 Health, uid PlayerID, SoLoud::Soloud * S) : SceneNode(Name) {
	m_Position = Pos;
	m_Health = Health;
	m_Aggresive = false;
	m_BombTimer = 5;

	m_StartY = Pos.y;
	m_PlayerID = PlayerID;
	m_JumpTimer = 0; 
	m_ExplodeAnimTimer = 0;

	m_IsDead = false;
	m_IsJumping = false;

	m_Audio = S;
	m_ExplodeSound.load("Data/Sounds/Explode.wav");
	m_DeathSound.load("Data/Sounds/Die.wav");
	m_JumpSound.load("Data/Sounds/Walk.wav");
}

NPCNode::~NPCNode() {}

void NPCNode::OnInit() {
	m_BillboardComponent = new BillboardComponent(m_Name + "_Billboard", "Data/Textures/Bunny.png", Vec2(1, 1), true);
	AddComponent(m_BillboardComponent);
}

void NPCNode::OnDeInit() {}
void NPCNode::OnEnable() {}
void NPCNode::OnDisable() {}

void NPCNode::OnUpdate(f64 DeltaTime) {
	m_ExplodeAnimTimer -= DeltaTime / 1000;
	m_JumpTimer -= DeltaTime / 1000;
	m_BillboardComponent->SetTransform(GetTransform());

	if (m_Position.y <= m_StartY) {
		if (m_IsJumping) {
			m_IsJumping = false;
		}
		if (m_Aggresive && !(m_ExplodeAnimTimer > 0))
			m_BillboardComponent->GetMaterial()->SetUVAdd(Vec2(0.25, 0));
	}

	if (!m_IsDead) {
		if (m_Aggresive) {
			UpdatePosition(DeltaTime);
			m_BombTimer -= DeltaTime / 1000;
			if (!m_IsJumping) {
				m_yVelocity = 0.15f;
				m_IsJumping = true;
				//m_JumpTimer = 1;
				m_BillboardComponent->GetMaterial()->SetUVAdd(Vec2(0.5, 0));
			}
		}

		if (m_BombTimer <= 0) {
			Explode();
		}
	} else {
		if (m_ExplodeAnimTimer <= 0)
			m_BillboardComponent->SetVisible(false);
	}

	if (IsDead() && !m_IsDead) {
		if (!(m_ExplodeAnimTimer > 0))
			m_Audio->play(m_DeathSound);
		m_IsDead = true;

		i32 num = rand() % 10+1;
		if (num == 5) {
			GetScene()->FindChild(m_PlayerID)->Action(4);
			BC_LOG("Lottery!");
		}
	}
}

void NPCNode::UpdatePosition(f64 DeltaTime) {
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

	m_yVelocity -= 0.01;
	m_Position.y += m_yVelocity * DeltaTime/15;

	if (m_Position.y <= m_StartY) {
		m_Position.y = m_StartY;
	}
}

void NPCNode::Explode() {
	m_Audio->play(m_ExplodeSound);
	StrongNodePtr Player = GetScene()->FindChild(m_PlayerID, true);
	m_BillboardComponent->GetMaterial()->SetUVAdd(Vec2(0.75, 0));
	if (SphereOverlapTest(GetPosition(), 5, Player->GetPosition(), 1)) {
		Player->Action(2);
	}
	m_ExplodeAnimTimer = 1;
	m_Health = 0;

	//Todo Play sound
}

bool NPCNode::IsDead() {
	return m_Health <= 0;
}

Mat4 NPCNode::GetTransform() {
	Mat4* Ret = new Mat4();
	Ret->Translate(m_Position);
	return *Ret;
}

void NPCNode::OnAction(i32 type) {
	m_Health -= 10;
	m_Aggresive = true;
}
}