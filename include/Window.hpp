#ifndef NIKONOVA_NOVA_BITGL_SRC_WINDOW_HPP
#define NIKONOVA_NOVA_BITGL_SRC_WINDOW_HPP






#include <Windows.h>



#include <string>






class Window
{
public:
	Window(int const width, int const height, std::string const &title) noexcept;
	~Window() noexcept;


public:
	auto is_open() -> bool;

	auto restore()  -> void;
	auto minimize() -> void;

	auto poll_events() -> void;
	auto wait_events() -> void;


public:
	auto get_hwnd() -> HWND;
	auto get_hdc()  -> HDC;


private:
	static auto create_window_class()                                                                           -> ATOM;
	static auto create_window(int const width, int const height, std::string const &title, bool const *is_open) -> HWND;


private:
	static auto CALLBACK m_window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) -> LRESULT;
	inline static ATOM m_window_class_id = 0;

	HWND m_window;
	HDC  m_dc;

	bool m_is_open;
};






#endif
