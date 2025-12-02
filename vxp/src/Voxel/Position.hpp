#if !defined(VXP_VOXEL_POSITION_HPP)
#define VXP_VOXEL_POSITION_HPP

#include "Core.hpp"

namespace Vxp
{
	using VoxelPosition = glm::i64vec3;
	using ChunkPosition = glm::i32vec3;

	struct LocalPosition {
		u8 y : 8 = 0;
		u8 z : 4 = 0;
		u8 x : 4 = 0;

		[[nodiscard]] inline constexpr operator glm::u8vec3(void) const { return glm::u8vec3{ x, y, z }; }
	};

	constexpr u16 k_ChunkWidth  = 16, k_ChunkHeight = 16, k_ChunkDepth  = 16;

	constexpr u16 k_ChunkDepthXWidth = k_ChunkDepth * k_ChunkWidth;
	constexpr u16 k_ChunkVolume = k_ChunkDepthXWidth * k_ChunkHeight;

	constexpr ChunkPosition VoxelToChunkPosition(const VoxelPosition& voxel_pos)
	{
		return ChunkPosition{
			(i32)((float)voxel_pos.x / (float)k_ChunkWidth),
			(i32)((float)voxel_pos.y / (float)k_ChunkHeight),
			(i32)((float)voxel_pos.z / (float)k_ChunkDepth)
		};
	}

	constexpr LocalPosition VoxelToLocalPosition(const VoxelPosition& voxel_pos)
	{
		return LocalPosition{
			(u8)(voxel_pos.y % k_ChunkHeight),
			(u8)(voxel_pos.z % k_ChunkDepth),
			(u8)(voxel_pos.x % k_ChunkWidth)
		};
	}

	constexpr VoxelPosition LocalToVoxelPosition(const ChunkPosition& chunk_pos, LocalPosition local_pos)
	{
		return VoxelPosition{
			(i64)chunk_pos.x * (i64)k_ChunkWidth + (i64)local_pos.x,
			(i64)chunk_pos.y * (i64)k_ChunkHeight + (i64)local_pos.y,
			(i64)chunk_pos.z * (i64)k_ChunkDepth + (i64)local_pos.z
		};
	}

	constexpr u16 ChunkIndex(LocalPosition local_pos)
	{
		return (u16)local_pos.y * k_ChunkDepthXWidth + (u16)local_pos.z * (u16)k_ChunkWidth + (u16)local_pos.x;
	}
} // namespace Vxp

#endif // VXP_VOXEL_POSITION_HPP