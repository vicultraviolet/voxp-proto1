#if !defined(VXP_CORE_APP_HPP)
#define VXP_CORE_APP_HPP

#include "Core.hpp"

#include <Natrium/Assets/AssetManager.hpp>

#include <Natrium/Core/Window.hpp>

#include <Natrium/Core/DeltaTime.hpp>
#include <Natrium/Layers/LayerManager.hpp>

#include "Core/Renderer.hpp"

namespace Vxp
{
	class App {
	public:

		App(void);
		~App(void);

		void run(void);

	private:
		Na::Ref<Na::Window> m_Window;
		Renderer m_Renderer;

		Na::LayerManager m_LayerManager;
	};

} // namespace Vxp

#endif // VXP_CORE_APP_HPP