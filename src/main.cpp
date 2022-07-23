#include <cmath>
#include <cstdio>



#include <chrono>
#include <iostream>



#include "Vector.hpp"
#include "Matrix.hpp"
#include "DrawWindow.hpp"






auto main() -> int
{
	BitGL::DrawWindow window({ 800, 800 }, "BitGL");
	window.restore();



	std::array<BitGL::Vector3<BitGL::FVector3>, 12> cube
	{{
		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
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
				point.scale({ 100, 100, 100 });
				point.rotate(std::cos(time_now), { 0, 1, 0 });
				point.rotate(std::sin(time_now), { 1, 0, 0 });
				point.rotate(std::sin(time_now), { 0, 0, 1 });
				point.translate({ 399, 399, 0 });
				//auto perspective = BitGL::FMatrix3::projection(1.5708f, 16.0f / 9, 0.1f, 1000.0f);
				//point *= perspective;
			}

			BitGL::Triangle2D triangle2d
			{{
				{ static_cast<int>(triangle[0].x()), static_cast<int>(triangle[0].y()) },
				{ static_cast<int>(triangle[1].x()), static_cast<int>(triangle[1].y()) },
				{ static_cast<int>(triangle[2].x()), static_cast<int>(triangle[2].y()) }
			}};

			window.add_triangle(triangle2d, { 255, 255, 255 });
		}

		window.draw();

		BitGL::Window::poll_events();
	}



	return EXIT_SUCCESS;
}
