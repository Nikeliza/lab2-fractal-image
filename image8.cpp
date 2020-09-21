#include "Image8.h"
#include <fstream>
#include <iostream>
//#include "stdafx.h"
//#include<iostream>


void Image8::create_image()
{
	image = std::vector<std::vector<BYTE>>(256);
	for (int i = 0; i < 256; i++) {
		image[i] = std::vector<BYTE>(256);
	}
	for (int i = 0; i < get_height(); i++) {
		for (int j = 0; j < get_width(); j++) {
			image[i][j] = (colors[image1[i][j]].rgbBlue + colors[image1[i][j]].rgbGreen + colors[image1[i][j]].rgbRed) / 3;
		}
	}
}

Image8::Image8(int width, int height)
{
	image1 = std::vector<std::vector<BYTE>>(height);
	for (int i = 0; i < height; i++) {
		image1[i] = std::vector<BYTE>(width);
	}
}

Image8::Image8(int width, int height, std::vector<RGBQUAD> c, BITMAPFILEHEADER bf, BITMAPINFOHEADER bi)
{
	image1 = std::vector<std::vector<BYTE>>(height);
	for (int i = 0; i < height; i++) {
		image1[i] = std::vector<BYTE>(width);
	}
	image = std::vector<std::vector<BYTE>>(height);
	for (int i = 0; i < height; i++) {
		image[i] = std::vector<BYTE>(width);
	}
	colors = c;
	bfh_l = bf;
	bih_l = bi;
}

Image8::Image8()
{
}

void Image8::read_image(const char* file_name)
{
	try {
		// ќткрываем файл
		std::ifstream file(file_name, std::ios::in | std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "file not open" << std::endl;
			return;
		}
		int size, pixels_adress, width, height;
		short int bits_per_pixel;

		file.read((char*)&bfh_l, sizeof(bfh_l));
		file.read((char*)&bih_l, sizeof(bih_l));
	
		image1 = std::vector<std::vector<BYTE>>(bih_l.biHeight);
		colors = std::vector<RGBQUAD>(256);
		for (int i = 0; i < 256; i++) {
			file.read((char*)&colors[i], 4);
		}
		for (int x = bih_l.biHeight - 1; x >= 0; x--)
		{
			std::vector<BYTE> mas1(bih_l.biWidth);
			for (int y = 0; y < bih_l.biWidth; y++)
			{
				file.read((char*)&mas1[y], 1);

			}
			image1[x] = mas1;
		}
		
		file.close();
		create_image();
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}
	
}

void Image8::print_image(const char* file_name)
{
	try {
		// ќткрываем файл
		std::ofstream file(file_name, std::ios::out | std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "file not open for write" << std::endl;
			return;
		}
		int size, pixels_adress, width, height;
		short int bits_per_pixel;

		file.write((char*)&bfh_l, sizeof(bfh_l));
		file.write((char*)&bih_l, sizeof(bih_l));
		for (int i = 0; i < 256; i++) {
			file.write((char*)&i, 1);
			file.write((char*)&i, 1);
			file.write((char*)&i, 1);
			file.write((char*)&i, 1);
		}
		unsigned int bgr = 0;
		size_t padding = 0;
		if ((bih_l.biWidth) % 4) padding = 4 - (bih_l.biWidth) % 4;
		for (int x = bih_l.biHeight - 1; x >= 0; x--)
		{

			for (int y = 0; y < bih_l.biWidth; y++)
			{
				file.write((char*)&image[x][y], 1);
			}
			for (int y = 0; y < padding; y++) {
				file.write((char*)&image[x][bih_l.biWidth - 1], 1);
			}

		}
		
		file.close();
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
}

int Image8::get_height()
{
	return image.size();
}

int Image8::get_width()
{
	return image[0].size();
}

std::vector<RGBQUAD> Image8::get_colors()
{
	return colors;
}

BITMAPFILEHEADER Image8::get_file()
{
	return bfh_l;
}

BITMAPINFOHEADER Image8::get_info()
{
	return bih_l;
}


std::vector<BYTE>& Image8::operator[](const int index)
{
	return image[index];
}
