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
	// FWD
	template<typename T, std::size_t N>
	class Matrix;






	template<typename T, std::size_t N>
	class Vector
	{
	public:
		constexpr auto normalize() -> void;

		constexpr auto scale(Vector<T, 3> const &factors)              -> void;
		auto rotate(T const angle, Vector<T, 3> const &axes)           -> void;
		constexpr auto translate(Vector<T, 3> const &offsets)          -> void;

		constexpr auto length() const -> T;


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
		template<typename Tb>
		static constexpr auto convert(Vector<T, N> const &from) -> Vector<Tb, N>;

		template<std::size_t Nb>
		static constexpr auto truncate(Vector<T, N> const &from) -> Vector<T, Nb>;

		template<std::size_t Nb>
		static constexpr auto extend(Vector<T, N> const &from, T const fill) -> Vector<T, Nb>;


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

		constexpr auto operator*=(Matrix<T, N> const &matrix) -> Vector<T, N> &;
		template<std::size_t Nb>
		constexpr auto operator*=(Matrix<T, Nb> const &matrix) -> Vector<T, N> &;



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
	template<typename T, std::size_t N> constexpr auto operator+(Vector<T, N> vector, T const scalar) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator-(Vector<T, N> vector, T const scalar) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator*(Vector<T, N> vector, T const scalar) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator/(Vector<T, N> vector, T const scalar) -> Vector<T, N>;

	template<typename T, std::size_t N> constexpr auto operator+(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator-(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator*(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;
	template<typename T, std::size_t N> constexpr auto operator/(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N>;

	template<typename T, std::size_t N> constexpr auto operator*(Vector<T, N> vector, Matrix<T, N> const &matrix) -> Vector<T, N>;



	// Comparison
	template<typename T, std::size_t N> constexpr auto operator==(Vector<T, N> const &lhs, Vector<T, N> const &rhs) -> bool;






	template<typename T>
	using Vector2   = Vector<T, 2>;
	using BVector2  = Vector2<bool>;
	using IVector2  = Vector2<int>;
	using FVector2  = Vector2<float>;
	using DVector2  = Vector2<double>;
	using LDVector2 = Vector2<long double>;

	template<typename T>
	using Vector3   = Vector<T, 3>;
	using BVector3  = Vector3<bool>;
	using IVector3  = Vector3<int>;
	using FVector3  = Vector3<float>;
	using DVector3  = Vector3<double>;
	using LDVector3 = Vector3<long double>;

	template<typename T>
	using Vector4   = Vector<T, 4>;
	using BVector4  = Vector4<bool>;
	using IVector4  = Vector4<int>;
	using FVector4  = Vector4<float>;
	using DVector4  = Vector4<double>;
	using LDVector4 = Vector4<long double>;






	template<typename T, std::size_t N>
	constexpr auto dot(Vector<T, N> const &a, Vector<T, N> const &b) -> T;
	template<typename T>
	constexpr auto cross(Vector3<T> const &a, Vector3<T> const &b) -> Vector3<T>;
}






#include "impl/Vector.ipp"






#endif
