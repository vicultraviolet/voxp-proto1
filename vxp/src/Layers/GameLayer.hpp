#if !defined(VXP_GAME_LAYER_HPP)
#define VXP_GAME_LAYER_HPP

#include <Natrium/Layers/Layer.hpp>

#include <Natrium/Core/Window.hpp>
#include <Natrium/HL/Renderer_HL.hpp>

namespace Vxp
{
	class GameLayer : public Na::Layer
	{
	public:
		GameLayer(
			Na::Ref<Na::Window> window,
			Na::Ref<Na::HL::Display> display,
			Na::View<Na::Graphics::Renderer> renderer
		);
		~GameLayer(void);

		void on_event(Na::Event& e) override;
		void update(double dt) override;
		void draw(void) override;

	private:
		Na::Ref<Na::Window> m_Window;
		Na::Ref<Na::HL::Display> m_Display;

		Na::View<Na::Graphics::Renderer> m_Renderer;


	};
} // namespace Vxp

#endif // VXP_GAME_LAYER_HPP