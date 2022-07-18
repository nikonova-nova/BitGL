#include <cmath>
#include <cstdio>



#include <chrono>
#include <iostream>



#include "Vec.hpp"
#include "DrawWindow.hpp"






auto main() -> int
{
	BitGL::DrawWindow window({ 800, 800 }, "BitGL");
	window.restore();


	auto time_before = BitGL::Window::get_time();

	while (window.is_open())
	{
		auto time_now = BitGL::Window::get_time();
		auto delta_time = time_now - time_before;
		time_before = time_now;

		printf("T: %f\tFPS: %f\n", delta_time, 1 / delta_time);

		std::uint8_t r = (std::cos(time_now + 0      ) + 1) * 127;
		std::uint8_t g = (std::cos(time_now + 2.0944 ) + 1) * 127;
		std::uint8_t b = (std::cos(time_now + 4.18879) + 1) * 127;

		window.clear_colorbuffer({ 0, 0, 0 });

		for (int i = 0; i < 800; ++i)
		{
			window.render_line({ i, 0 }, { i, 799 }, { r, g, b });
			window.render_line({ 0, i }, { 799, i }, { g, b, r });
		}

		window.draw();

		BitGL::Window::poll_events();
	}



	return EXIT_SUCCESS;
}
