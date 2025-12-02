#include "Pch.hpp"
#include "Layers/GameLayer.hpp"

#include <Natrium/Assets/AssetManager.hpp>

#include "Voxel/VoxelSide.hpp"

#include "Game/Textures.hpp"
#include "Game/RegisterAllVoxels.hpp"

namespace Vxp
{
	static void drawChunk(const Chunk& chunk, Renderer& renderer)
	{
		for (u8 y = 0; y < chunk.height(); y++)
		{
			for (u8 z = 0; z < chunk.depth(); z++)
			{
				for (u8 x = 0; x < chunk.width(); x++)
				{
					VoxelTypeID voxel = chunk[{y, z, x}];

					if (voxel == VoxelTypeID::None)
						continue;

					glm::vec3 pos = LocalToVoxelPosition(chunk.position(), LocalPosition{ y, z, x });

					const auto& voxel_type = VoxelRegistry::Get()->get_type(voxel);

					for (u8 i = 0; i < voxel_type.textures.size(); i++)
					{
						renderer.add_quad(Quad{
							.model =
								glm::translate(glm::mat4(1.0f), pos)
								* GetTransform((VoxelSide)(i + 1)),
							.texture = voxel_type.textures[i]
							});
					}
				}
			}
		}
	}

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

		m_Chunk.set_voxel(LocalPosition{ 0, 0, 0 }, VoxelTypeID::Dirt);
		m_Chunk.set_voxel(LocalPosition{ 1, 0, 0 }, VoxelTypeID::Grass);

		m_Chunk2.voxels().fill(VoxelTypeID::Dirt);
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

		drawChunk(m_Chunk, *m_Renderer);
		drawChunk(m_Chunk2, *m_Renderer);
	}

	void GameLayer::draw(void)
	{
		m_Renderer->draw_quads(m_Camera.matrices());
	}
} // namespace Vxp
