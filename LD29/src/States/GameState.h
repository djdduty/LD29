#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <System/StateManagement/State.h>
#include <Components/CameraComponent.h>
#include <Scene/Scene.h>

using namespace BearClaw;
namespace LD29 {
class GameState : public State 
{
private:
	Scene* m_Scene;

protected:

public:
	GameState();
	~GameState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);
};
}

#endif