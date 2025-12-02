#include "Pch.hpp"
#include "Voxel/VoxelRegistry.hpp"

namespace Vxp
{
	VoxelRegistry::VoxelRegistry(void)
	{
		VoxelRegistry::s_Registry = this;

		m_Voxels.emplace_back(VoxelType{});
	}

	VoxelRegistry::~VoxelRegistry(void)
	{
		if (VoxelRegistry::s_Registry == this)
			VoxelRegistry::s_Registry = nullptr;
	}

	VoxelTypeID VoxelRegistry::register_type(const VoxelType& type)
	{
		auto type_id = (VoxelTypeID)m_Voxels.size();

		m_NameToID.try_emplace(type.name, type_id);
		m_Voxels.emplace(type);

		return type_id;
	}

	VoxelTypeID VoxelRegistry::register_type(VoxelType&& type)
	{
		auto type_id = (VoxelTypeID)m_Voxels.size();

		m_NameToID.try_emplace(type.name, type_id);
		m_Voxels.emplace(std::move(type));

		return type_id;
	}
} // namespace Vxp
