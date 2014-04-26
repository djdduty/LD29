#ifndef MAINSTATE_H
#define MAINSTATE_H

#include <Scene/Scene.h>
#include <Components/CameraComponent.h>
#include <Renderer/Renderer.h>
#include <System/StateManagement/State.h>
#include <Gui/FontString.h>

#include <States/AboutState.h>
#include <States/GameState.h>

using namespace BearClaw;

namespace LD29 {
class MainState : public State
{
private:
	FontString* m_TitleString;
	FontString* m_PlayString;
	FontString* m_QuitString;
	FontString* m_AboutString;

	StateManager* m_Manager;

public:
    MainState();
    ~MainState();

    void Init(StateManager* Manager);
    void DeInit();
    void OnActivate();
    void OnDeactivate();
    void Update(f64 DeltaTime);

	void UpdateFontScale();
};
}

#endif