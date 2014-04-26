#include <Scene/SceneNode.h>
#include <System/Environment.h>

namespace BearClaw {
SceneNode::SceneNode(BcString Name)
{
    m_Name = Name;
    m_Id = Environ->GetUuid(BC_SCENE_NODE);

    m_Enabled               = false;
    m_Initialized           = false;
    m_IsUpdatingAfterChange = false;
    m_ShouldDie             = false;
    m_ParentHasBeenSet      = false;
}

SceneNode::~SceneNode()
{

}

void SceneNode::OnInit() {}
void SceneNode::Init()
{
    if(!m_Initialized)
    {
        m_Initialized = true;
        OnInit();
    }
}

void SceneNode::OnDeInit() {}
void SceneNode::DeInit()
{
    if(m_Initialized)
    {
        m_Initialized = false;
        OnDeInit();

        while(m_Children.size() > 0)
        {
            RemoveChild(m_Children.begin()->first);
        }

        while(m_Components.size() > 0)
        {
            RemoveComponent(m_Components.begin()->first);
        }
    }
}

StrongNodePtr SceneNode::AddChild(SceneNode* Node)
{
    if(Node)
    {
        BcString Key = Node->GetName();
        StrongNodePtr ChildPtr(Node);
        m_Children.insert(std::make_pair(Key, ChildPtr));
        ChildPtr->SetParent(this);
        ChildPtr->Init();

        if(!m_Enabled)
            ChildPtr->Disable();
        else
            ChildPtr->Enable();

        return FindChild(Key, false);
    }
    else
    {
        return StrongNodePtr();
    }
}

StrongNodePtr SceneNode::FindChild(BcString Name, bool recursive)
{
    for(SceneNodes::iterator it = m_Children.begin(); it != m_Children.end(); it++)
    {
            if(it->first == Name)
                return it->second;
    }

    if(recursive)
    {
        for(SceneNodes::iterator it = m_Children.begin(); it != m_Children.end(); it++)
        {
            if(it->first == Name)
                return it->second;
            else
            {
                const StrongNodePtr& Child = it->second->FindChild(Name, recursive);
                if(Child)
                    return Child;
            }
        }
    }

    return StrongNodePtr();
}

bool SceneNode::HasComponent(BcString name)
{
    return (m_Components.count(name) > 0);
}

void SceneNode::RemoveChild(BcString Name)
{
    if(FindChild(Name, false))
    {
        FindChild(Name, false)->DeInit();
        m_Children.erase(Name);
    }
}

void SceneNode::RemoveComponent(BcString Name)
{
    if(HasComponent(Name))
    {
        m_Components[Name]->DeInit();
        m_Components.erase(Name);
    }
}

BcString SceneNode::GetName()
{
    return m_Name;
}

void SceneNode::SetParent(SceneNode* Parent)
{
    if(Parent)
    {
        if(!Parent->FindChild(m_Name, false))
        {
            if(m_ParentHasBeenSet)
            {
                SceneNodes::iterator it = m_Parent->m_Children.find(m_Name);
                Parent->m_Children.insert(std::make_pair(m_Name, it->second));
                m_Parent->m_Children.erase(it);
                m_Parent = Parent;
            }
            else
                Parent->AddChild(this);

            return;
        }
    }

    m_ParentHasBeenSet = true;
    m_Parent = Parent;
    UpdateAllComponents(0);
}

Scene* SceneNode::GetScene()
{
    return m_Parent->GetScene();
}

void SceneNode::Update(f64 DeltaTime)
{
    if(m_Enabled)
    {
        UpdateAllChildren(DeltaTime);
        UpdateAllComponents(DeltaTime);
    }
}

bool SceneNode::IsScene()
{
    return false;
}

void SceneNode::UpdateAllComponents(f64 DeltaTime)
{
    m_IsUpdatingAfterChange = (DeltaTime == 0);

    for(Components::iterator it = m_Components.begin(); it != m_Components.end(); it++)
    {
        if(it->second->GetEnabled())
            it->second->Update(DeltaTime);
    }

    m_IsUpdatingAfterChange = false;
}

void SceneNode::UpdateAllChildren(f64 DeltaTime)
{
    m_IsUpdatingAfterChange = (DeltaTime == 0);

    for(SceneNodes::iterator it = m_Children.begin(); it != m_Children.end(); it++)
    {
        if(it->second->m_ShouldDie)
        {
            SceneNode* Node = it->second.get();
            it--;
            BcString Name = Node->GetName();
            RemoveChild(Name);
        }
        else
            it->second->Update(DeltaTime);
    }

    m_IsUpdatingAfterChange = false;
}

void SceneNode::Kill()
{
    m_ShouldDie = true;
}

bool SceneNode::GetEnabled()
{
    return m_Enabled;
}

void SceneNode::OnEnable() {}
void SceneNode::Enable()
{
    if(!m_ParentHasBeenSet || m_Parent->GetEnabled())
    {
        m_Enabled = true;

        for(SceneNodes::iterator it = m_Children.begin(); it != m_Children.end(); it++)
            it->second->Enable();

        for(Components::iterator it = m_Components.begin(); it != m_Components.end(); it++)
            it->second->Enable();

        OnEnable();
    }
}


void SceneNode::OnDisable() {}
void SceneNode::Disable()
{
    if(m_Enabled)
    {
        m_Enabled = false;

        for(SceneNodes::iterator it = m_Children.begin(); it != m_Children.end(); it++)
            it->second->Disable();

        for(Components::iterator it = m_Components.begin(); it != m_Components.end(); it++)
            it->second->Disable();

        OnDisable();
    }
}
}
