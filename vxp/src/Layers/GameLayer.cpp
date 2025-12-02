#include "Pch.hpp"
#include "Layers/GameLayer.hpp"

#include <Natrium/Assets/AssetManager.hpp>

#include "Voxel/VoxelSide.hpp"

namespace Vxp
{
	GameLayer::GameLayer(Na::Ref<Na::Window> window, Na::View<Renderer> renderer)
	: Na::Layer(0), m_Window(window), m_Renderer(renderer)
	{
		auto asset_manager = Na::AssetManager::Get();

		auto renderer_settings = asset_manager->get_by_name<Na::RendererSettings>("renderer_settings");

		auto dirt       = asset_manager->create_asset<Na::HostImage>("dirt");
		auto grass_top  = asset_manager->create_asset<Na::HostImage>("grass_top");
		auto grass_side = asset_manager->create_asset<Na::HostImage>("grass_side");

		dirt->load("assets/img/dirt.png");
		grass_top->load("assets/img/grass_top.png");
		grass_side->load("assets/img/grass_side.png");

		m_Blocks = asset_manager->create_asset<Na::HL::Texture>(
			"blocks",
			Na::HL::TextureDimensions(16, 16, 3),
			renderer_settings,
			Na::Graphics::SamplerFilter::Nearest
		);

		Na::WeakRef<const Na::HostImage> images[] = {
			dirt, grass_top, grass_side
		};
		m_Blocks->set_data(images);

		asset_manager->save_registry();

		m_Renderer->attach_texture(0, *m_Blocks);

		m_Camera.set_aspect_ratio((float)m_Window->width() / (float)m_Window->height());
		m_Camera.set_pos(glm::vec3(0.0f, 0.0f, 5.0f));
		m_Camera.set_eye(glm::vec3(0.0f, 0.0f, 0.0f));
		m_Camera.set_clip_planes(0.001f, 1000.0f);
		m_Camera.set_fov(100.0f);
	}

	GameLayer::~GameLayer(void)
	{

	}

	void GameLayer::on_event(Na::Event& e)
	{
		m_Input.on_event(e);
		switch (e.type)
		{
			case Na::EventType::WindowResized:
			{
				m_Camera.set_aspect_ratio(
					(float)e.window_resized.width / (float)e.window_resized.height
				);
				break;
			}
			case Na::EventType::MouseButtonPressed:
			{
				if (e.mouse_button_pressed.button == Na::MouseButtons::k_Left)
				{
					m_Window->capture_mouse();
					m_Camera.on_mouse_capture(glm::vec2(
						m_Input.mouse_x(),
						m_Input.mouse_y()
					));
				}
				break;
			}
			case Na::EventType::KeyPressed:
			{
				switch (e.key_pressed.key)
				{
					case Na::Keys::k_Escape:
					{
						m_Window->release_mouse();

						m_Camera.on_mouse_release();

						break;
					}
				}
				break;
			}
			case Na::EventType::MouseMoved:
			{
				if (m_Window->mouse_captured())
					m_Camera.rotate_with_mouse(glm::vec2(
						e.mouse_moved.x, e.mouse_moved.y
					));

				break;
			}
		}
	}

	void GameLayer::update(double dt)
	{
		if (m_Window->mouse_captured())
		{
			float amount = 5.0f * (float)dt;
			glm::vec3 move(0.0f);

			if (m_Input.key(Na::Keys::k_W))
				move.z = amount;
			if (m_Input.key(Na::Keys::k_S))
				move.z = -amount;
			if (m_Input.key(Na::Keys::k_D))
				move.x = amount;
			if (m_Input.key(Na::Keys::k_A))
				move.x = -amount;

			m_Camera.move(move);
		}

		m_Renderer->flush_quads();

		glm::mat4 model(1.0f);

		m_Renderer->add_quad(Quad{
			.model = model * GetTransform(VoxelSide::Front),
			.texture = TextureHandle{
				.descriptor_index = 0,
				.array_index = 2
			}
		});
		m_Renderer->add_quad(Quad{
			.model = model * GetTransform(VoxelSide::Back),
			.texture = TextureHandle{
				.descriptor_index = 0,
				.array_index = 2
			}
		});
		m_Renderer->add_quad(Quad{
			.model = model * GetTransform(VoxelSide::Right),
			.texture = TextureHandle{
				.descriptor_index = 0,
				.array_index = 2
			}
		});
		m_Renderer->add_quad(Quad{
			.model = model * GetTransform(VoxelSide::Left),
			.texture = TextureHandle{
				.descriptor_index = 0,
				.array_index = 2
			}
		});
		m_Renderer->add_quad(Quad{
			.model = model * GetTransform(VoxelSide::Top),
			.texture = TextureHandle{
				.descriptor_index = 0,
				.array_index = 1
			}
		});
		m_Renderer->add_quad(Quad{
			.model = model * GetTransform(VoxelSide::Bottom),
			.texture = TextureHandle{
				.descriptor_index = 0,
				.array_index = 0
			}
		});
	}

	void GameLayer::draw(void)
	{
		m_Renderer->draw_quads(m_Camera.matrices());
	}
} // namespace Vxp
