#if !defined(VXP_VOXEL_CHUNK_RENDERER_HPP)
#define VXP_VOXEL_CHUNK_RENDERER_HPP

#include "Voxel/Chunk.hpp"
#include "Core/Renderer.hpp"

namespace Vxp
{
	class ChunkRenderer {
	public:
		ChunkRenderer(Na::View<Renderer> renderer);

		void draw_chunk(const Chunk& chunk);

		[[nodiscard]] inline Na::View<Renderer> renderer(void) const { return m_Renderer; }

	private:
		void _add_quad(
			const glm::vec3& pos,
			VoxelSide side,
			const VoxelType& vxl_type
		);
	private:
		Na::View<Renderer> m_Renderer;
	};
} // namespace Vxp

#endif // VXP_VOXEL_CHUNK_RENDERER_HPP