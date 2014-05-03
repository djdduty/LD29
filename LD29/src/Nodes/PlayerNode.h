#ifndef PLAYERNODE_H
#define PLAYERNODE_H

#include <Scene/SceneNode.h>
#include <Utils/Math/Vec3.h>
#include <Utils/Math/Mat4.h>
#include <Components/CameraComponent.h>
#include <Components/FistComponent.h>
#include <Gui/FontString.h>
#include <soloud.h>
#include <soloud_wav.h>


//I don't want to hear shit about how bad this class is. I made my scene graph and I know how a node/component system is supposed to work, 
//but I am going to disobeye all that and use it like a normal entity system for this game because I am low on time and this is the faster than making a bunch of components.

using namespace BearClaw;
namespace LD29 {
class PlayerNode : public SceneNode
{
private:
	CameraComponent* m_CamComp;
	Vec3 m_BoundaryDistance;
	FistComponent* m_FistComp;
	f32 m_Health;
	SoLoud::Soloud* m_Audio;
	SoLoud::Wav m_DeathSound;
	bool m_HasBirthCert;
	bool m_IsDead;
	bool m_HasWon;

	FontString* m_HealthLabel;
protected:

public:
	PlayerNode(BcString Name, Vec3 BoundaryDistance, SoLoud::Soloud* s);
	~PlayerNode();
	void OnInit();
	void OnDeInit();
	void OnEnable();
	void OnDisable();
	void OnUpdate(f64 DeltaTime);

	void UpdatePosition(f64 DeltaTime);
	void UpdateRotation(Vec3 Delta);
	bool IsDead();
	bool GetHasBirthCert() { return m_HasBirthCert; }
	bool GetHasWon() { return m_HasWon; }

	void OnAction(i32 type);

	Mat4 GetTransform();
};
}

#endif