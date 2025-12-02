#include "Pch.hpp"
#include "Voxel/Chunk.hpp"

namespace Vxp
{
	Chunk::Chunk(ChunkPosition pos)
	: m_Position(std::move(pos))
	{

	}

	u16 Chunk::count(void) const
	{
		u16 count = 0;

		for (VoxelTypeID voxel : m_Voxels)
			if (voxel != VoxelTypeID::None)
				count++;

		return count;
	}
} // namespace Vxp
