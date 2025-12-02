#if !defined(VXP_CORE_CONTEXT_HPP)
#define VXP_CORE_CONTEXT_HPP

#include <Natrium/Core/Context.hpp>
#include <Natrium/Graphics/Device.hpp>
#include <Natrium/Assets/AssetManager.hpp>

namespace Vxp
{
	class Context {
	public:
		Context(void);
		~Context(void);
	private:
		Na::Context m_NatriumContext;
		Na::UniqueRef<Na::Graphics::Device> m_Device;

		Na::AssetManager m_AssetManager;
	};
} // namespace Vxp

#endif // VXP_CORE_CONTEXT_HPP