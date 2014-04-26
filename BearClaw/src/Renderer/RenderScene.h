#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include <Renderer/RenderNode.h>
#include <System/Interfaces.h>
#include <Renderer/Camera.h>
#include <map>

namespace BearClaw {

typedef std::map<BcString, StrongRenderNodePtr> RenderNodes;

class Renderer;

class RenderScene
{
public:
    friend class Renderer;

private:
    RenderNodes m_Children;
    BcCamera*   m_ActiveCamera;
    bool        m_Enabled;

public:
    RenderScene();
    ~RenderScene();

    StrongRenderNodePtr AddChild(RenderNode* Node);
    void RemoveChild(BcString Name);

    void SetActiveCamera(BcCamera* Cam);
    BcCamera* GetActiveCamera();

    void Init();

    void Enable();
    void Disable();
    bool IsEnabled();
};
}

#endif