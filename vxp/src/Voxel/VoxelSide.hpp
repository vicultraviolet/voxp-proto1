#if !defined(VXP_VOXEL_SIDE_HPP)
#define VXP_VOXEL_SIDE_HPP

#include "Core.hpp"

namespace Vxp
{
	enum class VoxelSide : u8 {
		None = 0,

		Front, Back,
		Right, Left,
		Top, Bottom,

		Last = Bottom
	};

	[[nodiscard]] const glm::mat4& GetTransform(VoxelSide side);
} // namespace Vxp

#endif // VXP_VOXEL_SIDE_HPP