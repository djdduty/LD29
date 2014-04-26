#include <Renderer/Camera.h>
#include <System/Environment.h>

namespace BearClaw {
BcCamera::BcCamera(CameraInitializer &Settings)
{
    m_Settings = Settings;
}

void BcCamera::Init()
{
    m_Rotation = Vec3();
}

void BcCamera::Translate(Vec3 Trans)
{
    m_Position += Trans.Multiply(GetTransform());
}

void BcCamera::Rotate(Vec3 &Rot)
{
    m_Rotation = m_Rotation + Rot;
    Update();
}

void BcCamera::Update()
{}

Mat4& BcCamera::GetProjection()
{
	if (m_Settings.Persp)
		return PerspectiveProjection(m_Settings.Fov, WindowWidth, WindowHeight, m_Settings.Near, m_Settings.Far);

	return OrthoProjection(0, WindowWidth, WindowHeight, 0, 0, m_Settings.Far);
}

Mat4& BcCamera::GetTransform()
{
    Mat4* Ret = new Mat4();
    Ret->Translate(m_Position);
    Ret->Rotate(m_Rotation);
    return *Ret;
}
}
