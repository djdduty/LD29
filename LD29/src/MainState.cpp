#include <MainState.h>
#include <System/StateManagement/StateManager.h>
#include <Gui/FontFile.h>
#include <soloud.h>
#include <soloud_wav.h>

#include <States/WinState.h>

using namespace BearClaw;
namespace LD29 {
int SelectedIndex;
MainState* ptrToThis;
SoLoud::Soloud gSoloud;
SoLoud::Wav gWave;
SoLoud::Wav gMus;
f32 songCounter;

void MenuKeyCallback(char button, Action_Type Type) //I hate this being global... but I am bad at callbacks
{
	if (Type == BC_PRESSED)
	{
		switch (button) {
			case BC_KEY_ESCAPE:
				GameWindow->SetCloseRequested(true);
			break;
			case BC_KEY_S:
				SelectedIndex += 1;
				gSoloud.play(gWave);
				if (SelectedIndex == -1) SelectedIndex = 2;
				if (SelectedIndex == 3) SelectedIndex = 0;
				ptrToThis->UpdateFontScale();
				//BC_LOG("Stuff");
			break;
			case BC_KEY_W:
				SelectedIndex -= 1;
				gSoloud.play(gWave);
				if (SelectedIndex == -1) SelectedIndex = 2;
				if (SelectedIndex == 3) SelectedIndex = 0;
				ptrToThis->UpdateFontScale();
				//BC_LOG("Stuff");
			break;
		}
	}
}

MainState::MainState()
{
	ptrToThis = this;
}

MainState::~MainState()
{}

void MainState::Init(StateManager* Manager)
{
	m_Manager = Manager;
	SelectedIndex = 0;
	InputMgr->AddKeyDownCB(MenuKeyCallback);
	InputMgr->HideCursor(true);

	FontFile* Font = new FontFile("font2");
	Font->Parse();
	m_TitleString = new FontString("FISTS OF TRUTH!", Vec2(50, -200), Font, 1.5);
	m_PlayString = new FontString("Play", Vec2(50, -400), Font, 0.6);
	m_AboutString = new FontString("About", Vec2(50, -460), Font, 0.4);
	m_QuitString = new FontString("Exit", Vec2(50, -520), Font, 0.4);
	m_ControlsString = new FontString("Menu: W/S to change selection, Space/Enter to confirm selection.", Vec2(50, -620), Font, 0.2);
	m_ControlsString2 = new FontString("Ingame: WASD to move, Left click to punch.", Vec2(50, -650), Font, 0.2);

	SoLoud::sdl_init(&gSoloud);
	gWave.load("Data/Sounds/MenuSwitch.wav");
	gMus.load("Data/Sounds/music1.wav");

	f32 v = gSoloud.getGlobalVolume();
	gSoloud.setGlobalVolume(v*0.5f);
	songCounter = 65;
	gSoloud.play(gMus);
}

void MainState::DeInit()
{
	InputMgr->RemoveKeyDownCB(MenuKeyCallback);
}

void MainState::OnActivate()
{
	InputMgr->AddKeyDownCB(MenuKeyCallback);
}

void MainState::OnDeactivate()
{
	InputMgr->RemoveKeyDownCB(MenuKeyCallback);
}

void MainState::UpdateFontScale() {
	m_PlayString->SetScale(0.4);
	m_AboutString->SetScale(0.4);
	m_QuitString->SetScale(0.4);

	if (SelectedIndex == 0) m_PlayString->SetScale(0.6);
	if (SelectedIndex == 1) m_AboutString->SetScale(0.6);
	if (SelectedIndex == 2) m_QuitString->SetScale(0.6);
}

void MainState::Update(f64 DeltaTime)
{
	songCounter -= DeltaTime / 1000;
	if (songCounter <= 0) {
		gSoloud.play(gMus);
		songCounter = 65;
	}

	if (InputMgr->GetKey(BC_KEY_RETURN) == BC_PRESSED || InputMgr->GetKey(BC_KEY_SPACE) == BC_PRESSED) {
		if (SelectedIndex == 0) { m_Manager->ChangeState(new GameState(&gSoloud,1), "Menu"); return; }
		if (SelectedIndex == 1) { m_Manager->ChangeState(new AboutState(), "Menu"); return; }
		if (SelectedIndex == 2) GameWindow->SetCloseRequested(true);
	}

	//have to render here as the renderer doesn't support these right now and there is no component for it
	m_TitleString->Render();
	m_PlayString->Render();
	m_AboutString->Render();
	m_QuitString->Render();
	m_ControlsString->Render();
	m_ControlsString2->Render();
}
}