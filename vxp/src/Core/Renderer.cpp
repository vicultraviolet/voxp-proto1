#include "Pch.hpp"
#include "Core/Renderer.hpp"

#include <Natrium/Graphics/Shader.hpp>
#include <Natrium/Assets/AssetManager.hpp>

namespace Vxp
{
	struct Vertex2D {
		glm::vec2 position;
		glm::vec2 uv_coord;
	};

	constexpr static std::array<Vertex2D, 4> vertices = {
		Vertex2D{ glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 1.0f) },
		Vertex2D{ glm::vec2( 0.5f, -0.5f), glm::vec2(1.0f, 1.0f) },
		Vertex2D{ glm::vec2( 0.5f,  0.5f), glm::vec2(1.0f, 0.0f) },
		Vertex2D{ glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 0.0f) }
	};

	constexpr static std::array<u32, 6> indices = {
		0, 1, 2,
		2, 3, 0
	};

	const static Na::Graphics::VertexAttributes vertexAttributes = {
		{ Na::Graphics::VertexAttributeType::Vec2 },
		{ Na::Graphics::VertexAttributeType::Vec2 }
	};

	Renderer::Renderer(
		Na::WeakRef<Na::Window> window,
		Na::Ref<const Na::RendererSettings> renderer_settings
	)
	{
		auto asset_manager = Na::AssetManager::Get();

		m_Display = Na::HL::Display::Make(window, renderer_settings);

		m_Renderer = Na::Graphics::Renderer::Make(renderer_settings);
		m_Renderer->bind_render_target(m_Display);

		auto vs = Na::Graphics::Shader::Make(
			"assets/shaders/quad_vertex.glsl",
			Na::Graphics::ShaderStage::Vertex
		).value();

		vs->set_push_constant_size(sizeof(Na::CameraMatrices));

		auto fs = Na::Graphics::Shader::Make(
			"assets/shaders/quad_fragment.glsl",
			Na::Graphics::ShaderStage::Fragment
		).value();

		m_QuadVertexBuffer = Na::Graphics::MakeVertexBuffer(sizeof(Vertex2D) * 4);
		m_QuadVertexBuffer->set_data(vertices.data());

		m_QuadIndexBuffer = Na::Graphics::MakeIndexBuffer(6);
		m_QuadIndexBuffer->set_data(indices.data());

		m_Quads.reallocate(512);
		m_InstanceBuffer = Na::Graphics::MakeUniformBuffer(
			(u64)sizeof(Quad) * 512,
			m_Renderer->settings()->max_frames_in_flight
		);

		m_UniformManager.init_layout(
			Na::HL::UniformSetIndices::k_Global,
			{ 
				Na::Graphics::UniformBinding
				{
					.binding = 0,
					.type = Na::Graphics::UniformType::UniformMultibuffer,
					.shader_stage = Na::Graphics::ShaderStage::Vertex
				}
			}
		);

		auto set_handle = m_UniformManager.create_set(
			Na::HL::UniformSetIndices::k_Global,
			m_Renderer
		);
		m_GlobalUniformSet = m_UniformManager.set(set_handle);

		m_GlobalUniformSet->bind(Na::Graphics::UniformSetBufferBindingInfo{
			.binding = 0,
			.buffer = m_InstanceBuffer,
			.type = Na::Graphics::BufferTypeFlags::UniformBuffer
		});

		m_UniformManager.init_layout(
			Na::HL::UniformSetIndices::k_Material,
			{
				Na::Graphics::UniformBinding
				{
					.binding = 0,
					.type = Na::Graphics::UniformType::Texture,
					.shader_stage = Na::Graphics::ShaderStage::Fragment,

					.count = 8,
					.partially_bound = true,
					.dynamic_count = false
				}
			}
		);

		set_handle = m_UniformManager.create_set(
			Na::HL::UniformSetIndices::k_Material,
			m_Renderer
		);
		m_TextureUniformSet = m_UniformManager.set(set_handle);

		Na::HL::TrianglePipelineCreateInfo pipeline_info
		{
			.render_target = m_Display,
			.shaders = { vs, fs },
			.vertex_attributes = &vertexAttributes,
			.uniform_set_layouts = &m_UniformManager.set_layouts()
		};
		m_Pipeline = Na::HL::Pipeline(pipeline_info);
	}

	void Renderer::destroy(void)
	{
		m_Renderer = nullptr;
		m_Display = nullptr;
	}

	void Renderer::attach_texture(u32 index, const Na::HL::Texture& texture)
	{
		Na::Graphics::UniformSetTextureBindingInfo texture_binding_info;

		texture_binding_info.binding = 0;
		texture_binding_info.array_index = index;

		texture_binding_info.texture_info = texture;

		m_TextureUniformSet->bind(texture_binding_info);
	}

	bool Renderer::begin(void)
	{
		if (!m_Display->acquire_next_image())
			return false;

		m_Renderer->begin_frame();
		m_Renderer->begin_render_pass(glm::vec4(0.15f, 0.1f, 0.35f, 1.0f));

		return true;
	}

	void Renderer::end(void)
	{
		m_Renderer->end_render_pass();
		m_Renderer->end_frame();
	}

	void Renderer::present(void)
	{
		m_Display->present();
	}

	void Renderer::flush_quads(void)
	{
		m_Quads.clear();
	}

	void Renderer::add_quad(Quad quad)
	{
		NA_ASSERT(m_Quads.size() < m_Quads.capacity(), "Maximum number of quads reached!");
		m_Quads.emplace_d(std::move(quad));
	}

	void Renderer::draw_quads(const Na::CameraMatrices& camera)
	{
		m_InstanceBuffer->set_subdata(
			m_Quads.ptr(),
			m_Renderer->current_frame_index()
		);

		m_Renderer->bind_pipeline(m_Pipeline.native());
		m_Renderer->bind_uniform_sets(
			{ m_GlobalUniformSet, m_TextureUniformSet },
			m_Pipeline.native()
		);

		m_Renderer->set_push_constant(
			(u32)sizeof(Na::CameraMatrices),
			Na::Graphics::ShaderStage::Vertex,
			0, // offset
			&camera,
			m_Pipeline.native()
		);

		m_Renderer->bind_vertex_buffer(m_QuadVertexBuffer);
		m_Renderer->bind_index_buffer(m_QuadIndexBuffer);

		m_Renderer->draw_indexed(
			6, // index count
			(u32)m_Quads.size() // instance count
		);
	}
} // namespace Vxp
