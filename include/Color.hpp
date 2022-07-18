#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_COLOR_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_COLOR_HPP






#include "Vec.hpp"






namespace BitGL
{
	constexpr auto to_colorref(Vec3<std::uint8_t> const &color) -> COLORREF;
}






#include "impl/Color.ipp"






#endif
