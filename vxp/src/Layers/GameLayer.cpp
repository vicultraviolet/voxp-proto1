#include "Pch.hpp"
#include "Layers/GameLayer.hpp"

#include <Natrium/Assets/AssetManager.hpp>

#include "Voxel/VoxelSide.hpp"

#include "Game/Textures.hpp"
#include "Game/RegisterAllVoxels.hpp"

namespace Vxp
{
	GameLayer::GameLayer(Na::Ref<Na::Window> window, Na::View<Renderer> renderer)
	: Na::Layer(0), m_Window(window), m_Renderer(renderer)
	{
		auto asset_manager = Na::AssetManager::Get();

		m_Textures = CreateTextures();

		for (u32 i = 0; const auto& texture : m_Textures)
		{
			m_Renderer->attach_texture(i++, *texture);
		}

		m_Camera.set_aspect_ratio((float)m_Window->width() / (float)m_Window->height());
		m_Camera.set_pos(glm::vec3(0.0f, 0.0f, 5.0f));
		m_Camera.set_eye(glm::vec3(0.0f, 0.0f, 0.0f));
		m_Camera.set_clip_planes(0.001f, 1000.0f);
		m_Camera.set_fov(100.0f);

		RegisterAllVoxels();
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

			if (m_Input.key(Na::Keys::k_1))
				m_CurrentVoxel = VoxelTypeID::Dirt;

			if (m_Input.key(Na::Keys::k_2))
				m_CurrentVoxel = VoxelTypeID::Grass;

			if (m_Input.mouse_button(Na::MouseButtons::k_Right))
			{
				const auto& voxel_type = m_VoxelRegistry.get_type(m_CurrentVoxel);

				if (const auto& interactable = voxel_type.get_component<InteractableComponent>())
				{
					interactable.on_interact();
				}
			}
		}

		m_Renderer->flush_quads();

		const auto& voxel_type = m_VoxelRegistry.get_type(m_CurrentVoxel);

		for (u8 i = 0; i < voxel_type.textures.size(); i++)
		{
			m_Renderer->add_quad(Quad{
				.model = GetTransform((VoxelSide)(i + 1)),
				.texture = voxel_type.textures[i]
			});
		}
	}

	void GameLayer::draw(void)
	{
		m_Renderer->draw_quads(m_Camera.matrices());
	}
} // namespace Vxp
