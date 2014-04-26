#include <AboutState.h>
#include <System/InputManager.h>
#include <System/StateManagement/StateManager.h>
#include <System/Environment.h>

using namespace BearClaw;
namespace LD29 {
StateManager* aManager;
void AboutKeyCallback(char button, Action_Type Type) 
{
	if (Type == BC_PRESSED)
	{
		switch (button) {
			case BC_KEY_ESCAPE:
				aManager->SetActiveState("Menu");
			break;
		}
	}
}

AboutState::AboutState() {}

AboutState::~AboutState() {}

void AboutState::Init(StateManager* Manager){
	aManager = Manager;
	InputMgr->AddKeyDownCB(AboutKeyCallback);
}

void AboutState::DeInit(){
	InputMgr->RemoveKeyDownCB(AboutKeyCallback);
}

void AboutState::OnActivate(){

}

void AboutState::OnDeactivate(){
	InputMgr->RemoveKeyDownCB(AboutKeyCallback);
}

void AboutState::Update(f64 DeltaTime){

}
}