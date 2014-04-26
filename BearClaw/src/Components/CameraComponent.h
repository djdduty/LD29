#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include <Scene/Component.h>
#include <Renderer/Camera.h>

namespace BearClaw {
class CameraComponent : public Component
{
private:
    BcCamera*   m_Camera;
public:
    //Constructor/Destructor and component functions
    CameraComponent(BcString Name, bool IsPerspective);
    ~CameraComponent();
    void Update();

    //misc
    void SetAsActiveCamera();

    //Camera functions
    void Rotate(Vec3 &Rot);
    void UpdateProjection();
    void Translate(Vec3 Trans);

    Mat4& GetTransform();
    Mat4& GetProjection();
    Vec3& GetPosition();
    Vec3& GetRotation();
};
}

#endif