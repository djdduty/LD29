#include <AboutState.h>
#include <System/InputManager.h>
#include <System/StateManagement/StateManager.h>
#include <Components/TwoDimRenderComponent.h>
#include <Components/CameraComponent.h>
#include <System/Environment.h>
#include <Renderer/Renderer.h>
#include <Scene/Scene.h>

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
	Scene* S = new Scene("TestScene");
	S->Init();

	SceneNode* CamNode = new SceneNode("CameraNode");
	S->AddChild(CamNode);
	CameraComponent* CamComp = new CameraComponent("Camera1", false);
	CamNode->AddComponent(CamComp);
	CamComp->SetAsActiveCamera();
	CamComp->Translate(Vec3(0, 0, -2));

	SceneNode* RenderNode = new SceneNode("RenderNode");
	S->AddChild(RenderNode);
	TwoDimRenderComponent* tc = new TwoDimRenderComponent("aboutImage", "Data/Textures/RainbowTilted.png");
	tc->GetTransformPtr()->Translate(Vec3(800, 250, 0));
	RenderNode->AddComponent(tc);

	RenderSingleton->SetScene(S);

	FontFile* Font = new FontFile("font2");
	Font->Parse();
	Strings = std::vector<FontString*>();
	FontString* Title = new FontString("About", Vec2(50, -200), Font, 1.5);
	FontString* About1 = new FontString("Game made in 48 hours by me(djdduty).", Vec2(50, -300), Font, 0.3);
	FontString* About2 = new FontString("This game is intended to be a satire and does-", Vec2(50, -350), Font, 0.3);
	FontString* About3 = new FontString("not reflect my views in any way. I made this-", Vec2(50, -400), Font, 0.3);
	FontString* About4 = new FontString("entirely in c++ using my engine. for sound I-", Vec2(50, -450), Font, 0.3);
	FontString* About5 = new FontString("added in SoLoud, after getting a backend working-", Vec2(50, -500), Font, 0.3);
	FontString* About6 = new FontString("it was super simple to use, shoutout to Sol_HSA!", Vec2(50, -550), Font, 0.3);
	FontString* About7 = new FontString("Press ESC to go back...", Vec2(50, -620), Font, 0.2);
	Strings.push_back(Title);
	Strings.push_back(About1);
	Strings.push_back(About2);
	Strings.push_back(About3);
	Strings.push_back(About4);
	Strings.push_back(About5);
	Strings.push_back(About6);
	Strings.push_back(About7);
}

void AboutState::DeInit(){
	InputMgr->RemoveKeyDownCB(AboutKeyCallback);
	RenderSingleton->UnsetScene();
}

void AboutState::OnActivate(){

}

void AboutState::OnDeactivate(){
	InputMgr->RemoveKeyDownCB(AboutKeyCallback);
}

void AboutState::Update(f64 DeltaTime){
	for (i32 i = 0; i < Strings.size(); i++) {
		Strings[i]->Render();
	}
}
}