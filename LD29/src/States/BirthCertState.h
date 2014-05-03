#ifndef BIRTHSTATE_H
#define BIRTHSTATE_H

#include <System/StateManagement/State.h>
#include <soloud_wav.h>
#include <soloud.h>
#include <vector>
#include <Gui/FontFile.h>
#include <Gui/FontString.h>

using namespace BearClaw;
namespace LD29 {
class BirthCertState : public State
{
private:
	std::vector<FontString*> Strings;
	StateManager* m_Manager;
	SoLoud::Soloud* m_Audio;

protected:

public:
	BirthCertState(SoLoud::Soloud* S);
	~BirthCertState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);
};
}

#endif