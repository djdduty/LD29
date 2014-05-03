#include <Nodes/PlayerNode.h>
#include <System/InputManager.h>
#include <System/Environment.h>
#include <Scene/Scene.h>
#include <sstream>

using namespace BearClaw;
namespace LD29 {
PlayerNode* PointerForGlobals;
void PlayerOnMouseMove(double x, double y) {
	f32 dx = (WindowWidth / 2) - x;
	f32 dy = (WindowHeight / 2) - y;
	PointerForGlobals->UpdateRotation(Vec3(-dy/20, -dx/10, 0));
	InputMgr->SetMousePosition(Vec2(WindowWidth / 2, WindowHeight / 2));
}

PlayerNode::PlayerNode(BcString Name, Vec3 Boundary, SoLoud::Soloud* s) : SceneNode(Name)
{
	PointerForGlobals = this;
	m_BoundaryDistance = Boundary;
	m_Health = 100;
	m_Audio = s;
	m_IsDead = false;
	m_HasBirthCert = false;
	m_HasWon = false;
}
PlayerNode::~PlayerNode() {}

void PlayerNode::OnInit() {
	m_CamComp = new CameraComponent(m_Name + "_CameraComponent", true);
	AddComponent(m_CamComp);
	m_CamComp->SetAsActiveCamera();
	m_FistComp = new FistComponent(m_Name + "_FistComponent", m_Audio);
	AddComponent(m_FistComp);

	FontFile* Font = new FontFile("font2");
	Font->Parse();
	m_HealthLabel = new FontString("Health: 100", Vec2(0, -50), Font, 1.0);

	m_DeathSound.load("Data/Sounds/Die.wav");
}

void PlayerNode::OnDeInit() {
	InputMgr->RemoveMouseMoveCB(PlayerOnMouseMove);
}

void PlayerNode::OnEnable() {
	InputMgr->AddMouseMoveCB(PlayerOnMouseMove);
}

void PlayerNode::OnDisable() {
	InputMgr->RemoveMouseMoveCB(PlayerOnMouseMove);
}

void PlayerNode::OnUpdate(f64 DeltaTime) {
	UpdatePosition(DeltaTime);
	if (m_Rotation.x >= 90) m_Rotation.x = 90;
	if (m_Rotation.x <= -90) m_Rotation.x = -90;

	m_CamComp->GetCamera()->SetPosition(Vec3(-m_Position.x, -m_Position.y, -m_Position.z));
	m_CamComp->GetCamera()->SetRotation(m_Rotation);
	m_HealthLabel->Render();

	if (IsDead() && !m_IsDead) {
		m_Audio->play(m_DeathSound);
		m_IsDead = true;
	}
}

bool PlayerNode::IsDead() {
	return m_Health <= 0;
}

void PlayerNode::UpdatePosition(f64 DeltaTime) {
	Vec3 Delta = Vec3();
	if (InputMgr->GetKey(BC_KEY_W) == BC_PRESSED) {
		Delta.z -= 0.005*DeltaTime;
	}

	if (InputMgr->GetKey(BC_KEY_S) == BC_PRESSED) {
		Delta.z += 0.005*DeltaTime;
	}

	if (InputMgr->GetKey(BC_KEY_A) == BC_PRESSED) {
		Delta.x -= 0.0025*DeltaTime;
	}

	if (InputMgr->GetKey(BC_KEY_D) == BC_PRESSED) {
		Delta.x += 0.0025*DeltaTime;
	}

	m_Position += Delta.Multiply(GetTransform());

	if (m_Position.x >= m_BoundaryDistance.x) m_Position.x = m_BoundaryDistance.x;
	if (m_Position.x <= -m_BoundaryDistance.x) m_Position.x = -m_BoundaryDistance.x;

	if (m_Position.z >= m_BoundaryDistance.z) m_Position.z = m_BoundaryDistance.z;
	if (m_Position.z <= -m_BoundaryDistance.z) m_Position.z = -m_BoundaryDistance.z;
	m_Position.y = 1.5;
}

void PlayerNode::OnAction(i32 type) {
	if (type != 1) {
		if (type == 4) {
			m_HasBirthCert = true;
		} 
		if (type == 8) {
			m_HasWon = true;
		} 
		if (type == 2) {
			m_Health -= 10;
			ostringstream ss;
			ss << m_Health;
			m_HealthLabel->SetContent("Health: " + ss.str());
		}
		if (type == 3) {
			m_Health -= 20;
			ostringstream ss;
			ss << m_Health;
			m_HealthLabel->SetContent("Health: " + ss.str());
		}
	}
}

void PlayerNode::UpdateRotation(Vec3 Delta) {
	m_Rotation.x += Delta.x;
	m_Rotation.y += Delta.y;
}

Mat4 PlayerNode::GetTransform() {
	Mat4* Ret = new Mat4();
	Ret->Translate(m_Position);
	Ret->Rotate(m_Rotation);
	return *Ret;
}
}