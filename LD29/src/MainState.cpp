#include <MainState.h>
#include <System/StateManagement/StateManager.h>
#include <Gui/FontFile.h>

using namespace BearClaw;
namespace BcGame {
CameraComponent* CamComp;
TestRenderComponent* tc;

string Content;
void KeyCallback(char button, Action_Type Type)
{
    if(Type == BC_PRESSED)
    {
        if(button == BC_KEY_ESCAPE)
            GameWindow->SetCloseRequested(true);
    }
}

MainState::MainState()
{

}

MainState::~MainState()
{

}

void MainState::Init(StateManager* Manager)
{
    m_Scene = new Scene("TestScene");
    m_Scene->Init();

    BC_LOG("Main state being initialized\n");

    SceneNode* CamNode = new SceneNode("CameraNode");
    m_Scene->AddChild(CamNode);
    m_CamComp = new CameraComponent("Camera1");
    CamNode->AddComponent(m_CamComp);
    m_CamComp->SetAsActiveCamera();
    m_CamComp->Translate(Vec3(0,0,-2));

    SceneNode* RenderNode = new SceneNode("RenderNode");
    m_Scene->AddChild(RenderNode);
    tc = new TestRenderComponent("TriangleComponent");
    tc->GetTransformPtr()->Translate(Vec3(0,0,0));
    tc->GetMaterial()->SetDiffuseTex("Data/Textures/Checker.png");
    tc->GetMaterial()->SetNormalTex("Data/Textures/NormalCement.png");
    RenderNode->AddComponent(tc);

    InputMgr->AddKeyDownCB(KeyCallback);
    RenderSingleton->SetScene(m_Scene);

    CamComp = m_CamComp;
}

void MainState::DeInit()
{

}

void MainState::OnActivate()
{
    BC_LOG("Main state being activated\n");
}

void MainState::OnDeactivate()
{

}

void MainState::Update(f64 DeltaTime)
{
    m_Scene->Update(DeltaTime);
    tc->GetTransformPtr()->Rotate(Vec3(0,0.01*DeltaTime,0));
}
}