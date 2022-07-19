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

		window.clear_colorbuffer({ 0, 0, 0 });

		BitGL::Point2D front_top_left      = { 99 , 299 };
		BitGL::Point2D front_top_right     = { 499, 299 };
		BitGL::Point2D front_bottom_right  = { 499, 699 };
		BitGL::Point2D front_bottom_left   = { 99 , 699 };

		BitGL::Point2D back_top_left      = { 299, 99  };
		BitGL::Point2D back_top_right     = { 699, 99  };
		BitGL::Point2D back_bottom_right  = { 699, 499 };
		BitGL::Point2D back_bottom_left   = { 299, 499 };

		BitGL::Triangle2D front_a = { front_top_left, front_top_right, front_bottom_right };
		BitGL::Triangle2D front_b = { front_bottom_right, front_bottom_left, front_top_left };

		BitGL::Triangle2D back_a = { back_top_left, back_top_right, back_bottom_right };
		BitGL::Triangle2D back_b = { back_bottom_right, back_bottom_left, back_top_left };

		BitGL::Triangle2D top_a = { back_top_left, back_top_right, front_top_right };
		BitGL::Triangle2D top_b = { front_top_right, front_top_left, back_top_left };

		BitGL::Triangle2D bottom_a = { back_bottom_left, back_bottom_right, front_bottom_right };
		BitGL::Triangle2D bottom_b = { front_bottom_right, front_bottom_left, back_bottom_left };

		BitGL::ColorRGB cyan = { 0, 255, 255 };

		window.render_triangle(front_a, cyan);
		window.render_triangle(front_b, cyan);

		window.render_triangle(back_a, cyan);
		window.render_triangle(back_b, cyan);

		window.render_triangle(top_a, cyan);
		window.render_triangle(top_b, cyan);

		window.render_triangle(bottom_a, cyan);
		window.render_triangle(bottom_b, cyan);

		window.draw();

		BitGL::Window::poll_events();
	}



	return EXIT_SUCCESS;
}
