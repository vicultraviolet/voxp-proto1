#include "Pch.hpp"

#include <Natrium/Main.hpp>

#include <Natrium/Core/Context.hpp>
#include <Natrium/Graphics/Device.hpp>

#include "Core/App.hpp"

int main(int argc, char* argv[])
{
	Na::ContextInitInfo context_info{};
	Na::Context context(context_info);

	Na::Graphics::DeviceInitInfo device_info
	{
		.backend = Na::Graphics::DeviceBackend::Vulkan,
		.required_extensions = {
			Na::Graphics::DeviceExtension::Swapchain
		}
	};
	auto device = Na::Graphics::Device::Make(device_info);

	Vxp::App app;
	app.run();

	return 0;
}
