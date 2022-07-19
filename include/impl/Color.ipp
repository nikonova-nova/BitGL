#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_COLOR_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_COLOR_IPP






#include "Vec.hpp"






namespace BitGL
{
	constexpr auto to_colorref(ColorRGB const &color) -> COLORREF
	{
		return RGB(color[Vec::b], color[Vec::g], color[Vec::r]);
	}
}






#endif
