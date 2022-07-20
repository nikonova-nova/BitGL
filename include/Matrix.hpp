#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_MATRIX_HPP






#include <array>






namespace BitGL
{
	template<typename T, std::size_t Rn, std::size_t Cn>
	class Matrix;



	template<typename T>
	class Matrix<T, 2, 2>
	{
	public:
		constexpr auto operator[](std::size_t n)       -> T       *;
		constexpr auto operator[](std::size_t n) const -> T const *;


	public:
		std::array<T, 2 * 2> m_internal_array;
	};
	template<typename T>
	using Matrix2x2 = Matrix<T, 2, 2>;



	template<typename T>
	class Matrix<T, 3, 3>
	{
	public:
		constexpr auto operator[](std::size_t n)       -> T       *;
		constexpr auto operator[](std::size_t n) const -> T const *;


	public:
		std::array<T, 3 * 3> m_internal_array;
	};
	template<typename T>
	using Matrix3x3 = Matrix<T, 3, 3>;



	template<typename T>
	class Matrix<T, 4, 4>
	{
	public:
		constexpr auto operator[](std::size_t n)       -> T       *;
		constexpr auto operator[](std::size_t n) const -> T const *;


	public:
		std::array<T, 4 * 4> m_internal_array;
	};
	template<typename T>
	using Matrix4x4 = Matrix<T, 4, 4>;
}






#endif
