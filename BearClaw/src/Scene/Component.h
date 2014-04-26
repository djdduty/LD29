#ifndef BC_COMPONENT_H
#define BC_COMPONENT_H

#include <System/OS/PlatformIncludes.h>
#include <System/Interfaces.h>
#include <System/BcTypes.h>
#include <Utils/BcString.h>
#include <Utils/Math.h>


namespace BearClaw {
class SceneNode;

class Component
{
private:
    bool        m_Initialized;//   = false;
    bool        m_Enabled;//       = false;

protected:
    BcString    m_Name;
    uid         m_Id;
    SceneNode*  m_Owner;

public:
    //Constructor/Destructor
    Component(BcString Name);
    virtual ~Component(){}
    //

    //Misc
    virtual void OnInit(){}
    virtual void OnDeInit(){}
    virtual void OnEnable(){}
    virtual void OnDisable(){}
    virtual void Update(f64 DeltaTime){}
    //

    //Setters
    void SetOwner(SceneNode* Node);
    //

    //Getters
    uid         GetUuid();
    BcString    GetName();
    SceneNode*  GetOwner();
    bool        GetEnabled();
    bool        GetInitialized();
    //

    //Base object functions
    void Init();
    void DeInit();
    void Enable();
    void Disable();
    //
};
}

#endif
