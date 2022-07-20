#include <cmath>
#include <cstdio>



#include <chrono>
#include <iostream>



#include "Vector.hpp"
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

		window.clear_colorbuffer({ 0, 0, 0 });

		window.add_triangle_filled({{ { 0, 799 }, { 399, 0 }, { 799, 799 } }}, { 0, 255, 255 });

		window.draw();

		BitGL::Window::poll_events();
	}



	return EXIT_SUCCESS;
}
