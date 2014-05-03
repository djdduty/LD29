#ifndef WINSTATE_H
#define WINSTATE_H

#include <System/StateManagement/State.h>
#include <soloud_wav.h>
#include <soloud.h>
#include <vector>
#include <Gui/FontString.h>

using namespace BearClaw;
namespace LD29 {
class WinState : public State
{
private:
	std::vector<FontString*> Strings;
	StateManager* m_Manager;

protected:

public:
	WinState(SoLoud::Soloud* S);
	~WinState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);
};
}

#endif