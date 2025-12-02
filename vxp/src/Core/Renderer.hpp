#if !defined(VXP_CORE_RENDERER_HPP)
#define VXP_CORE_RENDERER_HPP

#include "Core.hpp"
#include <Natrium/HL/Renderer_HL.hpp>

#include <Natrium/Graphics/Buffer.hpp>
#include <Natrium/HL/Texture_HL.hpp>
#include <Natrium/HL/UniformManager_HL.hpp>
#include <Natrium/HL/Pipeline_HL.hpp>

#include <Natrium/Math/Camera3dData.hpp>

namespace Vxp
{
	union TextureHandle {
		u64 handle;

		struct {
			u32 descriptor_index;
			u32 array_index;
		};

		glm::uvec2 vec;
	};

	struct Quad {
		glm::mat4 model{ 1.0f };
		TextureHandle texture;

		Byte offset[4];
	};

	constexpr u32 k_MaxQuadsPerFlush = 32768;

	class Renderer {
	public:
		Renderer(void) = default;
		Renderer(
			Na::WeakRef<Na::Window> window,
			Na::Ref<const Na::RendererSettings> renderer_settings
		);

		void destroy(void);

		void attach_texture(u32 index, const Na::HL::Texture& texture);

		[[nodiscard]] bool begin(void);
		void end(void);
		void present(void);

		void flush_quads(void);
		void add_quad(Quad quad);
		void draw_quads(const Na::CameraMatrices& camera);

	private:
		Na::Ref<Na::HL::Display> m_Display;
		Na::UniqueRef<Na::Graphics::Renderer> m_Renderer;

		Na::UniqueRef<Na::Graphics::Buffer> m_QuadVertexBuffer, m_QuadIndexBuffer;

		Na::ArrayList<Quad> m_Quads;

		Na::UniqueRef<Na::Graphics::Buffer> m_InstanceBuffer;

		Na::HL::UniformManager m_UniformManager;

		Na::Ref<Na::Graphics::UniformSet> m_GlobalUniformSet;
		Na::Ref<Na::Graphics::UniformSet> m_TextureUniformSet;

		Na::HL::Pipeline m_Pipeline;
	};

} // namespace Vxp

#endif // VXP_CORE_RENDERER_HPP