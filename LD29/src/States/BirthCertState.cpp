#include <States/BirthCertState.h>
#include <Renderer/Renderer.h>
#include <System/Environment.h>
#include <Components/CameraComponent.h>
#include <Components/BillboardComponent.h>
#include <System/StateManagement/StateManager.h>
#include <States/GameState.h>
#include <System/InputManager.h>

using namespace BearClaw;
namespace LD29 {
	BirthCertState::BirthCertState(SoLoud::Soloud* S) {
		m_Audio = S;
	}

	BirthCertState::~BirthCertState() {}

	void BirthCertState::Init(StateManager* Manager) {
		m_Manager = Manager;
		Scene* S = new Scene("TestScene");
		S->Init();

		SceneNode* CamNode = new SceneNode("CameraNode");
		S->AddChild(CamNode);
		CameraComponent* CamComp = new CameraComponent("Camera1", true);
		CamNode->AddComponent(CamComp);
		CamComp->SetAsActiveCamera();
		CamComp->Translate(Vec3(0, 0, -1));

		SceneNode* RenderNode = new SceneNode("RenderNode");
		S->AddChild(RenderNode);
		BillboardComponent * tc = new BillboardComponent("BunnyStateImage", "Data/Textures/BirthCertMenu.png", Vec2(1, 1), false);
		RenderNode->AddComponent(tc);

		RenderSingleton->SetScene(S);

		FontFile* Font = new FontFile("font2");
		Font->Parse();
		Strings = std::vector<FontString*>();
		FontString* Title = new FontString("You found Barack Obama's birth certificate!", Vec2(0, -50), Font, 0.6);
		FontString* About8 = new FontString("Press Space/Enter to continue.", Vec2(50, -640), Font, 0.2);
		Strings.push_back(Title);
		Strings.push_back(About8);
	}

	void BirthCertState::Update(f64 DeltaTime) {
		for (i32 i = 0; i < Strings.size(); i++) {
			Strings[i]->Render();
		}

		if (InputMgr->GetKey(BC_KEY_SPACE) == BC_PRESSED || InputMgr->GetKey(BC_KEY_RETURN) == BC_PRESSED) {
			GameState* gs = new GameState(m_Audio, 3);
			m_Manager->ChangeState(gs);
		}
	}

	void BirthCertState::DeInit() {}
	void BirthCertState::OnActivate() {}
	void BirthCertState::OnDeactivate() {}

}