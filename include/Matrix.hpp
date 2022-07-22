#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP






#include <array>






namespace BitGL
{
	template<typename T, std::size_t N>
	class Matrix
	{
	public:
		// Binary self-modifying
		constexpr auto operator*=(T const scalar)               -> Matrix<T, N> &;

		constexpr auto operator+=(Matrix<T, N> const &rhs) -> Matrix<T, N> &;
		constexpr auto operator-=(Matrix<T, N> const &rhs) -> Matrix<T, N> &;
		constexpr auto operator*=(Matrix<T, N> const &rhs) -> Matrix<T, N> &;



		constexpr auto operator[](std::size_t n)       -> T       *;
		constexpr auto operator[](std::size_t n) const -> T const *;


	public:
		std::array<T, N * N> m_internal_array;
	};






	// Binary non-self-modifying
	template<typename T, std::size_t N> constexpr auto operator*(Matrix<T, N> matrix, T const scalar)       -> Matrix<T, N>;

	template<typename T, std::size_t N> constexpr auto operator+(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N>;
	template<typename T, std::size_t N> constexpr auto operator-(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N>;
	template<typename T, std::size_t N> constexpr auto operator*(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N>;






	template<typename T>
	using Matrix2 = Matrix<T, 2>;
	template<typename T>
	using Matrix3 = Matrix<T, 3>;
	template<typename T>
	using Matrix4 = Matrix<T, 4>;
}






#include "impl/Matrix.ipp"






#endif
