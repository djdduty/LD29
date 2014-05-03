#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <Scene/Component.h>
#include <Utils/Math.h>
#include <map>

using namespace std::tr1;

namespace BearClaw {
class Scene;

typedef std::map<BcString, StrongNodePtr>       SceneNodes;
typedef std::map<BcString, StrongComponentPtr>  Components;

class SceneNode
{
private:
    bool        m_Enabled;//               = false;
    bool        m_Initialized;//           = false;
    bool        m_IsUpdatingAfterChange;// = false;
    bool        m_ShouldDie;//             = false;
    bool        m_ParentHasBeenSet;//      = false;

protected:
    uid         m_Id;
    BcString    m_Name;
    bool        IsScene();
    SceneNode*  m_Parent;
	
	Vec3 m_Position;
	Vec3 m_Rotation;

    //Functions
    void UpdateAllComponents(f64 DeltaTime);
    void UpdateAllChildren(f64 DeltaTime);
    //
    
    //Components
    Components m_Components;

    //Children
    SceneNodes m_Children;

public:
    //Constructor/Destructor
    SceneNode(BcString Name);
    virtual ~SceneNode();
    //

    //misc
    void Init();
    void DeInit();
    void Enable();
    void Disable();
    void Kill();

    //Children functions
    StrongNodePtr   AddChild(SceneNode* Node);
	StrongNodePtr   FindChild(BcString Name, bool recursive = true);
	StrongNodePtr   FindChild(uid ID, bool recursive = true);
    void            RemoveChild(BcString Name);
    //

    //Component functions
    bool HasComponent(BcString name);

    template <typename ComponentType>
    shared_ptr<ComponentType> AddComponent(ComponentType* component)
    {
        BcString name = component->GetName();
        if(!HasComponent(name))
        {
            StrongComponentPtr  ptr(component);
            ptr->SetOwner(this);
            ptr->Init();
            std::pair<BcString, StrongComponentPtr> pair(name, ptr);
            m_Components.insert(pair);

            if(!m_Enabled)
                component->Disable();
            else
                component->Enable();

            UpdateAllComponents(0);
        }
        return FindComponent<ComponentType>(name);
    }

    template <typename ComponentType>
    shared_ptr<ComponentType> FindComponent(BcString Name)
    {
        if(!HasComponent(Name))
            return shared_ptr<ComponentType>();

        return dynamic_pointer_cast<ComponentType>(m_Components[Name]);
    }

    void RemoveComponent(BcString Name);
    //

    //Setters
    void SetParent(SceneNode* Parent);
	void SetPosition(Vec3 Pos) { m_Position = Pos; }
    //

    //Getters
    SceneNode* GetParent();
    BcString GetName();
    virtual Scene* GetScene();
    bool GetEnabled();
	Vec3 GetPosition() { return m_Position; }
	Vec3 GetRotation() { return m_Rotation; }
	uid GetID() { return m_Id; }
    //

    //virtual misc
    virtual void OnInit();
    virtual void OnDeInit();
    virtual void OnEnable();
    virtual void OnDisable();
	virtual void OnUpdate(f64 DeltaTime);
    virtual void Update(f64 DeltaTime);
    //

	//hacky hacky
	void Action(i32 type);
	virtual void OnAction(i32 type);
};
}

#endif
