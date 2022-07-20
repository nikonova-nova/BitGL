#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_POINT_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_POINT_IPP






#include "Vec.hpp"






namespace BitGL
{
	constexpr auto to_1d_index(Point2D const &position, Vec2<int> const &size) -> std::size_t
	{
		return (size[Vec::height] - position[Vec::y] - 1) * size[Vec::width] + position[Vec::x];
	}
}






#endif
