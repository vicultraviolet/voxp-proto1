#include "Pch.hpp"
#include "Game/Textures.hpp"

#include <Natrium/Assets/AssetManager.hpp>

namespace Vxp
{
	Na::ArrayList<Na::Ref<Na::HL::Texture>> CreateTextures(void)
	{
		auto asset_manager = Na::AssetManager::Get();

		auto renderer_settings = asset_manager->get_by_name<Na::RendererSettings>("renderer_settings");

		auto dirt = asset_manager->create_asset<Na::HostImage>("dirt");
		auto grass_top = asset_manager->create_asset<Na::HostImage>("grass_top");
		auto grass_side = asset_manager->create_asset<Na::HostImage>("grass_side");

		dirt->load("assets/img/dirt.png");
		grass_top->load("assets/img/grass_top.png");
		grass_side->load("assets/img/grass_side.png");

		asset_manager->save_registry();

		Na::ArrayList<Na::Ref<Na::HL::Texture>> textures(1);

		auto texture = asset_manager->create_asset<Na::HL::Texture>(
			"blocks",
			Na::HL::TextureDimensions(16, 16, 3),
			renderer_settings,
			Na::Graphics::SamplerFilter::Nearest
		);

		Na::WeakRef<const Na::HostImage> images[] = {
			dirt, grass_top, grass_side
		};
		texture->set_data(images);

		textures.emplace_back(std::move(texture));

		return textures;
	}
} // namespace Vxp
