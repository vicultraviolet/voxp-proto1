#include "Pch.hpp"
#include "Game/RegisterAllVoxels.hpp"

#include "Game/Textures.hpp"

namespace Vxp
{
	void RegisterAllVoxels(void)
	{
		auto registry = VoxelRegistry::Get();

		VoxelType type = {
			.name = "Dirt",
			.textures = {
				TextureHandles::Dirt, // front
				TextureHandles::Dirt, // back
				TextureHandles::Dirt, // right
				TextureHandles::Dirt, // left
				TextureHandles::Dirt, // top
				TextureHandles::Dirt  // bottom
			}
		};
		registry->register_type(std::move(type));

		type = VoxelType{
			.name = "Grass Block",
			.textures = {
				TextureHandles::GrassSide, // front
				TextureHandles::GrassSide, // back
				TextureHandles::GrassSide, // right
				TextureHandles::GrassSide, // left
				TextureHandles::GrassTop,  // top
				TextureHandles::Dirt       // bottom
			}
		};

		type.set_component(InteractableComponent{
			.on_interact = [](void)
			{
				g_Logger.printf(Na::Info, "You interacted with a Grass Block voxel!");
			}
		});

		registry->register_type(type);
	}
} // namespace Vxp