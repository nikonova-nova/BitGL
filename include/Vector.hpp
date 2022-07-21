#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_VECTOR_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_VECTOR_HPP






#include <Windows.h>



#include <cstddef>



#include <array>






#define BITGL_VECTOR_DECL_ACCESS(f)    \
constexpr auto f()       -> T       &; \
constexpr auto f() const -> T const &;






namespace BitGL
{
	template<typename T, std::size_t N>
	class Vector
	{
	public:
		BITGL_VECTOR_DECL_ACCESS(x)
		BITGL_VECTOR_DECL_ACCESS(y)
		BITGL_VECTOR_DECL_ACCESS(z)
		BITGL_VECTOR_DECL_ACCESS(w)

		BITGL_VECTOR_DECL_ACCESS(r)
		BITGL_VECTOR_DECL_ACCESS(g)
		BITGL_VECTOR_DECL_ACCESS(b)
		BITGL_VECTOR_DECL_ACCESS(a)

		BITGL_VECTOR_DECL_ACCESS(s)
		BITGL_VECTOR_DECL_ACCESS(t)
		BITGL_VECTOR_DECL_ACCESS(p)
		BITGL_VECTOR_DECL_ACCESS(q)

		BITGL_VECTOR_DECL_ACCESS(width)
		BITGL_VECTOR_DECL_ACCESS(height)
		BITGL_VECTOR_DECL_ACCESS(depth)


	public:
		// Unary self-modifying
		constexpr auto operator++()    -> Vector<T, N> &;
		constexpr auto operator++(int) -> Vector<T, N>;
		constexpr auto operator--()    -> Vector<T, N> &;
		constexpr auto operator--(int) -> Vector<T, N>;



		// Binary self-modifying
		constexpr auto operator+=(T const scalar) -> Vector<T, N> &;
		constexpr auto operator-=(T const scalar) -> Vector<T, N> &;
		constexpr auto operator*=(T const scalar) -> Vector<T, N> &;
		constexpr auto operator/=(T const scalar) -> Vector<T, N> &;

		constexpr auto operator+=(Vector<T, N> const &rhs) -> Vector<T, N> &;
		constexpr auto operator-=(Vector<T, N> const &rhs) -> Vector<T, N> &;
		constexpr auto operator*=(Vector<T, N> const &rhs) -> Vector<T, N> &;
		constexpr auto operator/=(Vector<T, N> const &rhs) -> Vector<T, N> &;



		// Indexing
		constexpr auto operator[](std::size_t const index)       -> T       &;
		constexpr auto operator[](std::size_t const index) const -> T const &;


	public:
		std::array<T, N> m_internal_array;
	};






	// Unary non-self-modifying
	template<typename T, std::size_t N> constexpr auto operator+(Vector<T, N> vector) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator-(Vector<T, N> vector) -> Vector<T, N>;



	// Binary non-self-modifying
	template<typename T, std::size_t N> constexpr auto operator+(Vector<T, N> const vector, T const scalar) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator-(Vector<T, N> const vector, T const scalar) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator*(Vector<T, N> const vector, T const scalar) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator/(Vector<T, N> const vector, T const scalar) -> Vector<T, N>;

	template<typename T, std::size_t N> constexpr auto operator+(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator-(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator*(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator/(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;



	// Comparison
	template<typename T, std::size_t N> constexpr auto operator==(Vector<T, N> const &lhs, Vector<T, N> const &rhs) -> bool;






	template<typename T>
	using Vector2 = Vector<T, 2>;
	template<typename T>
	using Vector3 = Vector<T, 3>;
	template<typename T>
	using Vector4 = Vector<T, 4>;
}






#include "impl/Vector.ipp"






#endif
