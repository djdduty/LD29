#include <Scene/Component.h>
#include <Scene/SceneNode.h>
#include <System/Environment.h>

namespace BearClaw {
Component::Component(BcString Name)
{
    m_Name  = Name;
    m_Id    = Environ->GetUuid(BC_COMPONENT);

    m_Initialized = false;
    m_Enabled = false;
}

void Component::Init()
{
    if(!m_Initialized)
    {
        m_Initialized = true;
        OnInit();
        Enable();
    }
}

void Component::DeInit()
{
    if(m_Initialized)
    {
        m_Initialized = false;
        Disable();
        OnDeInit();
    }
}

void Component::Enable()
{
    if(!m_Enabled && m_Owner->GetEnabled())
    {
        m_Enabled = true;
        OnEnable();
    }
}

void Component::Disable()
{
    if(m_Enabled)
    {
        m_Enabled = false;
        OnDisable();
    }
}

//Setters
void Component::SetOwner(SceneNode* Node)
{
    m_Owner = Node;
}
//

//Getters
SceneNode* Component::GetOwner()
{
    return m_Owner;
}

bool Component::GetInitialized()
{
    return m_Initialized;
}

bool Component::GetEnabled()
{
    return m_Enabled;
}

BcString Component::GetName()
{
    return m_Name;
}

uid Component::GetUuid()
{
    return m_Id;
}
}
