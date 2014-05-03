#ifndef NPCNODE_H
#define NCPNODE_H

#include <Scene/SceneNode.h>
#include <Components/BillboardComponent.h>
#include <soloud.h>
#include <soloud_wav.h>

using namespace BearClaw;
namespace LD29 {
class ObamaNode : public SceneNode
{
private:
	f32 m_Health;
	bool m_Aggresive;
	SoLoud::Soloud* m_Audio;
	SoLoud::Wav m_DeathSound;
	bool m_IsDead;

	f32 m_AttackTimer;
	uid m_PlayerID;

	BillboardComponent* m_BillboardComponent;

protected:

public:
	ObamaNode(BcString Name, Vec3 Pos, f32 Health, uid PlayerID, SoLoud::Soloud* S);
	~ObamaNode();
	void OnInit();
	void OnDeInit();
	void OnEnable();
	void OnDisable();
	void OnUpdate(f64 DeltaTime);

	void UpdatePosition(f64 DeltaTime);
	bool IsDead();

	void OnAction(i32 type);
	void Attack();
	void Explode();

	Mat4 GetTransform();
};
}

#endif