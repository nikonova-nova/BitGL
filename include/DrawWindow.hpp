#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_DRAWWINDOW_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_DRAWWINDOW_HPP






#include <cstdint>



#include <string>
#include <vector>



#include "Color.hpp"
#include "Point.hpp"
#include "Triangle.hpp"
#include "Window.hpp"






namespace BitGL
{
	class DrawWindow : public Window
	{
	public:
		DrawWindow(Vec2<int> const &size, std::string const &title);
		~DrawWindow();


	public:
		auto clear_colorbuffer(ColorRGB const &color)                     -> void;
		auto render_point(Point2D const &position, ColorRGB const &color) -> void;
		auto render_line(Point2D const &point_a, Point2D const &point_b, ColorRGB const &color)  -> void;
		auto render_triangle(Triangle2D const &triangle, ColorRGB const &color) -> void;

		auto draw() -> void;


	private:
		std::vector<COLORREF> m_colorbuffer;
		HDC                   m_colorbuffer_dc;
		HBITMAP               m_colorbuffer_bitmap;

		HBITMAP m_old_bitmap; // necessary to properly destruct framebuffer_dc
	};
}






#endif
