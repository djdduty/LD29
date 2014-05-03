#include <States/DeathState.h>
#include <Renderer/Renderer.h>
#include <System/Environment.h>
#include <Components/CameraComponent.h>
#include <Components/BillboardComponent.h>
#include <System/StateManagement/StateManager.h>
#include <States/GameState.h>
#include <System/InputManager.h>

using namespace BearClaw;
namespace LD29 {
	DeathState::DeathState(SoLoud::Soloud* S) {
		m_Audio = S;
	}

	DeathState::~DeathState() {}

	void DeathState::Init(StateManager* Manager) {
		m_Manager = Manager;
		FontFile* Font = new FontFile("font2");
		Font->Parse();
		Strings = std::vector<FontString*>();
		FontString* Title = new FontString("You Died!", Vec2((WindowHeight/2)+100, -100), Font, 1);
		FontString* About8 = new FontString("Press Space/Enter to try again.", Vec2((WindowHeight/2)-020, -240), Font, 0.5);
		Strings.push_back(Title);
		Strings.push_back(About8);
	}

	void DeathState::Update(f64 DeltaTime) {
		for (i32 i = 0; i < Strings.size(); i++) {
			Strings[i]->Render();
		}

		if (InputMgr->GetKey(BC_KEY_SPACE) == BC_PRESSED || InputMgr->GetKey(BC_KEY_RETURN) == BC_PRESSED) {
			m_Manager->SetActiveState("Menu");
		}
	}

	void DeathState::DeInit() {}
	void DeathState::OnActivate() {}
	void DeathState::OnDeactivate() {}

}