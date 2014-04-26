#include <System/InputManager.h>

namespace BearClaw {
void InputManager::Reset()
{
    memset(&Keys[0], 0, BC_KEY_COUNT * sizeof(int));
    memset(&MouseButtons[0], 0, MOUSE_BUTTON_COUNT * sizeof(int));
    MousePosition = Vec2(0.0);
    memset(&Events[0], 0, sizeof(Events));

    ShowCursor = true;
}

void InputManager::AddKeyDownCB(KeyCB CB)
{
    m_KeyCBs.push_back(CB);
}

void InputManager::AddMouseMoveCB(MouseMoveCB CB)
{
    m_MouseMoveCBs.push_back(CB);
}

void InputManager::AddMouseButtonCB(MouseButtonCB CB)
{
    m_MouseButtonCBs.push_back(CB);
}

void InputManager::RemoveKeyDownCB(KeyCB CB)
{
    for(i32 i = 0;i < m_KeyCBs.size();i++)
    {
        if(m_KeyCBs[i] == CB)
        {
            m_KeyCBs.erase(m_KeyCBs.begin()+i);
            return;
        }
    }
}

void InputManager::RemoveMouseMoveCB(MouseMoveCB CB)
{
    for(i32 i = 0;i < m_MouseMoveCBs.size();i++)
    {
        if(m_MouseMoveCBs[i] == CB)
        {
            m_MouseMoveCBs.erase(m_MouseMoveCBs.begin()+i);
            return;
        }
    }
}

void InputManager::RemoveMouseButtonCB(MouseButtonCB CB)
{
    for(i32 i = 0;i < m_MouseButtonCBs.size();i++)
    {
        if(m_MouseButtonCBs[i] == CB)
        {
            m_MouseButtonCBs.erase(m_MouseButtonCBs.begin()+i);
            return;
        }
    }
}

void InputManager::OnKeyDown(char Key, Action_Type Action)
{
    for(i32 i = 0; i < m_KeyCBs.size(); i++)
    {
        KeyCB Keycb = m_KeyCBs[i];
        Keycb(Key, Action);
    }
}

void InputManager::OnMouseMove(double x, double y)
{
    for(i32 i = 0; i < m_MouseMoveCBs.size(); i++)
    {
        MouseMoveCB MMCB = m_MouseMoveCBs[i];
        MMCB(x, y);
    }
}

void InputManager::OnMouseButton(Mouse_Button Button, Action_Type Action)
{
    for(i32 i = 0; i < m_MouseButtonCBs.size(); i++)
    {
        MouseButtonCB MBCB = m_MouseButtonCBs[i];
        MBCB(Button, Action);
    }
}
}
