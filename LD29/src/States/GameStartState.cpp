#include <States/GameStartState.h>
#include <Renderer/Renderer.h>
#include <System/Environment.h>
#include <Components/CameraComponent.h>
#include <System/StateManagement/StateManager.h>
#include <States/GameState.h>
#include <System/InputManager.h>

using namespace BearClaw;
namespace LD29 {
GameStartState::GameStartState(SoLoud::Soloud* S) {
	m_BunnyTimer = 4;
	m_Audio = S;
}

GameStartState::~GameStartState() {}

void GameStartState::Init(StateManager* Manager) {
	m_Manager = Manager;
	Scene* S = new Scene("TestScene");
	S->Init();

	SceneNode* CamNode = new SceneNode("CameraNode");
	S->AddChild(CamNode);
	CameraComponent* CamComp = new CameraComponent("Camera1", true);
	CamNode->AddComponent(CamComp);
	CamComp->SetAsActiveCamera();
	CamComp->Translate(Vec3(0, 0, -2));

	SceneNode* RenderNode = new SceneNode("RenderNode");
	S->AddChild(RenderNode);
	tc = new BillboardComponent("BunnyStateImage", "Data/Textures/Bunny.png", Vec2(1,1), true);
	RenderNode->SetPosition(Vec3(0.8,-0.1,0));
	RenderNode->AddComponent(tc);

	RenderSingleton->SetScene(S);

	FontFile* Font = new FontFile("font2");
	Font->Parse();
	Strings = std::vector<FontString*>();
	FontString* Title = new FontString("You broke the universe!", Vec2(50, -200), Font, 1);
	FontString* About1 = new FontString("In your careless rampage of rage and", Vec2(50, -300), Font, 0.3);
	FontString* About2 = new FontString("sweat, you accidentally rip off the", Vec2(50, -350), Font, 0.3);
	FontString* About3 = new FontString("Do Not Remove tag from the nearby", Vec2(50, -400), Font, 0.3);
	FontString* About4 = new FontString("mattress. Suddenly you are shrinking,", Vec2(50, -450), Font, 0.3);
	FontString* About5 = new FontString("atoms the size of cities are flying by.", Vec2(50, -500), Font, 0.3);
	FontString* About7 = new FontString("You continue to shrink until all goes black...", Vec2(50, -550), Font, 0.3);
	FontString* About8 = new FontString("Press Space/Enter to continue.", Vec2(50, -640), Font, 0.2);
	Strings.push_back(Title);
	Strings.push_back(About1);
	Strings.push_back(About2);
	Strings.push_back(About3);
	Strings.push_back(About4);
	Strings.push_back(About5);
	Strings.push_back(About7);
	Strings.push_back(About8);
}

void GameStartState::Update(f64 DeltaTime) {
	m_BunnyTimer -= (DeltaTime / 1000)*2;
	if (m_BunnyTimer <= 0) {
		m_BunnyTimer = 4;
	}
	if (m_BunnyTimer >= 3) tc->GetMaterial()->SetUVAdd(Vec2(0.0, 0.0));
	if (m_BunnyTimer >= 2 && m_BunnyTimer <= 3) tc->GetMaterial()->SetUVAdd(Vec2(0.25, 0.0));
	if (m_BunnyTimer >= 1 && m_BunnyTimer <= 2) tc->GetMaterial()->SetUVAdd(Vec2(0.50, 0.0));
	if (m_BunnyTimer >= 0 && m_BunnyTimer <= 1) tc->GetMaterial()->SetUVAdd(Vec2(0.75, 0.0));

	for (i32 i = 0; i < Strings.size(); i++) {
		Strings[i]->Render();
	}

	if (InputMgr->GetKey(BC_KEY_SPACE) == BC_PRESSED || InputMgr->GetKey(BC_KEY_RETURN) == BC_PRESSED) {
		GameState* gs = new GameState(m_Audio, 2);
		m_Manager->ChangeState(gs);
	}
}

void GameStartState::DeInit() {}
void GameStartState::OnActivate() {}
void GameStartState::OnDeactivate() {}

}