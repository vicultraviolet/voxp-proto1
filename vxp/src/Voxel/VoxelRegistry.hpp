#if !defined(VXP_VOXEL_REGISTRY_HPP)
#define VXP_VOXEL_REGISTRY_HPP

#include "Voxel/VoxelType.hpp"

namespace Vxp
{
	class VoxelRegistry {
	public:
		VoxelRegistry(void);
		~VoxelRegistry(void);

		VoxelTypeID register_type(const VoxelType& type);
		VoxelTypeID register_type(VoxelType&& type);

		[[nodiscard]] inline VoxelType& get_type(VoxelTypeID id) { return m_Voxels[(u64)id]; }
		[[nodiscard]] inline const VoxelType& get_type(VoxelTypeID id) const { return m_Voxels[(u64)id]; }

		[[nodiscard]] inline VoxelTypeID get_type_id(std::string_view name) const { return m_NameToID.at(name); }

		[[nodiscard]] static inline Na::View<VoxelRegistry> Get(void) { return VoxelRegistry::s_Registry; }

	private:
		Na::ArrayList<VoxelType> m_Voxels;
		std::unordered_map<std::string_view, VoxelTypeID> m_NameToID;

		static inline Na::View<VoxelRegistry> s_Registry;
	};
} // namespace Vxp

#endif // VXP_VOXEL_REGISTRY_HPP