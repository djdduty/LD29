#ifndef TEST_RENDER_COMPONENT_H
#define TEST_RENDER_COMPONENT_H

#include <Scene/Component.h>
#include <Renderer/RenderNode.h>
#include <Resource/Mesh.h>

namespace BearClaw {
class TestRenderComponent : public Component, public RenderNode
{
private:
    f64 Timer;

protected:
    Mesh* M;

public:
    TestRenderComponent(BcString Name);
    ~TestRenderComponent();
    void OnInit();
    void OnDeInit();
    void OnEnable();
    void OnDisable();
    void Update(f64 DeltaTime);

    void InitRenderNode();
    void Render();

    //misc
    void CreateVBO();
    void CreateIBO();
};
}

#endif