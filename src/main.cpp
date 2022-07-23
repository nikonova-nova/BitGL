#include <cmath>
#include <cstdio>



#include <chrono>
#include <iostream>



#include "Vector.hpp"
#include "Matrix.hpp"
#include "DrawWindow.hpp"






auto main() -> int
{
	BitGL::DrawWindow window({ 1280, 720 }, "BitGL");
	window.restore();



	std::array<BitGL::Vector3<BitGL::FVector3>, 12> cube
	{{
		// SOUTH
		{ -1.0f, -1.0f, -1.0f,    -1.0f, 1.0f, -1.0f,    1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, -1.0f,    1.0f, -1.0f, -1.0f },

		// EAST
		{ 1.0f, -1.0f, -1.0f,    1.0f, 1.0f, -1.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f,    1.0f, -1.0f, 1.0f },

		// NORTH
		{ 1.0f, -1.0f, 1.0f,    1.0f, 1.0f, 1.0f,    -1.0f, 1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f,    -1.0f, 1.0f, 1.0f,    -1.0f, -1.0f, 1.0f },

		// WEST
		{ -1.0f, -1.0f, 1.0f,    -1.0f, 1.0f, 1.0f,    -1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, 1.0f,    -1.0f, 1.0f, -1.0f,    -1.0f, -1.0f, -1.0f },

		// TOP
		{ -1.0f, 1.0f, -1.0f,    -1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, -1.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, -1.0f },

		// BOTTOM
		{ 1.0f, -1.0f, 1.0f,    -1.0f, -1.0f, 1.0f,    -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, 1.0f,    -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f },
	}};



	auto time_before = BitGL::Window::get_time();

	while (window.is_open())
	{
		auto time_now = BitGL::Window::get_time();
		auto delta_time = time_now - time_before;
		time_before = time_now;

		printf("T: %f\tFPS: %f\n", delta_time, 1 / delta_time);

		window.clear_colorbuffer({ 0, 0, 0 });

		for (auto triangle : cube)
		{
			for (auto &point : triangle.m_internal_array)
			{
				auto window_size = BitGL::convert<int, 2, float>(window.get_size());

				point.translate({ 0.0f, 0.0f, 0.0f });
				point.project(1.5708f, window_size.x() / window_size.y(), 0.1f, 1000.0f);
				point.scale({ window_size.x() / 2, window_size.y() / 2, 1 });
			}

			BitGL::Triangle2D triangle2d
			{{
				BitGL::convert<float, 2, int>(BitGL::truncate<float, 3, 2>(triangle.x())),
				BitGL::convert<float, 2, int>(BitGL::truncate<float, 3, 2>(triangle.y())),
				BitGL::convert<float, 2, int>(BitGL::truncate<float, 3, 2>(triangle.z()))
			}};

			window.add_triangle(triangle2d, { 255, 255, 255 });
		}

		window.draw();

		BitGL::Window::poll_events();
	}



	return EXIT_SUCCESS;
}
