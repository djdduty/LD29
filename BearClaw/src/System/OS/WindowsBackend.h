#ifdef BC_USE_WINDOWS_BACKEND

#ifndef WINDOWS_BACKEND_H
#define WINDOWS_BACKEND_H

#include <System/OS/Window.h>
#include <Windows.h>

namespace BearClaw {
class BackendWindow
{
private:
    HDC                 m_HDC;
    HWND                m_Window;
    WindowInitializer   m_Initializer;

public:
    BackendWindow(WindowInitializer &Initializer);
    ~BackendWindow();
    void Create();
    void MakeCurrent();
    bool GetCloseRequested();
    Vec2 GetWindowSize();
    void SwapBuffers();
    void PollEvents();
    void Destroy();

    HWND GetWindow() {return m_Window;}
};

struct InputImpl
{
    bool    HideCursor;
    u16     KeyToBC[256];
};
}

#endif

#endif