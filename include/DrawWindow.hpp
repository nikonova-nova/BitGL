#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_DRAWWINDOW_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_DRAWWINDOW_HPP






#include <string>
#include <vector>



#include "Window.hpp"






class DrawWindow : public Window
{
public:
	DrawWindow(Vec2<int> const &size, std::string const &title);
	~DrawWindow();


public:
	auto clear_colorbuffer(Vec3<int> const &color)                      -> void;
	auto render_point(Vec2<int> const &position, Vec3<int> const &color) -> void;

	auto draw() -> void;


private:
	std::vector<COLORREF> m_colorbuffer;
	HDC                   m_colorbuffer_dc;
	HBITMAP               m_colorbuffer_bitmap;

	HBITMAP m_old_bitmap; // necessary to properly destruct framebuffer_dc
};






#endif
