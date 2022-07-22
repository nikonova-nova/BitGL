#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP






#include <array>






namespace BitGL
{
	template<typename T, std::size_t Rn, std::size_t Cn>
	class Matrix
	{
	public:
		// Binary self-modifying
		constexpr auto operator*=(T const scalar)               -> Matrix<T, Rn, Cn> &;

		constexpr auto operator+=(Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> &;
		constexpr auto operator-=(Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> &;
		constexpr auto operator*=(Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> &;



		constexpr auto operator[](std::size_t n)       -> T       *;
		constexpr auto operator[](std::size_t n) const -> T const *;


	public:
		std::array<T, Rn * Cn> m_internal_array;
	};






	// Binary non-self-modifying
	template<typename T, std::size_t Rn, std::size_t Cn> constexpr auto operator*(Matrix<T, Rn, Cn> matrix, T const scalar)            -> Matrix<T, Rn, Cn>;

	template<typename T, std::size_t Rn, std::size_t Cn> constexpr auto operator+(Matrix<T, Rn, Cn> lhs, Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn>;
	template<typename T, std::size_t Rn, std::size_t Cn> constexpr auto operator-(Matrix<T, Rn, Cn> lhs, Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn>;
	template<typename T, std::size_t Rn, std::size_t Cn> constexpr auto operator*(Matrix<T, Rn, Cn> lhs, Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn>;






	template<typename T>
	using Matrix2x2 = Matrix<T, 2, 2>;
	template<typename T>
	using Matrix3x3 = Matrix<T, 3, 3>;
	template<typename T>
	using Matrix4x4 = Matrix<T, 4, 4>;
}






#include "impl/Matrix.ipp"






#endif
