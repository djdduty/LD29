#ifndef GAMESTARTSTATE_H
#define GAMESTARTSTATE_H

#include <System/StateManagement/State.h>
#include <Components/BillboardComponent.h>
#include <soloud_wav.h>
#include <soloud.h>
#include <vector>
#include <Gui/FontString.h>
#include <Gui/FontFile.h>

using namespace BearClaw;
namespace LD29 {
class GameStartState : public State
{
private:
	std::vector<FontString*> Strings;
	StateManager* m_Manager;
	BillboardComponent* tc;
	f32 m_BunnyTimer;

	SoLoud::Soloud* m_Audio;

protected:

public:
	GameStartState(SoLoud::Soloud* S);
	~GameStartState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);
};
}

#endif