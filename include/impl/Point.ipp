#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_POINT_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_POINT_IPP






#include "Vec.hpp"






namespace BitGL
{
	constexpr auto to_1d_index(Vec2<int> const &position, int const width) -> std::size_t
	{
		return position[Vec::y] * width + position[Vec::x];
	}
}






#endif
