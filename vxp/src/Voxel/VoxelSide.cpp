#include "Pch.hpp"
#include "Voxel/VoxelSide.hpp"

namespace Vxp
{
	[[nodiscard]] static glm::mat4 calculateVoxelSideTransform(VoxelSide side)
	{
		glm::mat4 mat(1.0f);
		switch (side)
		{
		case VoxelSide::Top:
			mat = glm::translate(mat, glm::vec3(0.0f, 0.5f, 0.0f));
			mat = glm::rotate(mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case VoxelSide::Bottom:
			mat = glm::translate(mat, glm::vec3(0.0f, -0.5f, 0.0f));
			mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case VoxelSide::Right:
			mat = glm::translate(mat, glm::vec3(0.5f, 0.0f, 0.0f));
			mat = glm::rotate(mat, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case VoxelSide::Left:
			mat = glm::translate(mat, glm::vec3(-0.5f, 0.0f, 0.0f));
			mat = glm::rotate(mat, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case VoxelSide::Front:
			mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, 0.5f));
			break;
		case VoxelSide::Back:
			mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, -0.5f));
			mat = glm::rotate(mat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		}
		return mat;
	}

	static const std::array<glm::mat4, 7> voxelSideTransforms = {
		calculateVoxelSideTransform(VoxelSide::None),
		calculateVoxelSideTransform(VoxelSide::Front),
		calculateVoxelSideTransform(VoxelSide::Back),
		calculateVoxelSideTransform(VoxelSide::Right),
		calculateVoxelSideTransform(VoxelSide::Left),
		calculateVoxelSideTransform(VoxelSide::Top),
		calculateVoxelSideTransform(VoxelSide::Bottom)
	};

	const glm::mat4& GetTransform(VoxelSide side)
	{
		return voxelSideTransforms[(u8)side];
	}
} // namespace Vxp
