#include "Pch.hpp"
#include "App.hpp"

#include <Natrium/Graphics/Device.hpp>

#include "Layers/GameLayer.hpp"

namespace Vxp
{
	App::App(void)
	{
		auto asset_manager = Na::AssetManager::Get();

		auto renderer_settings = asset_manager->get_by_name<Na::RendererSettings>("renderer_settings");

		m_Window = Na::MakeRef<Na::Window>(1280, 720, "Voxploration Prototype 1");
		m_Renderer = Renderer(m_Window, renderer_settings);

		m_LayerManager.attach_layer(Na::MakeRef<GameLayer>(m_Window, &m_Renderer));
	}

	App::~App(void)
	{
		m_LayerManager.detach_all();

		Na::Graphics::Device::Get()->wait_all();
	}

	void App::run(void)
	{
		Na::DeltaTime dt;
		while (true)
		{
			for (Na::Event& e : Na::PollEvents())
			{
				if (e.type == Na::EventType::WindowClosed)
					return;

				for (const auto& layer : m_LayerManager)
					layer->on_event(e);
			}

			if (!m_Window->focused())
				std::this_thread::sleep_for(33ms);

			dt.calculate();

			for (const auto& layer : m_LayerManager)
				layer->update(dt);

			if (m_Window->minimized())
				continue;

			if (!m_Renderer.begin())
				continue;

			for (const auto& layer : m_LayerManager)
				layer->draw();

			m_Renderer.end();
			m_Renderer.present();
		}
	}
} // namespace Vxp
