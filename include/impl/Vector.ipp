#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_IPP






#include <cmath>






#include "Matrix.hpp"






#define BITGL_VECTOR_DEFN_ACCESS(f, i)                                                          \
template<typename T, std::size_t N>                                                             \
constexpr auto Vector<T, N>::f()       -> T       &                                             \
{                                                                                               \
	static_assert(N >= i + 1, "This function will index out of bounds on this size of Vector"); \
	return m_internal_array[i];                                                                 \
}                                                                                               \
template<typename T, std::size_t N>                                                             \
constexpr auto Vector<T, N>::f() const -> T const &                                             \
{                                                                                               \
	static_assert(N >= i + 1, "This function will index out of bounds on this size of Vector"); \
	return m_internal_array[i];                                                                 \
}






namespace BitGL
{
	// VectorN
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::normalize() -> void
	{
		*this /= length();
	}

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::scale(Vector<T, 3> const &factors) -> void
	{ static_assert(N == 3, "This function is only available for Vector3s"); *this *= Matrix<T, N>::scalar(factors); }
	template<typename T, std::size_t N>
	auto Vector<T, N>::rotate(T const angle, Vector<T, 3> const &axes) -> void
	{ static_assert(N == 3, "This function is only available for Vector3s"); *this *= Matrix<T, N>::rotation(angle, axes); }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::translate(Vector<T, 3> const &offsets) -> void
	{ static_assert(N == 3, "This function is only available for Vector3s"); *this *= Matrix<T, N>::translation(offsets); }

	template<typename T, std::size_t N>
	auto Vector<T, N>::project(T const fov, T const aspect_ratio, T const zn, T const zf) -> void
	{
		static_assert(N == 3, "This function is only available for Vector3s");
		auto temp = extend<T, 3, 4>(*this, 1);
		temp *= Matrix<T, N>::projection(fov, aspect_ratio, zn, zf);
		if (temp.w() != 0)
		{
			temp /= temp.w();
		};
		*this = truncate<T, 4, 3>(temp);
	}

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::length() const -> T
	{
		return std::sqrt(dot(*this, *this));
	}



	BITGL_VECTOR_DEFN_ACCESS(x, 0)
	BITGL_VECTOR_DEFN_ACCESS(y, 1)
	BITGL_VECTOR_DEFN_ACCESS(z, 2)
	BITGL_VECTOR_DEFN_ACCESS(w, 3)

	BITGL_VECTOR_DEFN_ACCESS(r, 0)
	BITGL_VECTOR_DEFN_ACCESS(g, 1)
	BITGL_VECTOR_DEFN_ACCESS(b, 2)
	BITGL_VECTOR_DEFN_ACCESS(a, 3)

	BITGL_VECTOR_DEFN_ACCESS(s, 0)
	BITGL_VECTOR_DEFN_ACCESS(t, 1)
	BITGL_VECTOR_DEFN_ACCESS(p, 2)
	BITGL_VECTOR_DEFN_ACCESS(q, 3)

	BITGL_VECTOR_DEFN_ACCESS(width, 0)
	BITGL_VECTOR_DEFN_ACCESS(height, 1)
	BITGL_VECTOR_DEFN_ACCESS(depth, 2)



	template<typename T, std::size_t N, typename Tb>
	constexpr auto convert(Vector<T, N> const &from) -> Vector<Tb, N>
	{
		Vector<Tb, N> result;
		for (std::size_t i = 0; i < N; ++i)
		{
			result[i] = static_cast<Tb>(from[i]);
		}
		return result;
	}

	template<typename T, std::size_t N, std::size_t Nb>
	constexpr auto truncate(Vector<T, N> const &from) -> Vector<T, Nb>
	{
		static_assert(Nb < N, "This function is only valid if the passed Vector has a larger element count than the resulting Vector");
		Vector<T, Nb> result;
		for (std::size_t i = 0; i < Nb; ++i)
		{
			result[i] = from[i];
		}
		return result;
	}

