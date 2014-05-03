#ifndef NPCNODE_H
#define NCPNODE_H

#include <Scene/SceneNode.h>
#include <Components/BillboardComponent.h>
#include <soloud.h>
#include <soloud_wav.h>

using namespace BearClaw;
namespace LD29 {
class NPCNode : public SceneNode
{
private:
	f32 m_Reach;
	f32 m_Health;
	bool m_Aggresive;
	f32 m_BombTimer;
	SoLoud::Soloud* m_Audio;
	SoLoud::Wav m_ExplodeSound;
	SoLoud::Wav m_DeathSound;
	SoLoud::Wav m_JumpSound;
	bool m_IsDead;

	bool m_IsJumping;
	f32 m_yVelocity;
	f32 m_StartY;
	f32 m_JumpTimer;

	f32 m_ExplodeAnimTimer;

	uid m_PlayerID;

	BillboardComponent* m_BillboardComponent;

protected:

public:
	NPCNode(BcString Name, Vec3 Pos, f32 Health, uid PlayerID, SoLoud::Soloud* S);
	~NPCNode();
	void OnInit();
	void OnDeInit();
	void OnEnable();
	void OnDisable();
	void OnUpdate(f64 DeltaTime);

	void UpdatePosition(f64 DeltaTime);
	bool IsDead();

	void OnAction(i32 type);
	void Explode();

	Mat4 GetTransform();
};
}

#endif