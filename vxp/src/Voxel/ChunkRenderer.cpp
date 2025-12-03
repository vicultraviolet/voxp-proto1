#include "Pch.hpp"
#include "Voxel/ChunkRenderer.hpp"

#include "Voxel/VoxelRegistry.hpp"

namespace Vxp
{
	struct SideInfo {
		VoxelSide side;
		i8 dy, dz, dx;
	};

	constexpr static std::array<SideInfo, 6> sideInfos = {
		SideInfo{ .side = VoxelSide::Top,    .dy =  1, .dz =  0, .dx =  0 },
		SideInfo{ .side = VoxelSide::Bottom, .dy = -1, .dz =  0, .dx =  0 },
		SideInfo{ .side = VoxelSide::Front,  .dy =  0, .dz =  1, .dx =  0 },
		SideInfo{ .side = VoxelSide::Back,   .dy =  0, .dz = -1, .dx =  0 },
		SideInfo{ .side = VoxelSide::Right,  .dy =  0, .dz =  0, .dx =  1 },
		SideInfo{ .side = VoxelSide::Left,   .dy =  0, .dz =  0, .dx = -1 }
	};

	ChunkRenderer::ChunkRenderer(Na::View<Renderer> renderer)
	: m_Renderer(renderer)
	{

	}


	void ChunkRenderer::draw_chunk(const Chunk& chunk)
	{
		for (u8 y = 0; y < chunk.height(); y++)
		{
			for (u8 z = 0; z < chunk.depth(); z++)
			{
				for (u8 x = 0; x < chunk.width(); x++)
				{
					VoxelTypeID vxl = chunk.get_voxel({ y, z, x });
					if (vxl == VoxelTypeID::None)
						continue;

					glm::vec3 pos = LocalToVoxelPosition(chunk.position(), LocalPosition{ y, z, x });
					const auto& vxl_type = VoxelRegistry::Get()->get_type(vxl);

					for (const auto& side : sideInfos)
					{
						u8 ny = y + side.dy;
						u8 nz = z + side.dz;
						u8 nx = x + side.dx;

						bool out_of_bounds =
							ny >= chunk.height() ||
								nz >= chunk.depth() ||
									nx >= chunk.width();

						VoxelTypeID neighbor = VoxelTypeID::None;
						if (!out_of_bounds)
							neighbor = chunk.get_voxel({ ny, nz, nx });

						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(pos, side.side, vxl_type);
						}
					}
				}
			}
		}
	}

	/*

	void ChunkRenderer::draw_chunk(const Chunk& chunk)
	{
		for (u8 y = 0; y < chunk.height(); y++)
		{
			for (u8 z = 0; z < chunk.depth(); z++)
			{
				for (u8 x = 0; x < chunk.width(); x++)
				{
					VoxelTypeID voxel = chunk.get_voxel({ y, z, x });

					if (voxel == VoxelTypeID::None)
						continue;

					glm::vec3 pos = LocalToVoxelPosition(chunk.position(), LocalPosition{ y, z, x });

					const auto& voxel_type = VoxelRegistry::Get()->get_type(voxel);

					if (y < 15)
					{
						VoxelTypeID neighbor = chunk.get_voxel({ (u8)(y + 1), z, x });
						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(
								pos,
								VoxelSide::Top,
								voxel_type.texture_at(VoxelSide::Top)
							);
						}
					} else
					{
						this->_add_quad(
							pos,
							VoxelSide::Top,
							voxel_type.texture_at(VoxelSide::Top)
						);
					}

					if (y > 0)
					{
						VoxelTypeID neighbor = chunk.get_voxel({ (u8)(y - 1), z, x });
						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(
								pos,
								VoxelSide::Bottom,
								voxel_type.texture_at(VoxelSide::Bottom)
							);
						}
					} else
					{
						this->_add_quad(
							pos,
							VoxelSide::Bottom,
							voxel_type.texture_at(VoxelSide::Bottom)
						);
					}

					if (z < 15)
					{
						VoxelTypeID neighbor = chunk.get_voxel({ y, (u8)(z + 1), x });
						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(
								pos,
								VoxelSide::Front,
								voxel_type.texture_at(VoxelSide::Front)
							);
						}
					} else
					{
						this->_add_quad(
							pos,
							VoxelSide::Front,
							voxel_type.texture_at(VoxelSide::Front)
						);
					}

					if (z > 0)
					{
						VoxelTypeID neighbor = chunk.get_voxel({ y, (u8)(z - 1), x });
						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(
								pos,
								VoxelSide::Back,
								voxel_type.texture_at(VoxelSide::Back)
							);
						}
					} else
					{
						this->_add_quad(
							pos,
							VoxelSide::Back,
							voxel_type.texture_at(VoxelSide::Back)
						);
					}

					if (x < 15)
					{
						VoxelTypeID neighbor = chunk.get_voxel({ y, z, (u8)(x + 1) });
						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(
								pos,
								VoxelSide::Right,
								voxel_type.texture_at(VoxelSide::Right)
							);
						}
					} else
					{
						this->_add_quad(
							pos,
							VoxelSide::Right,
							voxel_type.texture_at(VoxelSide::Right)
						);
					}

					if (x > 0)
					{
						VoxelTypeID neighbor = chunk.get_voxel({ y, z, (u8)(x - 1) });
						if (neighbor == VoxelTypeID::None)
						{
							this->_add_quad(
								pos,
								VoxelSide::Left,
								voxel_type.texture_at(VoxelSide::Left)
							);
						}
					} else
					{
						this->_add_quad(
							pos,
							VoxelSide::Left,
							voxel_type.texture_at(VoxelSide::Left)
						);
					}
				}
			}
		}
	}

	*/

	void ChunkRenderer::_add_quad(
		const glm::vec3& pos,
		VoxelSide side,
		const VoxelType& vxl_type
	)
	{
		glm::vec3 quad_pos = pos + Offset(side);

		glm::mat4 mat(1.0f);

		mat = glm::translate(mat, quad_pos);
		mat = Rotate(mat, side);

		m_Renderer->add_quad(Quad{
			.model = mat,
			.texture = vxl_type.texture_at(side)
		});
	}
} // namespace Vxp