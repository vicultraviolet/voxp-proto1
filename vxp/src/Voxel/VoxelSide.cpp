#include "Pch.hpp"
#include "Voxel/VoxelSide.hpp"

namespace Vxp
{
	[[nodiscard]] static glm::mat4 calculateVoxelSideTransform(VoxelSide side)
	{
		glm::mat4 mat(1.0f);
		mat = glm::translate(mat, Offset(side));
		return Rotate(mat, side);
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

	glm::vec3 Offset(VoxelSide side)
	{
		switch (side)
		{
		case VoxelSide::Top:    return glm::vec3( 0.0f,  0.5f,  0.0f);
		case VoxelSide::Bottom: return glm::vec3( 0.0f, -0.5f,  0.0f);
		case VoxelSide::Right:  return glm::vec3( 0.5f,  0.0f,  0.0f);
		case VoxelSide::Left:   return glm::vec3(-0.5f,  0.0f,  0.0f);
		case VoxelSide::Front:  return glm::vec3( 0.0f,  0.0f,  0.5f);
		case VoxelSide::Back:   return glm::vec3( 0.0f,  0.0f, -0.5f);
		}
		return glm::vec3(0.0f);
	}

	glm::mat4 Rotate(const glm::mat4& mat, VoxelSide side)
	{
		switch (side)
		{
		case VoxelSide::Top:    return glm::rotate(mat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		case VoxelSide::Bottom: return glm::rotate(mat, glm::radians( 90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		case VoxelSide::Right:  return glm::rotate(mat, glm::radians( 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		case VoxelSide::Left:   return glm::rotate(mat, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		case VoxelSide::Front:  return mat;
		case VoxelSide::Back:   return glm::rotate(mat, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		return mat;
	}
} // namespace Vxp
