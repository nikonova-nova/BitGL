#include <algorithm>



#include "Color.hpp"
#include "Point.hpp"
#include "DrawWindow.hpp"






namespace BitGL
{
	DrawWindow::DrawWindow(Vec2<int> const &size, std::string const &title) :
		Window               (size, title),
		m_colorbuffer        (size[Vec::width] * size[Vec::height], RGB(0, 0, 0)),
		m_colorbuffer_dc     { CreateCompatibleDC(get_hdc()) },
		m_colorbuffer_bitmap { CreateBitmap(size[Vec::width], size[Vec::height], 1, sizeof(decltype(m_colorbuffer)::value_type) * 8, m_colorbuffer.data()) },
		m_old_bitmap         { static_cast<decltype(m_old_bitmap)>(SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap)) }
	{}
	DrawWindow::~DrawWindow()
	{
		SelectObject(m_colorbuffer_dc, m_old_bitmap);
		DeleteObject(m_colorbuffer_bitmap);
		DeleteDC(m_colorbuffer_dc);
	}



	auto DrawWindow::clear_colorbuffer(ColorRGB const &color) -> void
	{
		std::fill(m_colorbuffer.begin(), m_colorbuffer.end(), to_colorref(color));
	}
	auto DrawWindow::render_point(Point2D const &position, ColorRGB const &color) -> void
	{
		m_colorbuffer[to_1d_index(position, get_size())] = to_colorref(color);
	}
	auto DrawWindow::render_line(Point2D const &point_a, Point2D const &point_b, ColorRGB const &color) -> void
	{
		auto x_0 = point_a[Vec::x];
		auto y_0 = point_a[Vec::y];

		auto x_1 = point_b[Vec::x];
		auto y_1 = point_b[Vec::y];

		auto d_x = std::abs(x_1 - x_0);
		auto s_x = x_1 > x_0 ? 1 : -1;

		auto d_y = -std::abs(y_1 - y_0);
		auto s_y = y_1 > y_0 ? 1 : -1;

		auto error = d_x + d_y;



		while (true)
		{
			render_point({ x_0, y_0 }, color);

			if (x_0 == x_1 && y_0 == y_1) { break; }

			if (error * 2 >= d_y)
			{
				if (x_0 == x_1) { break; }
				error += d_y;
				x_0 += s_x;
			}

			if (error * 2 <= d_x)
			{
				if (y_0 == y_1) { break; }
				error += d_x;
				y_0 += s_y;
			}
		}
	}

	auto DrawWindow::render_triangle(Triangle2D const &triangle, ColorRGB const &color) -> void
	{
		render_line(triangle[Vec::x], triangle[Vec::y], color);
		render_line(triangle[Vec::y], triangle[Vec::z], color);
		render_line(triangle[Vec::z], triangle[Vec::x], color);
	}

	auto DrawWindow::draw() -> void
	{
		SetBitmapBits(m_colorbuffer_bitmap, m_colorbuffer.size() * sizeof(decltype(m_colorbuffer)::value_type), m_colorbuffer.data());
		SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap);

		auto window_size = get_size();

		BitBlt(get_hdc(),
		       0,
		       0,
		       window_size[Vec::width],
		       window_size[Vec::height],
		       m_colorbuffer_dc,
		       0,
		       0,
		       SRCCOPY);
	}
}
