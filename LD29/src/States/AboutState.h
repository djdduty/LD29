#ifndef ABOUTSTATE_H
#define ABOUTSTATE_H

#include <System/StateManagement/State.h>
#include <Gui/FontFile.h>
#include <Gui/FontString.h>

using namespace BearClaw;
namespace LD29 {
class AboutState : public State
{
private:
	std::vector<FontString*> Strings;

protected:

public:
	AboutState();
	~AboutState();

	void Init(StateManager* Manager);
	void DeInit();
	void OnActivate();
	void OnDeactivate();
	void Update(f64 DeltaTime);
};
}

#endif