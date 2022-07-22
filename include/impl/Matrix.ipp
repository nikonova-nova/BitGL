#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP






#include <cmath>






namespace BitGL
{
	template<typename T, std::size_t N>
	constexpr auto identity() -> Matrix<T, N>
	{
		Matrix<T, N> temp {};
		for (std::size_t i = 0; i < N; ++i)
		{
			temp[i][i] = 1;
		}
		return temp;
	}

	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::scalar(Vector<T, 4> const &factors) -> Matrix<T, 4>
	{
		return Matrix<T, 4>
		{
			factors.x(), 0          , 0          , 0,
			0          , factors.y(), 0          , 0,
			0          , 0          , factors.z(), 0,
			0          , 0          , 0          , 1
		};
	}
	template<typename T, std::size_t N>
	auto Matrix<T, N>::rotation(T const angle, Vector<T, 4> const &axes) -> Matrix<T, 4>
	{
		T const s = std::sin(angle);
		T const c = std::cos(angle);
		T const n = 1 - c;
		T const x = axes.x();
		T const y = axes.y();
		T const z = axes.z();
		return Matrix<T, 4>
		{
			x*x*n+  c, y*x*n-z*s, z*x*n+y*s, 0,
			x*y*n+z*s, y*y*n  +c, z*y*n-x*s, 0,
			x*z*n-y*s, y*z*n+x*s, z*z*n  +c, 0,
			0        , 0        , 0        , 1
		};
	}
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::translation(Vector<T, 4> const &offsets)          -> Matrix<T, 4>
	{
		return Matrix<T, 4>
		{
			1, 0, 0, offsets.x(),
			0, 1, 0, offsets.y(),
			0, 0, 1, offsets.z(),
			0, 0, 0, 1
		};
	}



	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator*=(T const scalar)          -> Matrix<T, N> & { for (auto &x : m_internal_array) { x *= scalar; } return *this; }

	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator+=(Matrix<T, N> const &rhs) -> Matrix<T, N> &
	{ for (std::size_t i = 0; i < N * N; ++i) { m_internal_array[i] += rhs.m_internal_array[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator-=(Matrix<T, N> const &rhs) -> Matrix<T, N> &
	{ for (std::size_t i = 0; i < N * N; ++i) { m_internal_array[i] -= rhs.m_internal_array[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator*=(Matrix<T, N> const &rhs) -> Matrix<T, N> &
	{
		Matrix<T, N> temp {};
		for (std::size_t i = 0; i < N; ++i)
		{
			for (std::size_t j = 0; j < N; ++j)
			{
				for (std::size_t k = 0; k < N; ++k)
				{
					temp[i][j] += (*this)[i][k] * rhs[k][j];
				}
			}
		}
		m_internal_array = temp.m_internal_array;
		return *this;
	}



	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator[](std::size_t n)       -> T       * { return m_internal_array.data() + n * N; }
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator[](std::size_t n) const -> T const * { return m_internal_array.data() + n * N; }



	template<typename T, std::size_t N>
	constexpr auto operator*(Matrix<T, N> matrix, T const scalar)       -> Matrix<T, N> { matrix += scalar; return matrix; }

	template<typename T, std::size_t N>
	constexpr auto operator+(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N> { lhs += rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N> { lhs -= rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator*(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N> { lhs *= rhs; return lhs; }
}






#endif
