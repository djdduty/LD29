#ifndef TEST_RENDER_COMPONENT_H
#define TEST_RENDER_COMPONENT_H

#include <Scene/Component.h>
#include <Renderer/RenderNode.h>
#include <Resource/Mesh.h>

namespace BearClaw {
	class TwoDimRenderComponent : public Component, public RenderNode
	{
	private:
		f64 Timer;

	protected:
		Mesh* m_Mesh;
		string m_TexName;

	public:
		TwoDimRenderComponent(BcString Name, string TexName);
		~TwoDimRenderComponent();
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