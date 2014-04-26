#include <iostream>
#include <stdio.h>

#include <System/StateManagement/StateManager.h>
#include <System/StateManagement/GameApp.h>
#include <System/StateManagement/State.h>
#include <System/Environment.h>
#include <MainState.h>

using namespace BearClaw;
using namespace LD29;

int main()
{
    WindowInitializer WinInit;
    WinInit.Width           =   1280;
    WinInit.Height          =   720;
    WinInit.rgbaBits[0]     =   8;
    WinInit.rgbaBits[1]     =   8;
    WinInit.rgbaBits[2]     =   8;
    WinInit.rgbaBits[3]     =   0;
    WinInit.DepthBits       =   0;
    WinInit.StencilBits     =   0;
    WinInit.SamplesCount    =   0;
    WinInit.FullScreen      =   false;
    WinInit.Resizable       =   true;
    WinInit.MajorVersion    =   3;
    WinInit.MinorVersion    =   0;
    WinInit.Title           =   "LD29 - FISTS OF TRUTH";

    Environ->Init(WinInit);
    GameApp* Game = new GameApp(new MainState());
    Game->Start();
}
