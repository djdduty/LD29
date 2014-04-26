#ifndef CAMERA_H
#define CAMERA_H

#include <Utils/Math.h>

namespace BearClaw {

struct CameraInitializer
{
    f32     Fov;//     =   45.0f;
    f32     Near;//    =   0.1f;
    f32     Far;//     =   1000.0f;
    u32     Width;//   =   WindowWidth;
    u32     Height;//  =   WindowHeight;
    Vec3    Pos;//     =   Vec3(0,0,0);
    bool    Persp;//   =   true;
};

class BcCamera
{
protected:
    CameraInitializer   m_Settings;
    Vec3                m_Position;
    Vec3                m_Rotation;

public:
    BcCamera(CameraInitializer &Settings);
    void Init();
    void Update();
    void Rotate(Vec3 &Rot);
    void Translate(Vec3 Trans);

    Mat4& GetTransform();
    Mat4& GetProjection();
    Vec3& GetPosition()         {   return m_Position;                          }
    Vec3& GetRotation()         {   return m_Rotation;                          }
};
}

#endif
