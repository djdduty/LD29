#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include <System/StateManagement/State.h>
#include <soloud_wav.h>
#include <soloud.h>
#include <vector>
#include <Gui/FontString.h>

using namespace BearClaw;
namespace LD29 {
class DeathState : public State
{
private:
	std::vector<FontString*> Strings;
	StateManager* m_Manager;
	SoLoud::Soloud* m_Audio;

protected:

public:
	DeathState(SoLoud::Soloud* S);
	~DeathState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);
};
}

#endif