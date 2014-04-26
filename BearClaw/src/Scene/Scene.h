#ifndef SCENE_H
#define SCENE_H

#include <Scene/SceneNode.h>
#include <Renderer/RenderScene.h>

namespace BearClaw {
class Scene : public SceneNode
{
private:

protected:
    RenderScene* m_RenderScene;

public:
    Scene(BcString Name);
    ~Scene();
    void OnInit();
    void OnDeInit();
    void OnEnable();
    void OnDisable();
    //TODO PhysicsWorld* GetPhysicsWorld();

    bool IsScene()
    {
        return true;
    }

    RenderScene* GetRenderScene()
    {
        return m_RenderScene;
    }

    Scene* GetScene()
    {
        return this;
    } 
};
}

#endif
