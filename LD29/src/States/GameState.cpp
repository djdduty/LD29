#include <GameState.h>
#include <System/InputManager.h>
#include <System/StateManagement/StateManager.h>
#include <Nodes/NPCNode.h>
#include <System/Environment.h>
#include <MainState.h>
#include <SceneLoader.h>
#include <stdlib.h>

#include <Nodes/ObamaNode.h>
#include <States/GameStartState.h>
#include <States/BirthCertState.h>
#include <States/DeathState.h>
#include <States/WinState.h>

using namespace BearClaw;
namespace LD29 {
StateManager* gManager;
SoLoud::Soloud* gAudio;
void GameKeyCallback(char button, Action_Type Type)
{
	if (button == BC_KEY_ESCAPE && Type == BC_PRESSED)
	{
		//GameWindow->SetCloseRequested(true);
		gManager->SetActiveState("Menu");
	}
}

void GameMouseDownCB(Mouse_Button Button, Action_Type Action) {
	if (Button == MOUSE_BUTTON_1 && Action == BC_PRESSED) {
		gManager->ChangeState(new GameStartState(gAudio));
	}
	//BC_LOG("Click :3");
}

GameState::GameState(SoLoud::Soloud* S, i32 Level) {
	m_SoLoud = S;
	m_Level = Level;
	m_LevelLoaded = false;
}

GameState::~GameState() {}

void GameState::Init(StateManager* Manager){
	m_Manager = Manager;
	gManager = Manager;
	gAudio = m_SoLoud; FontFile* Font = new FontFile("font2");
	Font->Parse();
	InputMgr->AddKeyDownCB(GameKeyCallback);
	if (m_Level == 1) {
		LoadLevelOne();
		m_HintString = new FontString("You ary angry from lack of sleep, swing your fist a little to let out some frustration!", Vec2(0, -100), Font, 0.3);
		InputMgr->AddMouseButtonCB(GameMouseDownCB);
	}
	if (m_Level == 2) {
		LoadLevelTwo();
		m_HintString = new FontString("You get the feeling your fist can uncover great evil, and that these bunnies might have something you need!", Vec2(0, -100), Font, 0.2);
	}
	if (m_Level == 3) {
		LoadLevelThree();
		m_HintString = new FontString("Now that I think about it, Obama does seem suspicious...", Vec2(0, -100), Font, 0.3);
	}
}

void GameState::UpdateLevelOne(f64 DeltaTime) {
	m_HintString->Render();
}

void GameState::UpdateLevelTwo(f64 DeltaTime) {
	if (Player->IsDead()) {
		m_Manager->ChangeState(new BirthCertState(m_SoLoud));
		return;
	} 
	m_HintString->Render();
	if (Player->GetHasBirthCert()) {
		m_Manager->ChangeState(new BirthCertState(m_SoLoud));
	}
}

void GameState::UpdateLevelThree(f64 DeltaTime) {
	if (Player->IsDead()) {
		m_Manager->ChangeState(new DeathState(m_SoLoud));
		return;
	}
	m_HintString->Render();
	if (Player->GetHasWon()) {
		m_Manager->ChangeState(new WinState(m_SoLoud));
	}
}

void GameState::LoadLevelOne() {
	if (!m_LevelLoaded) {
		SceneLoader loader = SceneLoader("Data/Scenes/Level1.txt");
		m_Scene = loader.Parse();
		m_Scene->Init();
		m_Scene->Enable();
		Player = new PlayerNode("Player", Vec3(2.6, 2.6, 2.6), m_SoLoud);
		m_Scene->AddChild(Player);
		RenderSingleton->SetScene(m_Scene);
		m_LevelLoaded = true;
	}
}

void GameState::Update(f64 DeltaTime){
	m_Scene->Update(DeltaTime);

	if (m_Level == 1) UpdateLevelOne(DeltaTime);
	if (m_Level == 2) UpdateLevelTwo(DeltaTime);
	if (m_Level == 3) UpdateLevelThree(DeltaTime);
}

void GameState::LoadLevelTwo() {
	if (!m_LevelLoaded) {
		RenderSingleton->UnsetScene();
		SceneLoader loader = SceneLoader("Data/Scenes/Level2.txt");
		m_Scene = loader.Parse();
		m_Scene->Init();
		m_Scene->Enable();
		Player = new PlayerNode("Player", Vec3(29.6, 29.6, 29.6), m_SoLoud);
		m_Scene->AddChild(Player);
		RenderSingleton->SetScene(m_Scene);

		for (int i = 0; i < 100; i++) {
			i32 x = rand() % 56 + 1;
			i32 z = rand() % 56 + 1;
			x -= 28;
			z -= 28;
			NPCNode* npc = new NPCNode("Npc" + i, Vec3(x, 0.5, z), 50, Player->GetID(), m_SoLoud);
			m_Scene->AddChild(npc);
		}
		m_LevelLoaded = true;
	}
}

void GameState::LoadLevelThree() {
	if (!m_LevelLoaded) {
		RenderSingleton->UnsetScene();
		SceneLoader loader = SceneLoader("Data/Scenes/Level3.txt");
		m_Scene = loader.Parse();
		m_Scene->Init();
		m_Scene->Enable();
		Player = new PlayerNode("Player", Vec3(14.6, 14.6, 14.6), m_SoLoud);
		m_Scene->AddChild(Player);
		ObamaNode* Obama = new ObamaNode("Obama", Vec3(0, 1, -10), 100, Player->GetID(), m_SoLoud);
		m_Scene->AddChild(Obama);
		RenderSingleton->SetScene(m_Scene);
		m_LevelLoaded = true;
	}
}

void GameState::DeInit(){
	InputMgr->RemoveKeyDownCB(GameKeyCallback);
	m_Scene->Disable();
	RenderSingleton->UnsetScene();
	if (m_Level == 1)
		InputMgr->RemoveMouseButtonCB(GameMouseDownCB);
}

void GameState::OnActivate(){
	m_Scene->Enable();
}

void GameState::OnDeactivate(){
	InputMgr->RemoveKeyDownCB(GameKeyCallback);
}

void GameState::DeleteScene() {
	RenderSingleton->UnsetScene();
	delete(m_Scene);
}
}