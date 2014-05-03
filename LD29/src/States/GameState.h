#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <System/StateManagement/State.h>
#include <Nodes/PlayerNode.h>
#include <Scene/Scene.h>
#include <soloud.h>
#include <soloud_wav.h>

using namespace BearClaw;
namespace LD29 {
class GameState : public State 
{
private:
	Scene* m_Scene;
	PlayerNode* Player;
	SoLoud::Soloud* m_SoLoud;
	i32 m_Level;
	bool m_LevelLoaded;
	StateManager* m_Manager;
	FontString* m_HintString;

protected:

public:
	GameState(SoLoud::Soloud* S, i32 Level);
	~GameState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);

	void LoadLevelOne();
	void UpdateLevelOne(f64 DeltaTime);
	
	void LoadLevelTwo();
	void UpdateLevelTwo(f64 DeltaTime);
	
	void LoadLevelThree();
	void UpdateLevelThree(f64 DeltaTime);

	void DeleteScene();
};
}

#endif