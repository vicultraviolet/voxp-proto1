#include "Pch.hpp"
#include "Voxel/VoxelType.hpp"

namespace Vxp
{
	bool VoxelType::is_single_texture(void) const
	{
		for (u32 i = 1; i < textures.size(); i++)
			if (textures[i].handle != textures[0].handle)
				return false;

		return true;
	}
} // namespace Vxp
