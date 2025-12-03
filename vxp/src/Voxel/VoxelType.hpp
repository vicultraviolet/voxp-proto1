#if !defined(VXP_VOXEL_TYPE_HPP)
#define VXP_VOXEL_TYPE_HPP

#include "Voxel/VoxelSide.hpp"
#include "Voxel/VoxelTypeID.hpp"
#include "Voxel/VoxelComponents.hpp"
#include "Core/Renderer.hpp"

namespace Vxp
{
	struct VoxelType {
		std::string_view name = "None";

		bool block_entity = false;

		std::array<TextureHandle, 6> textures{};

		VoxelComponents components;

		[[nodiscard]] inline TextureHandle texture_at(VoxelSide side) const { return textures[(u64)side - 1]; }

		template<typename T>
		void set_component(const T& component)
		{
			std::get<T>(components) = component;
		}

		template<typename T>
		void set_component(T&& component)
		{
			std::get<T>(components) = std::move(component);
		}

		template<typename T>
		[[nodiscard]] T& get_component(void)
		{
			return std::get<T>(components);
		}

		template<typename T>
		[[nodiscard]] const T& get_component(void) const
		{
			return std::get<T>(components);
		}

		[[nodiscard]] bool is_single_texture(void) const;
	};
} // namespace Vxp

#endif // VXP_VOXEL_TYPE_HPP