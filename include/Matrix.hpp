#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP






#include <array>






namespace BitGL
{
	// FWD
	template<typename T, std::size_t N>
	class Vector;






	template<typename T, std::size_t N>
	class Matrix
	{
	public:
		static constexpr auto identity() -> Matrix<T, N>;

		static constexpr auto scalar(Vector<T, 3> const &factors)               -> Matrix<T, 4>;
		static           auto rotation(T const angle, Vector<T, 3> const &axes) -> Matrix<T, 4>;
		static constexpr auto translation(Vector<T, 3> const &offsets)          -> Matrix<T, 4>;

		static           auto projection(T const fov, T const aspect_ratio, T const near, T const far) -> Matrix<T, 4>;


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
	using Matrix2   = Matrix<T, 2>;
	using BMatrix2  = Matrix2<bool>;
	using IMatrix2  = Matrix2<int>;
	using FMatrix2  = Matrix2<float>;
	using DMatrix2  = Matrix2<double>;
	using LDMatrix2 = Matrix2<long double>;

	template<typename T>
	using Matrix3   = Matrix<T, 3>;
	using BMatrix3  = Matrix3<bool>;
	using IMatrix3  = Matrix3<int>;
	using FMatrix3  = Matrix3<float>;
	using DMatrix3  = Matrix3<double>;
	using LDMatrix3 = Matrix3<long double>;

	template<typename T>
	using Matrix4   = Matrix<T, 4>;
	using BMatrix4  = Matrix4<bool>;
	using IMatrix4  = Matrix4<int>;
	using FMatrix4  = Matrix4<float>;
	using DMatrix4  = Matrix4<double>;
	using LDMatrix4 = Matrix4<long double>;
}






#include "impl/Matrix.ipp"






#endif
