#if !defined(VXP_CHUNK_HPP)
#define VXP_CHUNK_HPP

#include "Voxel/Position.hpp"
#include "Voxel/VoxelType.hpp"

namespace Vxp
{
	class Chunk {
	public:
		using iterator = std::array<VoxelTypeID, k_ChunkVolume>::iterator;
		using const_iterator = std::array<VoxelTypeID, k_ChunkVolume>::const_iterator;

		explicit Chunk(ChunkPosition pos);

		[[nodiscard]] inline VoxelTypeID get_voxel(LocalPosition pos) const { return m_Voxels[ChunkIndex(pos)]; }

		[[nodiscard]] inline void set_voxel(LocalPosition pos, VoxelTypeID type_id) { m_Voxels[ChunkIndex(pos)] = type_id; }

		[[nodiscard]] inline VoxelTypeID& operator[](LocalPosition pos) { return m_Voxels[ChunkIndex(pos)]; }
		[[nodiscard]] inline const VoxelTypeID& operator[](LocalPosition pos) const { return m_Voxels[ChunkIndex(pos)]; }

		[[nodiscard]] u16 count(void) const;

		[[nodiscard]] inline constexpr u8 width(void) const { return k_ChunkWidth; }
		[[nodiscard]] inline constexpr u8 height(void) const { return k_ChunkHeight; }
		[[nodiscard]] inline constexpr u8 depth(void) const { return k_ChunkDepth; }

		[[nodiscard]] inline constexpr u16 volume(void) const { return k_ChunkVolume; }

		[[nodiscard]] inline ChunkPosition position(void) const { return m_Position; }

		[[nodiscard]] inline auto& voxels(void) { return m_Voxels; }
		[[nodiscard]] inline const auto& voxels(void) const { return m_Voxels; }

		[[nodiscard]] inline auto begin(void) { return m_Voxels.begin(); }
		[[nodiscard]] inline auto end(void) { return m_Voxels.end(); }

		[[nodiscard]] inline auto begin(void) const { return m_Voxels.begin(); }
		[[nodiscard]] inline auto end(void) const { return m_Voxels.end(); }

		[[nodiscard]] inline auto cbegin(void) const { return m_Voxels.cbegin(); }
		[[nodiscard]] inline auto cend(void) const { return m_Voxels.cend(); }
	private:
		ChunkPosition m_Position;

		std::array<VoxelTypeID, k_ChunkVolume> m_Voxels{};
	};
} // namespace Vxp

#endif // VXP_CHUNK_HPP