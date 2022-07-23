#include <algorithm>



#include "Color.hpp"
#include "Point.hpp"
#include "DrawWindow.hpp"






namespace BitGL
{
	DrawWindow::DrawWindow(Vector2<int> const &size, std::string const &title) :
		Window               (size, title),
		m_colorbuffer        (size.width() * size.height(), RGB(0, 0, 0)),
		m_colorbuffer_dc     { CreateCompatibleDC(get_hdc()) },
		m_colorbuffer_bitmap { CreateBitmap(size.width(), size.height(), 1, sizeof(decltype(m_colorbuffer)::value_type) * 8, m_colorbuffer.data()) },
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
	auto DrawWindow::add_point(Point2D const &position, ColorRGB const &color) -> void
	{
		auto position_center_origin = get_size() / 2;
		position_center_origin += position;
		m_colorbuffer[to_1d_index(position_center_origin - 1, get_size())] = to_colorref(color);
	}
	auto DrawWindow::add_line(Point2D const &point_a, Point2D const &point_b, ColorRGB const &color) -> void
	{
		auto x_0 = point_a.x();
		auto y_0 = point_a.y();

		auto x_1 = point_b.x();
		auto y_1 = point_b.y();

		auto d_x = std::abs(x_1 - x_0);
		auto s_x = x_1 > x_0 ? 1 : -1;

		auto d_y = -std::abs(y_1 - y_0);
		auto s_y = y_1 > y_0 ? 1 : -1;

		auto error = d_x + d_y;



		while (true)
		{
			add_point({ x_0, y_0 }, color);

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

	auto DrawWindow::add_triangle(Triangle2D const &triangle, ColorRGB const &color) -> void
	{
		add_line(triangle[0], triangle[1], color);
		add_line(triangle[1], triangle[2], color);
		add_line(triangle[2], triangle[0], color);
	}
	auto DrawWindow::add_triangle_filled(Triangle2D triangle, ColorRGB const &color) -> void
	{
		std::sort(triangle.begin(),
		          triangle.end(),
		          [](Point2D const &a, Point2D const &b) { return a.y() > b.y(); });

		if (triangle[0].y() == triangle[1].y())
		{
			add_triangle_filled_flat_top(triangle, color);
		}
		else if (triangle[1].y() == triangle[2].y())
		{
			add_triangle_filled_flat_bottom(triangle, color);
		}
		else
		{
			Point2D divider_point =
			{
				static_cast<int>(triangle[0].x() + (static_cast<float>(triangle[1].y() - triangle[0].y()) / (triangle[2].y() - triangle[0].y())) * (triangle[2].x() - triangle[0].x())),
				triangle[1].y()
			};

			add_triangle_filled_flat_top({ triangle[1], divider_point, triangle[2] }, color);
			add_triangle_filled_flat_bottom({ triangle[0], triangle[1], divider_point }, color);
		}
	}

	auto DrawWindow::draw() -> void
	{
		SetBitmapBits(m_colorbuffer_bitmap, m_colorbuffer.size() * sizeof(decltype(m_colorbuffer)::value_type), m_colorbuffer.data());
		SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap);

		auto window_size = get_size();

		BitBlt(get_hdc(),
		       0,
		       0,
		       window_size.width(),
		       window_size.height(),
		       m_colorbuffer_dc,
		       0,
		       0,
		       SRCCOPY);
	}



	auto DrawWindow::add_triangle_filled_flat_top(Triangle2D const &triangle, ColorRGB const &color) -> void
	{
		auto a_x_0 = triangle[2].x();
		auto a_y_0 = triangle[2].y();
		auto b_x_0 = triangle[2].x();
		auto b_y_0 = triangle[2].y();

		auto a_x_1 = triangle[0].x();
		auto a_y_1 = triangle[0].y();

		auto b_x_1 = triangle[1].x();
		auto b_y_1 = triangle[1].y();



		auto a_d_x = std::abs(a_x_1 - a_x_0);
		auto a_s_x = a_x_1 > a_x_0 ? 1 : -1;

		auto b_d_x = std::abs(b_x_1 - b_x_0);
		auto b_s_x = b_x_1 > b_x_0 ? 1 : -1;

		auto a_d_y = -(a_y_1 - a_y_0);
		auto a_s_y = 1;

		auto b_d_y = -(b_y_1 - b_y_0);
		auto b_s_y = 1;

		auto a_error = a_d_x + a_d_y;
		auto b_error = b_d_x + b_d_y;



		while (true)
		{
			add_line({ a_x_0, a_y_0 }, { b_x_0, b_y_0 }, color);

			if ((a_x_0 == a_x_1 && a_y_0 == a_y_1) &&
			    (b_x_0 == b_x_1 && b_y_0 == b_y_1)) { break; }

			while (a_error * 2 >= a_d_y)
			{
				if (a_x_0 == a_x_1) { break; }
				a_error += a_d_y;
				a_x_0 += a_s_x;
			}

			if (a_error * 2 <= a_d_x)
			{
				if (a_y_0 == a_y_1) { break; }
				a_error += a_d_x;
				a_y_0 += a_s_y;
			}

			while (b_error * 2 >= b_d_y)
			{
				if (b_x_0 == b_x_1) { break; }
				b_error += b_d_y;
				b_x_0 += b_s_x;
			}

			if (b_error * 2 <= b_d_x)
			{
				if (b_y_0 == b_y_1) { break; }
				b_error += b_d_x;
				b_y_0 += b_s_y;
			}
		}
	}
	auto DrawWindow::add_triangle_filled_flat_bottom(Triangle2D const &triangle, ColorRGB const &color) -> void
	{
		auto a_x_0 = triangle[0].x();
		auto a_y_0 = triangle[0].y();
		auto b_x_0 = triangle[0].x();
		auto b_y_0 = triangle[0].y();

		auto a_x_1 = triangle[1].x();
		auto a_y_1 = triangle[1].y();

		auto b_x_1 = triangle[2].x();
		auto b_y_1 = triangle[2].y();



		auto a_d_x = std::abs(a_x_1 - a_x_0);
		auto a_s_x = a_x_1 > a_x_0 ? 1 : -1;

		auto b_d_x = std::abs(b_x_1 - b_x_0);
		auto b_s_x = b_x_1 > b_x_0 ? 1 : -1;

		auto a_d_y = a_y_1 - a_y_0;
		auto a_s_y = -1;

		auto b_d_y = b_y_1 - b_y_0;
		auto b_s_y = -1;

		auto a_error = a_d_x + a_d_y;
		auto b_error = b_d_x + b_d_y;



		while (true)
		{
			add_line({ a_x_0, a_y_0 }, { b_x_0, b_y_0 }, color);

			if ((a_x_0 == a_x_1 && a_y_0 == a_y_1) &&
			    (b_x_0 == b_x_1 && b_y_0 == b_y_1)) { break; }

			while (a_error * 2 >= a_d_y)
			{
				if (a_x_0 == a_x_1) { break; }
				a_error += a_d_y;
				a_x_0 += a_s_x;
			}

			if (a_error * 2 <= a_d_x)
			{
				if (a_y_0 == a_y_1) { break; }
				a_error += a_d_x;
				a_y_0 += a_s_y;
			}

			while (b_error * 2 >= b_d_y)
			{
				if (b_x_0 == b_x_1) { break; }
				b_error += b_d_y;
				b_x_0 += b_s_x;
			}

			if (b_error * 2 <= b_d_x)
			{
				if (b_y_0 == b_y_1) { break; }
				b_error += b_d_x;
				b_y_0 += b_s_y;
			}
		}
	}
}
