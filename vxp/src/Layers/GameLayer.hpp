#if !defined(VXP_GAME_LAYER_HPP)
#define VXP_GAME_LAYER_HPP

#include "Core.hpp"

#include <Natrium/Layers/Layer.hpp>
#include <Natrium/Core/Input.hpp>

#include <Natrium/Core/Window.hpp>
#include "Core/Renderer.hpp"

#include <Natrium/HL/Texture_HL.hpp>

namespace Vxp
{
	class GameLayer : public Na::Layer
	{
	public:
		GameLayer(Na::Ref<Na::Window> window, Na::View<Renderer> renderer);
		~GameLayer(void);

		void on_event(Na::Event& e) override;
		void update(double dt) override;
		void draw(void) override;

	private:
		Na::Ref<Na::Window> m_Window;
		Na::View<Renderer> m_Renderer;

		Na::Input m_Input;

		Na::Camera3dData m_Camera;

		Na::Ref<Na::HL::Texture> m_Blocks;
	};
} // namespace Vxp

#endif // VXP_GAME_LAYER_HPP