#include <States/WinState.h>
#include <Renderer/Renderer.h>
#include <System/Environment.h>
#include <Components/CameraComponent.h>
#include <Components/BillboardComponent.h>
#include <System/StateManagement/StateManager.h>
#include <States/GameState.h>
#include <System/InputManager.h>

using namespace BearClaw;
namespace LD29 {
	WinState::WinState(SoLoud::Soloud* S) {
	}

	WinState::~WinState() {}

	void WinState::Init(StateManager* Manager) {
		m_Manager = Manager;
		FontFile* Font = new FontFile("font2");
		Font->Parse();
		Strings = std::vector<FontString*>();
		FontString* Title = new FontString("You Win!", Vec2((WindowHeight / 2) + 100, -100), Font, 1);
		FontString* About8 = new FontString("Press ESC to quit.", Vec2((WindowHeight / 2) + 100, -240), Font, 0.5);
		Strings.push_back(Title);
		Strings.push_back(About8);
	}

	void WinState::Update(f64 DeltaTime) {
		for (i32 i = 0; i < Strings.size(); i++) {
			Strings[i]->Render();
		}

		if (InputMgr->GetKey(BC_KEY_ESCAPE) == BC_PRESSED) {
			GameWindow->SetCloseRequested(true);
		}
	}

	void WinState::DeInit() {}
	void WinState::OnActivate() {}
	void WinState::OnDeactivate() {}

}