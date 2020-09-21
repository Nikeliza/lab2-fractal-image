#pragma once
#include <vector>
#include "Windows.h"

class Image8
{
	std::vector<std::vector<BYTE>> image1;
	std::vector<std::vector<BYTE>> image;
	BITMAPFILEHEADER bfh_l;
	BITMAPINFOHEADER bih_l;
	std::vector<RGBQUAD> colors;

	void create_image();

public:
	Image8(int width, int height);
	Image8(int width, int height, std::vector<RGBQUAD> c, BITMAPFILEHEADER bf, BITMAPINFOHEADER bi);
	Image8();
	void read_image(const char* file_name);
	void print_image(const char* file_name);


	int get_height();
	int get_width();
	std::vector<RGBQUAD> get_colors();
	BITMAPFILEHEADER get_file();
	BITMAPINFOHEADER get_info();

	std::vector<BYTE>& operator[] (const int index);
};

