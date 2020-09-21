#include <iostream>
#include "Image8.h"
#include "fract_predst.h"

double get_mse(Image8 img1, Image8 img2) {
	unsigned long long int razn = 0;
	for (int i = 0; i < img1.get_height(); i++) {
		for (int j = 0; j < img1.get_width(); j++) {
			razn += pow((img1[i][j] - img2[i][j]), 2);
		}
	}
	return razn / (img1.get_width() * img1.get_height());
}

int main() {
	Image8 image;
	image.read_image("Lena-gs.bmp");
	fract_predst f(image);
	f.build_fract();
	Image8 imag1;
	imag1.read_image("1.bmp");
	const char* a[12] = { "a.bmp", "b.bmp", "c.bmp", "d.bmp", "e.bmp", "f.bmp", "g.bmp", "h.bmp", "k.bmp", "l.bmp", "m.bmp", "n.bmp"  };

	for (int i = 0; i < 12; i++) {
		Image8 image2 = f.create_image(imag1);
		
		image2.print_image(a[i]);
		std::cout << 10 * log10(255.0 * 255.0 / get_mse(image, image2)) << std::endl;
		imag1 = image2;
	}
	int asd;
	std::cin >> asd;
	return 1;
}