	template<typename T, std::size_t N, std::size_t Nb>
	constexpr auto extend(Vector<T, N> const &from, T const fill) -> Vector<T, Nb>
	{
		static_assert(Nb > N, "This function is only valid if the passed Vector has a smaller element count than the resulting Vector");
		Vector<T, Nb> result;
		for (std::size_t i = 0; i < N; ++i)
		{
			result[i] = from[i];
		}
		for (std::size_t i = N; i < Nb; ++i)
		{
			result[i] = fill;
		}
		return result;
	}



	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator++()    -> Vector<T, N> & { for (auto &x : m_internal_array) { ++x; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator++(int) -> Vector<T, N>   { auto tmp { *this }; operator++(); return tmp; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator--()    -> Vector<T, N> & { for (auto &x : m_internal_array) { --x; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator--(int) -> Vector<T, N>   { auto tmp { *this }; operator--(); return tmp; }



	template<typename T, std::size_t N>
	constexpr auto operator+(Vector<T, N> vector) -> Vector<T, N> { return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Vector<T, N> vector) -> Vector<T, N> { for (auto &x : vector.m_internal_array) { x = -x; } return vector; }



	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator+=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x += scalar; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator-=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x -= scalar; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator*=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x *= scalar; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator/=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x /= scalar; } return *this; }

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator+=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] += rhs[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator-=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] -= rhs[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator*=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] *= rhs[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator/=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] /= rhs[i]; } return *this; }

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator*=(Matrix<T, N> const &matrix) -> Vector<T, N> &
	{
		Vector<T, N> temp {};
		for (std::size_t i = 0; i < N; ++i)
		{
			for (std::size_t j = 0; j < N; ++j)
			{
				temp[i] += matrix[i][j] * (*this)[j];
			}
		}
		*this = temp;
		return *this;
	}
	template<typename T, std::size_t N>
	template<std::size_t Nb>
	constexpr auto Vector<T, N>::operator*=(Matrix<T, Nb> const &matrix) -> Vector<T, N> &
	{
		static_assert(Nb > N, "This function is only for when the passed Matrix is larger than the this Vector");
		auto temp = extend<T, N, Nb>(*this, 1);
		temp *= matrix;
		*this = truncate<T, Nb, N>(temp);
		return *this;
	}



	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator[](std::size_t const index)       -> T       & { return m_internal_array[index]; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator[](std::size_t const index) const -> T const & { return m_internal_array[index]; }



	template<typename T, std::size_t N>
	constexpr auto operator+(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector += scalar; return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector -= scalar; return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator*(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector *= scalar; return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator/(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector /= scalar; return vector; }

	template<typename T, std::size_t N>
	constexpr auto operator+(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs += rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs -= rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator*(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs *= rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator/(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs /= rhs; return lhs; }

	template<typename T, std::size_t N>
	constexpr auto operator*(Vector<T, N> vector, Matrix<T, N> const &matrix) -> Vector<T, N> { vector *= matrix; return vector; }

	template<typename T, std::size_t N, std::size_t Nb>
	constexpr auto operator*(Vector<T, N> vector, Matrix<T, Nb> const &matrix) -> Vector<T, N>
	{
		static_assert(Nb > N, "This function is only for when the passed Matrix is larger than the passed Vector");
		vector *= matrix;
		return vector;
	}



	template<typename T, std::size_t N>
	constexpr auto operator==(Vector<T, N> const &lhs, Vector<T, N> const &rhs) -> bool
	{ for (std::size_t i = 0; i < N; ++i) { if (lhs.m_internal_array[i] != rhs.m_internal_array[i]) { return false; } } return true; }



	template<typename T, std::size_t N>
	constexpr auto dot(Vector<T, N> const &a, Vector<T, N> const &b) -> T
	{
		auto tmp { a * b };
		T accum {};
		for (auto const &x : tmp.m_internal_array)
		{
			accum += x;
		}
		return accum;
	}
	template<typename T>
	constexpr auto cross(Vector3<T> const &a, Vector3<T> const &b) -> Vector3<T>
	{
		return {
			a.y() * b.z() - a.z() * b.y(),
			a.z() * b.x() - a.x() * b.z(),
			a.x() * b.y() - a.y() * b.x()
		};
	}
}






#endif
