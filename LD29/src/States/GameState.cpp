#include <GameState.h>
#include <System/InputManager.h>
#include <System/StateManagement/StateManager.h>
#include <System/Environment.h>
#include <MainState.h>
#include <SceneLoader.h>

using namespace BearClaw;
namespace LD29 {
StateManager* gManager;
CameraComponent* m_CamComp;
void GameKeyCallback(char button, Action_Type Type)
{
	if (Type == BC_PRESSED)
	{
		switch (button) {
		case BC_KEY_ESCAPE:
			gManager->ChangeState(new MainState());
			break;
		}
	}
}

void GameOnMouseMove(double x, double y) {
	f32 dx = (WindowWidth / 2) - x;
	f32 dy = (WindowHeight / 2) - y;
	m_CamComp->Rotate(Vec3(-dy/10, -dx/10, 0));
	InputMgr->SetMousePosition(Vec2(WindowWidth / 2, WindowHeight / 2));
}

GameState::GameState() {}

GameState::~GameState() {}

void GameState::Init(StateManager* Manager){
	gManager = Manager;
	InputMgr->AddKeyDownCB(GameKeyCallback);

	SceneLoader loader = SceneLoader("Data/Scenes/Level1.txt");
	m_Scene = loader.Parse();
	SceneNode* CamNode = new SceneNode("CameraNode");
	m_Scene->AddChild(CamNode);
	m_CamComp = new CameraComponent("Camera1", true);
	CamNode->AddComponent(m_CamComp);
	m_CamComp->SetAsActiveCamera();
	m_CamComp->Translate(Vec3(0, 0, -2));
	RenderSingleton->SetScene(m_Scene);

	InputMgr->AddMouseMoveCB(GameOnMouseMove);
}

void GameState::DeInit(){
	InputMgr->RemoveKeyDownCB(GameKeyCallback);
	InputMgr->RemoveMouseMoveCB(GameOnMouseMove);
	RenderSingleton->UnsetScene();
}

void GameState::OnActivate(){
	m_Scene->Enable();
}

void GameState::OnDeactivate(){
	InputMgr->RemoveKeyDownCB(GameKeyCallback);
	InputMgr->RemoveMouseMoveCB(GameOnMouseMove);
	m_Scene->Disable();
}

void GameState::Update(f64 DeltaTime){
	m_Scene->Update(DeltaTime);

	if (InputMgr->GetKey(BC_KEY_W) == BC_PRESSED) {
		m_CamComp->Translate(Vec3(0, 0, 0.01*DeltaTime));
	}
	if (InputMgr->GetKey(BC_KEY_S) == BC_PRESSED) {
		m_CamComp->Translate(Vec3(0, 0, -0.01*DeltaTime));
	}
	if (InputMgr->GetKey(BC_KEY_A) == BC_PRESSED) {
		m_CamComp->Translate(Vec3(0.01*DeltaTime, 0, 0));
	}
	if (InputMgr->GetKey(BC_KEY_D) == BC_PRESSED) {
		m_CamComp->Translate(Vec3(-0.01*DeltaTime, 0, 0));
	}
	if (InputMgr->GetKey(BC_KEY_Q) == BC_PRESSED) {
		m_CamComp->Translate(Vec3(0, 0.01*DeltaTime, 0));
	}
	if (InputMgr->GetKey(BC_KEY_E) == BC_PRESSED) {
		m_CamComp->Translate(Vec3(0, -0.01*DeltaTime, 0));
	}
	//Must be a leak in Translate?
}
}