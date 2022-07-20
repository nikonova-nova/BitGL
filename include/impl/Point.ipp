#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_POINT_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_POINT_IPP






#include "Vector.hpp"






namespace BitGL
{
	constexpr auto to_1d_index(Point2D const &position, Vector2<int> const &size) -> std::size_t
	{
		return (size.height() - position.y() - 1) * size.width() + position.x();
	}
}






#endif
