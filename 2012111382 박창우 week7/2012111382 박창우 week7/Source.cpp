#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include<vector>




const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

bool insidecircle(int x, int y, int x_c, int y_c)
{
	int r = 50;

	int f = (x_c - x)*(x_c - x) + (y_c - y)*(y_c - y) - r*r;
	if (f <100 && f>-100) return true;
	else return false;
}



class Object
{
public:

	int x;
	int y;

	void (Object::*draw_surrounding_object_callback_)() = nullptr;

	void exec()
	{
		if (draw_surrounding_object_callback_ != nullptr)
			(this->*draw_surrounding_object_callback_)();
	}

	void command(Object* ob, void(Object::*draw_surrounding_object_callback_)())
	{
		(ob->*draw_surrounding_object_callback_)();
	}

	void drawcircle()
	{
		for (int x_i = x - 60; x_i < x + 60; x_i++)
		{
			for (int y_i = y - 60; y_i < y + 60; y_i++)
			{
				if (insidecircle(x_i, y_i, x, y) == true)
				{
					drawPixel(x_i, y_i, 1.0f, 0.0f, 1.0f);
				}
			}
		}
	}



	void drawbox()
	{
		for (int i = x - 50; i < x + 50; i++)
		{
			for (int j = y - 50; j < y + 50; j++)
			{
				if (i == x - 50) drawPixel(i, j, 1.0f, 0.7f, 0.5f);
				if (i == x + 49) drawPixel(i, j, 1.0f, 0.7f, 0.5f);
				if (j == y - 50) drawPixel(i, j, 1.0f, 0.7f, 0.5f);
				if (j == y + 49) drawPixel(i, j, 1.0f, 0.7f, 0.5f);
			}
		}
	}

	void draw_innerbox()
	{
		for (int i = x - 35; i < x + 35; i++)
		{
			for (int j = y - 35; j < y + 35; j++)
			{
				if (i == x - 35) drawPixel(i, j, 0.0f, 1.0f, 0.5f);
				if (i == x + 34) drawPixel(i, j, 0.0f, 1.0f, 0.5f);
				if (j == y - 35) drawPixel(i, j, 0.0f, 1.0f, 0.5f);
				if (j == y + 34) drawPixel(i, j, 0.0f, 1.0f, 0.5f);
			}
		}
	}



};





// And implement an templatized GeometricObject class.
int main()
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "2012111382_week7", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/////여기부터시작
		std::fill_n(pixels, width*height * 3, 1.0f);



		Object shape1;
		shape1.draw_surrounding_object_callback_
			= &Object::drawbox;
		shape1.x = 400;
		shape1.y = 300;

		shape1.command(&shape1, &Object::draw_innerbox);

		shape1.exec();


		Object shape2;
		shape2.draw_surrounding_object_callback_
			= &Object::drawcircle;
		shape2.x = 200;
		shape2.y = 300;

		shape2.command(&shape2, &Object::draw_innerbox);

		shape2.exec();




		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	delete[] pixels;

	glfwTerminate();
	return 0;
}