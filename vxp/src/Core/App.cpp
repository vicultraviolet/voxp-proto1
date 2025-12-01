#include "Pch.hpp"
#include "App.hpp"

#include <Natrium/Graphics/Device.hpp>

#include "Layers/GameLayer.hpp"

namespace Vxp
{
	App::App(void)
	{
		auto renderer_settings = Na::MakeRef<Na::RendererSettings>();

		renderer_settings->max_frames_in_flight = 2;

		m_Window = Na::MakeRef<Na::Window>(1280, 720, "Voxploration Prototype 1");
		m_Display = Na::HL::Display::Make(m_Window, renderer_settings);

		m_Renderer = Na::Graphics::Renderer::Make(renderer_settings);
		m_Renderer->bind_render_target(m_Display);

		m_LayerManager.attach_layer(Na::MakeRef<GameLayer>(m_Window, m_Display, m_Renderer));
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

			if (!m_Display->acquire_next_image())
				continue;

			m_Renderer->begin_frame();
			m_Renderer->begin_render_pass(glm::vec4(0.15f, 0.1f, 0.35f, 1.0f));

			for (const auto& layer : m_LayerManager)
				layer->draw();

			m_Renderer->end_render_pass();
			m_Renderer->end_frame();

			m_Display->present();
		}
	}
} // namespace Vxp
