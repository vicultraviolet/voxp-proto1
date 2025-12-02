#include "Pch.hpp"
#include "Core/Context.hpp"

namespace Vxp
{
	Context::Context(void)
	: m_NatriumContext(Na::ContextInitInfo{
	
	  }),
	  m_Device(Na::Graphics::Device::Make(Na::Graphics::DeviceInitInfo{
		  .backend = Na::Graphics::DeviceBackend::Vulkan,
		  .required_extensions = {
			  Na::Graphics::DeviceExtension::Swapchain,
			  Na::Graphics::DeviceExtension::UniformIndexing
		  },
		  .uniform_indexing_info = Na::Graphics::UniformIndexingInfo{
			  .array_types = {
				  Na::Graphics::UniformType::Texture
			  },
			  .binding_partially_bound = true,
			  .runtime_array = true
		  }
	  })),
	  m_AssetManager(Na::AssetManagerCreateInfo{
		  .engine_assets_dir = "assets/engine",
		  .shader_output_dir = "bin/shaders/",
		  .asset_registry_path = "assets/asset_registry.json"
	  })
	{
		m_AssetManager.bind();

		auto renderer_settings
			= m_AssetManager.create_asset
				<Na::RendererSettings>("renderer_settings");

		renderer_settings->load("renderer_settings.json");

		renderer_settings->set_max_anisotropy(m_Device->limits()->max_anisotropy());

		renderer_settings->save("renderer_settings.json");

		m_AssetManager.save_registry();
	}

	Context::~Context(void)
	{
		m_AssetManager.save_registry();

		m_Device->wait_all();
	}
} // namespace Vxp
