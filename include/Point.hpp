#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_POINT_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_POINT_HPP






#include "Vector.hpp"






namespace BitGL
{
	using Point2D = Vector2<int>;






	constexpr auto to_1d_index(Point2D const &position, Vector2<int> const &size) -> std::size_t;
}






#include "impl/Point.ipp"






#endif
