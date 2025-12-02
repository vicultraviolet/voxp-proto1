#if !defined(VXP_VOXEL_COMPONENTS_HPP)
#define VXP_VOXEL_COMPONENTS_HPP

namespace Vxp
{
	struct InteractableComponent {
		std::function<void()> on_interact;

		[[nodiscard]] inline operator bool (void) const { return on_interact != nullptr; }
	};

	using VoxelComponents = std::tuple<
		InteractableComponent
	>;

	template<typename T, typename t_Tuple>
	struct tuple_contains;

	template<typename T, typename... Ts>
	struct tuple_contains<T, std::tuple<Ts...>> : std::disjunction<std::is_same<T, Ts>...> {};

	template<typename T, typename Tuple>
	inline constexpr bool tuple_contains_v = tuple_contains<T, Tuple>::value;
} // namespace Vxp

#endif // VXP_VOXEL_COMPONENTS_HPP