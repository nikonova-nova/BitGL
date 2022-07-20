#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_VEC_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_VEC_HPP






#include <Windows.h>



#include <cstddef>



#include <array>






#define BITGL_VEC_DECL_ACCESS(f)       \
constexpr auto f()       -> T       &; \
constexpr auto f() const -> T const &;






namespace BitGL
{
	template<typename T, std::size_t N>
	class Vec;



	template<typename T>
	class Vec<T, 2>
	{
	public:
		BITGL_VEC_DECL_ACCESS(x)
		BITGL_VEC_DECL_ACCESS(y)

		BITGL_VEC_DECL_ACCESS(r)
		BITGL_VEC_DECL_ACCESS(g)

		BITGL_VEC_DECL_ACCESS(s)
		BITGL_VEC_DECL_ACCESS(t)

		BITGL_VEC_DECL_ACCESS(width)
		BITGL_VEC_DECL_ACCESS(height)


	public:
		std::array<T, 2> m_internal_array;
	};
	template<typename T>
	using Vec2 = Vec<T, 2>;



	template<typename T>
	class Vec<T, 3>
	{
	public:
		BITGL_VEC_DECL_ACCESS(x)
		BITGL_VEC_DECL_ACCESS(y)
		BITGL_VEC_DECL_ACCESS(z)

		BITGL_VEC_DECL_ACCESS(r)
		BITGL_VEC_DECL_ACCESS(g)
		BITGL_VEC_DECL_ACCESS(b)

		BITGL_VEC_DECL_ACCESS(s)
		BITGL_VEC_DECL_ACCESS(t)
		BITGL_VEC_DECL_ACCESS(p)

		BITGL_VEC_DECL_ACCESS(width)
		BITGL_VEC_DECL_ACCESS(height)
		BITGL_VEC_DECL_ACCESS(depth)


	public:
		std::array<T, 3> m_internal_array;
	};
	template<typename T>
	using Vec3 = Vec<T, 3>;



	template<typename T>
	class Vec<T, 4>
	{
	public:
		BITGL_VEC_DECL_ACCESS(x)
		BITGL_VEC_DECL_ACCESS(y)
		BITGL_VEC_DECL_ACCESS(z)
		BITGL_VEC_DECL_ACCESS(w)

		BITGL_VEC_DECL_ACCESS(r)
		BITGL_VEC_DECL_ACCESS(g)
		BITGL_VEC_DECL_ACCESS(b)
		BITGL_VEC_DECL_ACCESS(a)

		BITGL_VEC_DECL_ACCESS(s)
		BITGL_VEC_DECL_ACCESS(t)
		BITGL_VEC_DECL_ACCESS(p)
		BITGL_VEC_DECL_ACCESS(q)


	public:
		std::array<T, 4> m_internal_array;
	};
	template<typename T>
	using Vec4 = Vec<T, 4>;
}






#include "impl/Vec.ipp"






#endif
