#if !defined(VXP_CORE_APP_HPP)
#define VXP_CORE_APP_HPP

#include <Natrium/Core/Window.hpp>
#include <Natrium/HL/Renderer_HL.hpp>

#include <Natrium/Core/DeltaTime.hpp>
#include <Natrium/Layers/LayerManager.hpp>

namespace Vxp
{
	class App {
	public:

		App(void);
		~App(void);

		void run(void);

	private:
		Na::Ref<Na::Window> m_Window;
		Na::Ref<Na::HL::Display> m_Display;

		Na::UniqueRef<Na::Graphics::Renderer> m_Renderer;

		Na::LayerManager m_LayerManager;
	};

} // namespace Vxp

#endif // VXP_CORE_APP_HPP