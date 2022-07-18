#include <cmath>



#include <chrono>
#include <iostream>



#include "Vec.hpp"
#include "DrawWindow.hpp"






auto main() -> int
{
	BitGL::DrawWindow window({ 800, 800 }, "BitGL");
	window.restore();



	while (window.is_open())
	{
		auto time_now = BitGL::Window::get_time();

		std::uint8_t r = (std::cos(time_now + 0      ) + 1) * 127;
		std::uint8_t g = (std::cos(time_now + 2.0944 ) + 1) * 127;
		std::uint8_t b = (std::cos(time_now + 4.18879) + 1) * 127;

		window.clear_colorbuffer({ 0, 0, 0 });

		window.render_line({ 400, 799 }, { 0  , 400 }, { r, g, b });
		window.render_line({ 0  , 400 }, { 400, 0   }, { r, g, b });
		window.render_line({ 400, 0   }, { 799, 400 }, { r, g, b });
		window.render_line({ 799, 400 }, { 400, 799 }, { r, g, b });

		window.draw();

		BitGL::Window::poll_events();
	}



	return EXIT_SUCCESS;
}
