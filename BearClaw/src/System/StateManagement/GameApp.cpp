#include <System/StateManagement/GameApp.h>
#include <System/StateManagement/StateManager.h>
#include <System/OS/PlatformIncludes.h>
#include <System/Environment.h>

namespace BearClaw {
GameApp::GameApp(State* S)
{
    m_StateManager = new StateManager(S);

    m_bIsCloseRequested = false;
    m_bIsRunning = false;
    m_bIsClosing = false;
}

GameApp::~GameApp()
{
    delete m_StateManager;
}

void GameApp::Start()
{
    f64 OldTime = BCGetTimeInMS();
    f64 DeltaTime = 0.0f;
    
    BC_LOG("Starting main loop...\n");

    m_StateManager->Init(this);
    
    BC_LOG("Done initializing main loop.\n");
    while(!GameWindow->GetCloseRequested() && !m_bIsCloseRequested)
    {
        DeltaTime = BCGetTimeInMS() - OldTime;
        OldTime = BCGetTimeInMS();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Environ->Update(DeltaTime);
        m_StateManager->UpdateState(DeltaTime);
        
        GameWindow->SwapBuffers();
    }

    GameWindow->Destroy();
}
}