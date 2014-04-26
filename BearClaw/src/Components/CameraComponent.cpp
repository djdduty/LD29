#include <Components/CameraComponent.h>
#include <System/Environment.h>
#include <Scene/Scene.h>

namespace BearClaw {
	CameraComponent::CameraComponent(BcString Name, bool IsPerspective) : Component(Name)
{
    CameraInitializer CamInit;
    CamInit.Far = 1000.0f;
    CamInit.Fov = 45.0f;
    CamInit.Near = 0.1f;
    CamInit.Height = WindowHeight;
    CamInit.Width = WindowWidth;
    CamInit.Persp = IsPerspective;
    CamInit.Pos = Vec3(0,0,0);

    m_Camera = new BcCamera(CamInit);
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::SetAsActiveCamera()
{
    m_Owner->GetScene()->GetRenderScene()->SetActiveCamera(m_Camera);
}

void CameraComponent::Update()
{
    m_Camera->Update();
}

void CameraComponent::Rotate(Vec3 &Rot)
{
    m_Camera->Rotate(Rot);//(Rot.x, Rot.y, Rot.z,1.0));
}

void CameraComponent::Translate(Vec3 Trans)
{
    m_Camera->Translate(Trans);
}

Mat4& CameraComponent::GetTransform()
{
    return m_Camera->GetTransform();
}

Mat4& CameraComponent::GetProjection()
{
    return m_Camera->GetProjection();
}

Vec3& CameraComponent::GetPosition()
{
    return m_Camera->GetPosition();
}

Vec3& CameraComponent::GetRotation()
{
    return m_Camera->GetRotation();
}
}