#if !defined(VXP_GAME_TEXTURES_HPP)
#define VXP_GAME_TEXTURES_HPP

#include "Core/Renderer.hpp"

namespace Vxp
{
	namespace TextureHandles
	{
		constexpr TextureHandle Dirt{ .descriptor_index = 0, .array_index = 0 };
		constexpr TextureHandle GrassTop{ .descriptor_index = 0, .array_index = 1 };
		constexpr TextureHandle GrassSide{ .descriptor_index = 0, .array_index = 2 };
	} // namespace TextureHandles

	[[nodiscard]] Na::ArrayList<Na::Ref<Na::HL::Texture>> CreateTextures(void);
} // namespace Vxp

#endif // VXP_GAME_TEXTURES_HPP