#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

// scratched from https://courses.engr.illinois.edu/ece390/archive/archive-f2000/mp/mp4/anti.html
// see 'Rasterization' part.
void drawBoldLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
		drawPixel(i + 1, j, red, green, blue);
		drawPixel(i, j + 1, red, green, blue);
	}
}

void drawSq(const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= (i0+length); i++)
	{
		int j = j0;
		drawPixel(i, j, red, green, blue);
		j = j0 + length;
		drawPixel(i, j, red, green, blue);	
	}
	for (int j = j0; j <= (j0+length); j++)
	{
		int i = i0;
		drawPixel(i, j, red, green, blue);
		i = i0 + length;
		drawPixel(i, j, red, green, blue);
	}
}

void drawSqColor(const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= (i0+length); i++)
	{
		for (int j = j0; j <= (j0+length); j++)
		{			
			drawPixel(i, j, red, green, blue);	
		}
	}
}

//void test(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
//{
//	for (int i = i0; i <= i1; i++)
//	{
//		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;
//
//		drawPixel(i, j, red, green, blue);
//	}
//}

void drawTri(const int& i0, const int& j0, const int& height, const int& width, const float& red, const float& green, const float& blue)
{
	int j_ix = j0 - height;
	int i1 = i0 - (width / 2);
	int i2 = i0 + (width / 2);
	for (int i = i1; i <= i0; i++)
	{
		const int j = (j0 - j_ix)*(i - i1) / (i0 - i1) + j_ix;

		drawPixel(i, j, red, green, blue);
		drawPixel(i + 1, j, red, green, blue);
		drawPixel(i, j + 1, red, green, blue);
	}
	for (int i = i0; i <= i2; i++)
	{
		const int j = (j_ix - j0)*(i - i0) / (i2 - i0) + j0;

		drawPixel(i, j, red, green, blue);
		drawPixel(i+1, j, red, green, blue);
		drawPixel(i, j+1, red, green, blue);
	}
	for (int i = i1; i <= i2; i++)
	{
		const int j = j_ix;

		drawPixel(i, j, red, green, blue);
	}
}
void drawPenta(const int& i0, const int& j0, const int& length, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= (i0 + length); i++)
	{
		for (int j = j0; j <= (j0 + length); j++)
		{
			drawPixel(i, j, red, green, blue);

		}
	}
}
void drawCir(const int& x, const int& y, const int& r, const float& red, const float& green, const float& blue)
{
	for (int i = (x - r-1); i <= (x + r); i++)
	{
		for (int j = (y - r-1); j <= (y + r); j++)
		{
			const double f = (i - x)*(i - x) + (j - y)*(j - y) - r*r;
			if (f <100.0f)
			{
				if (f > -100.0f)
				{
					drawPixel(i, j, red, green, blue);
				}
			}
		}
	}	
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	// drawing a line
	//TODO: anti-aliasing
	drawBoldLine(50, 300, 200, 450, 1.0f, 0.0f, 0.0f);
	drawSq(250, 300, 150, 0.0f, 1.0f, 0.0f);
	drawSqColor(450, 300, 150, 0.0f, 0.0f, 1.0f);
	//test(0, 0, 25, 100, 1.0f, 0.0f, 0.0f);
	drawTri(120, 200, 140, 160, 255.0f, 0.0f, 255.0f);
	drawCir(530, 130, 80, 0.0f, 0.0f, 0.0f);
	

	//TODO: try moving object
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Week3", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
