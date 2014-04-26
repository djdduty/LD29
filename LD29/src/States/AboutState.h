#ifndef ABOUTSTATE_H
#define ABOUTSTATE_H

#include <System/StateManagement/State.h>

using namespace BearClaw;
namespace LD29 {
class AboutState : public State
{
private:

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