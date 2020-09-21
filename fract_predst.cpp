#include "fract_predst.h"

#include <iostream>
void fract_predst::get_integr_predst()
{
	integr_predst = std::vector<std::vector<unsigned int>>(image.get_height());
	std::vector<std::vector<unsigned int>> stolb1(image.get_height());
	for (int i = 0; i < image.get_height(); i++) {
		std::vector<unsigned int > str(image.get_width());
		std::vector<unsigned int > stolb(image.get_width());
		for (int j = 0; j < image.get_width(); j++) {
			if (i == 0) {
				if (j == 0) {
					str[0] = image[i][j];
					stolb[0] = image[i][j];
				}
				else {
					str[j] = str[j - 1] + image[i][j];
					stolb[j] = image[i][j];
				}
			}
			else {
				if (j == 0) {
					stolb[j] = stolb1[i - 1][j] + image[i][j];
					str[j] = stolb[j];
				}
				else {
					stolb[j] = stolb1[i - 1][j] + image[i][j];
					str[j] = str[j - 1] + stolb[j];
				}
			}
		}
		integr_predst[i] = str;
		stolb1[i] = stolb;
	}
}

int fract_predst::get_klass(int i, int j, int n)
{
	int otv = 0;
	int summ = 0;
	int summ00 = 0, summ01 = 0, summ10 = 0, summ11 = 0;
	if (i == 0) {
		if (j == 0) {
			summ = integr_predst[i + n - 1][j + n - 1];
			summ00 = integr_predst[i + (n / 2) - 1][j + (n / 2) - 1];
			summ01 = integr_predst[i + (n / 2) - 1][j + n - 1] - summ00;
			summ10 = integr_predst[i + n - 1][j + (n / 2) - 1] - summ00;
			summ11 = summ - summ01 - summ10 - summ00;
		}
		else {
			summ = integr_predst[i + n - 1][j + n - 1] - integr_predst[i + n - 1][j - 1];
			summ00 = integr_predst[i + (n / 2) - 1][j + (n / 2) - 1] - integr_predst[i + (n / 2) - 1][j - 1];
			summ01 = integr_predst[i + (n / 2) - 1][j + n - 1] - integr_predst[i + n / 2 - 1][j + n / 2 - 1];
			summ10 = integr_predst[i + n - 1][j + (n / 2) - 1] - integr_predst[i + n - 1][j - 1] - summ00;
			summ11 = summ - summ01 - summ10 - summ00;
		}
		
	}
	else {
		if (j == 0) {
			summ = integr_predst[i + n - 1][j + n - 1] - integr_predst[i - 1][j + n - 1];
			
			summ00 = integr_predst[i + (n / 2) - 1][j + (n / 2) - 1] - integr_predst[i - 1][j + (n / 2) - 1];
			summ01 = integr_predst[i + (n / 2) - 1][j + n - 1] - integr_predst[i - 1][j + n - 1] - summ00;
			summ10 = integr_predst[i + n - 1][j + (n / 2) - 1] - integr_predst[i + n / 2 - 1][j + n / 2 - 1];
			summ11 = summ - summ01 - summ10 - summ00;
		}
		else {
			summ = integr_predst[i + n - 1][j + n - 1] - integr_predst[i - 1][j + n - 1] - integr_predst[i + n - 1][j - 1] + integr_predst[i - 1][j - 1];
			summ00 = integr_predst[i + (n / 2) - 1][j + (n / 2) - 1] - integr_predst[i - 1][j + (n / 2) - 1] - integr_predst[i + n / 2 - 1][j - 1] + integr_predst[i - 1][j - 1];
			summ01 = integr_predst[i + (n / 2) - 1][j + n - 1] - integr_predst[i - 1][j + n - 1] - integr_predst[i + n / 2 - 1][j + n / 2 - 1] + integr_predst[i - 1][j + n / 2 - 1];
			summ10 = integr_predst[i + n - 1][j + (n / 2) - 1] - integr_predst[i + n / 2 - 1][j + n / 2 - 1] - integr_predst[i + n - 1][j - 1] + integr_predst[i + n / 2 - 1][j - 1];
			summ11 = summ - summ01 - summ10 - summ00;

		}
	}
	int sr = summ / (n * n);
	int sr00 = summ00 / (n * n / 4), sr01 = summ01 / (n * n / 4), sr10 = summ10 / (n * n / 4), sr11 = summ11 / (n * n / 4);

	if (sr00 > sr) {
		otv = 8;
	}
	if (sr01 > sr) {
		otv += 4;
	}
	if (sr10 > sr) {
		otv += 1;
	}
	if (sr11 > sr) {
		otv += 2;
	}
	return otv;
}

void fract_predst::klassification()
{
	klass = std::vector<std::vector<number>>(16);
	for (int i = 0; i < 16; i++) {
		std::vector<number> str;
		
		klass[i] = str;
	}
	for (int j = 0; j < 248; j+=2) {
		for (int k = 0; k < 248; k+=2) {
			number nu;
			nu.x = j;
			nu.y = k;
			klass[get_klass(j, k, 8)].push_back(nu);
		}
			
	}
}

int fract_predst::raven(int x1, int y1, std::vector<std::vector<int>> mas, int shag, const int razm)
{
	int rasst = 0;
	std::vector<std::vector<int>> new_mas(razm);
	int x = 0, y = 0;
	for (int i = 0; i < 8; i += shag) {
		new_mas[x] = std::vector<int>(razm);
		for (int j = 0; j < 8; j += shag) {
			int c = 0;
			for (int k = 0; k < shag; k++) {
				for (int p = 0; p < shag; p++) {
					c += mas[i + k][j + p];
				}
			}
			new_mas[x][y] = c / 4;
			//new_mas[x][y] = (mas[i][j] + mas[i][j + 1] + mas[i + 1][j] + mas[i + 1][j + 1]) / 4;

			y += 1;
		}
		x += 1;
		y = 0;
	}
	double sr1 = 0;
	double sr2 = 0;
	double disp1 = 0;
	double disp2 = 0;
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) {
			rasst += pow(abs(new_mas[i][j] - image[x1 + i][y1 + j]), 2);
			sr1 += new_mas[i][j];
			sr2 += image[x1 + i][y1 + j];
		}
	}
	sr1 = sr1 / 16;
	sr2 = sr2 / 16;
	for (int i = 0; i < razm; i++) {
		for (int j = 0; j < razm; j++) {
			disp1 += (new_mas[i][j] - sr1) * (image[x1 + i][y1 + j] - sr2);
			disp2 += pow(image[x1 + i][y1 + j] - sr2, 2);
		}
	}

	
	disp1 = disp1 / 15;
	disp2 = disp2 / 15;

	koef1 = disp1 / disp2;
	koef2 = sr2 - koef1 * sr1;
	return pow(rasst, 0.5);
}

std::vector<std::vector<BYTE>> fract_predst::get_kusok(Image8 im, el_fract el, int shag)
{
	std::vector<std::vector<BYTE>> mas(shag);
	std::vector<std::vector<int>> m = get_im(im, el.x, el.y, el.n);
	for (int i = 0; i < shag; i++) {
		std::vector<BYTE> line(shag);
		for (int j = 0; j < shag; j++) {
			int c = 0;
			for (int k = 0; k < (8 / shag); k++) {
				for (int p = 0; p < (8 / shag); p++) {
					c += m[i * (8 / shag) + k][j * (8 / shag) + p];
				}
			}
			//line[j] = (m[i * 2][j * 2] + m[i * 2][j * 2 + 1] + m[i * 2 + 1][j * 2] + m[i * 2 + 1][j * 2 + 1]) / 4;
			line[j] = c / 4;
		}
		mas[i] = line;
	}
	return mas;
}

std::vector<std::vector<int>> fract_predst::get_im(Image8 image2, int n1, int n2, int p)
{
	std::vector<std::vector<int>> mas(8);
	for (int i = 0; i < 8; i++) {
		mas[i] = std::vector<int>(8);
	}

	if (p == 0) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[i][j] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 1) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[j][7 - i] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 2) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[7 - i][7 - j] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 3) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[7 - j][i] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 4) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[i][7 - j] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 5) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[7 - j][7 - i] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 6) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[7 - i][j] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 7) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				mas[j][i] = image2[n1 + i][n2 + j];
			}
		}
		return mas;
	}
}

std::vector<std::vector<int>> fract_predst::get_im(int n1, int n2, int p, const int razm)
{
	std::vector<std::vector<int>> mas(razm);
	for (int i = 0; i < razm; i++) {
		mas[i] = std::vector<int>(razm);
	}

	if (p == 0) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[i][j] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 1) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[j][7 - i] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 2) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[7 - i][7 - j] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 3) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[7 - j][i] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 4) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[i][7 - j] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 5) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[7 - j][7 - i] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 6) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[7 - i][j] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
	if (p == 7) {
		for (int i = 0; i < razm; i++) {
			for (int j = 0; j < razm; j++) {
				mas[j][i] = image[n1 + i][n2 + j];
			}
		}
		return mas;
	}
}

std::vector<double> fract_predst::get_koef(int x1, int y1, std::vector<std::vector<int>> mas)
{
	int rasst = 0;
	int new_mas[4][4];
	int x = 0, y = 0;
	for (int i = 0; i < 8; i += 2) {
		for (int j = 0; j < 8; j += 2) {
			new_mas[x][y] = (mas[i][j] + mas[i][j + 1] + mas[i + 1][j] + mas[i + 1][j + 1]) / 4;
			y += 1;
		}
		x += 1;
		y = 0;
	}

	double sr1 = 0;
	double sr2 = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sr1 += new_mas[i][j];
			sr2 += image[x1 + i][y1 + j];
		}
	}
	sr1 = sr1 / 16;
	sr2 = sr2 / 16;
	return std::vector<double>(2);
	//return sr2 / sr1;
}


std::vector<int> get_vse(int kl) {
	std::vector<int> mas_kl(8);
	for (int t = 0; t < 4; t++) {
		mas_kl[t] = kl;
		kl = ((kl & 0b0001) << 3) | (kl >> 1);
	}

	int ch1 = kl % 2;
	kl /= 2;
	int ch2 = kl % 2;
	kl /= 2;
	int ch3 = kl % 2;
	kl /= 2;
	int ch4 = kl % 2;
	kl = ch3 * 8 + ch4 * 4 + ch1 * 2 + ch2;
	for (int t = 4; t < 8; t++) {
		mas_kl[t] = kl;
		kl = ((kl & 0b0001) << 3) | (kl >> 1);
	}
	return mas_kl;
}

void fract_predst::build_fract()
{
	get_integr_predst();
	klassification();
	fract = std::vector<std::vector<el_fract>>(64);
	fract1 = std::vector<std::vector<el_fract>>(128);
	for (int i = 0; i < 64; i++) {
		fract[i] = std::vector<el_fract>(64);
		fract1[i] = std::vector<el_fract>(128);
		fract1[i + 64] = std::vector<el_fract>(128);
	}
	for (int i = 0; i < 64; i++) {
		std::cout << i << std::endl;
		for (int j = 0; j < 64; j++) {
			int kl1 = get_klass(i * 4, j * 4, 4);
			el_fract minim;
			int min_dest = 10000000;
			std::vector<number> pr = klass[kl1];
			int p = 0;
			for (number k : pr)
			{
				std::vector<int> mas_kl = get_vse(kl1);

				for (int t = 0; t < 8; t++) {
					if (kl1 == mas_kl[t]) {
						std::vector<std::vector<int>> prom = get_im(k.x, k.y, t, 8);
						int d = raven(i * 4, j * 4, prom, 2, 4);
						if (d < min_dest) {
							min_dest = d;
							minim.n = t;
							minim.x = k.x;
							minim.y = k.y;
							minim.koef1 = koef1;
							minim.koef2 = koef2;
						}
					}

				}
			}

			if (min_dest <= 68) {
			fract[i][j] = minim;
			norm.push_back(std::pair<int, int>(i, j));
			}
			else {
				int kl1 = get_klass(i * 4, j * 4, 2);
				int kl2 = get_klass(i * 4, j * 4 + 2, 2);
				int kl3 = get_klass(i * 4 + 2, j * 4, 2);
				int kl4 = get_klass(i * 4 + 2, j * 4 + 2, 2);
				int min_dest1 = 10000000;
				el_fract minim1;
				int min_dest2 = 10000000;
				el_fract minim2;
				int min_dest3 = 10000000;
				el_fract minim3;
				int min_dest4 = 10000000;
				el_fract minim4;

				std::vector<number> pr = klass[kl1];

				for (number k : pr)
				{
					std::vector<int> mas_kl1 = get_vse(kl1);
					for (int t = 0; t < 8; t++) {
						if (kl1 == mas_kl1[t]) {
							std::vector<std::vector<int>> prom = get_im(k.x, k.y, t, 8);
							int d = raven(i * 4, j * 4, prom, 4, 2);
							if (d < min_dest1) {
								min_dest1 = d;
								minim1.n = t;
								minim1.x = k.x;
								minim1.y = k.y;
								minim1.koef1 = koef1;
								minim1.koef2 = koef2;
							}
						}
					}
				}
				pr = klass[kl2];

				for (number k : pr)
				{
					std::vector<int> mas_kl2 = get_vse(kl2);
					for (int t = 0; t < 8; t++) {
						if (kl2 == mas_kl2[t]) {
							std::vector<std::vector<int>> prom = get_im(k.x, k.y, t, 8);
							int d = raven(i * 4, j * 4 + 2, prom, 4, 2);
							if (d < min_dest2) {
								min_dest2 = d;
								minim2.n = t;
								minim2.x = k.x;
								minim2.y = k.y;
								minim2.koef1 = koef1;
								minim2.koef2 = koef2;
							}
						}
					}
				}
				pr = klass[kl3];

				for (number k : pr)
				{
					std::vector<int> mas_kl3 = get_vse(kl3);
					for (int t = 0; t < 8; t++) {
						if (kl3 == mas_kl3[t]) {
							std::vector<std::vector<int>> prom = get_im(k.x, k.y, t, 8);
							int d = raven(i * 4 + 2, j * 4, prom, 4, 2);
							if (d < min_dest3) {
								min_dest3 = d;
								minim3.n = t;
								minim3.x = k.x;
								minim3.y = k.y;
								minim3.koef1 = koef1;
								minim3.koef2 = koef2;
							}
						}
					}
				}
				pr = klass[kl4];

				for (number k : pr)
				{
					std::vector<int> mas_kl4 = get_vse(kl4);
					for (int t = 0; t < 8; t++) {
						if (kl4 == mas_kl4[t]) {
							std::vector<std::vector<int>> prom = get_im(k.x, k.y, t, 8);
							int d = raven(i * 4 + 2, j * 4 + 2, prom, 4, 2);
							if (d < min_dest4) {
								min_dest4 = d;
								minim4.n = t;
								minim4.x = k.x;
								minim4.y = k.y;
								minim4.koef1 = koef1;
								minim4.koef2 = koef2;
							}
						}
					}
				}

				int cou = 0;
				if (min_dest < min_dest1) {
					cou++;
				}
				if (min_dest < min_dest2) {
					cou++;
				}
				if (min_dest < min_dest3) {
					cou++;
				}
				if (min_dest < min_dest4) {
					cou++;
				}
				if (cou > 2) {
					fract[i][j] = minim;
					norm.push_back(std::pair<int, int>(i, j));
				}
				else {
					ne_norm.push_back(std::pair<int, int>(i, j));
					fract1[i * 2][j * 2] = minim1;
					fract1[i * 2][j * 2 + 1] = minim2;
					fract1[i * 2 + 1][j * 2] = minim3;
					fract1[i * 2 + 1][j * 2 + 1] = minim4;
				}

			}
		

		}
	}
}

Image8 fract_predst::create_image(Image8 image1)
{
	Image8 im(256, 256, image1.get_colors(), image1.get_file(), image1.get_info());
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			if (std::find(norm.begin(), norm.end(), std::pair<int, int>(i, j)) != norm.end()) {
				std::vector<std::vector<BYTE>> v = get_kusok(image1, fract[i][j], 4);
				for (int k = 0; k < 4; k++) {
					for (int p = 0; p < 4; p++) {

						im[i * 4 + k][j * 4 + p] = v[k][p] * fract[i][j].koef1 + fract[i][j].koef2;
					}
				}
			}
			else {
				std::vector<std::vector<BYTE>> v = get_kusok(image1, fract1[i * 2][j * 2], 2);
				for (int k = 0; k < 2; k++) {
					for (int p = 0; p < 2; p++) {

						im[i * 4 + k][j * 4 + p] = v[k][p] * fract1[i * 2][j * 2].koef1 + fract1[i * 2][j * 2].koef2;
					}
				}
				v = get_kusok(image1, fract1[i * 2][j * 2 + 1], 2);
				for (int k = 0; k < 2; k++) {
					for (int p = 0; p < 2; p++) {

						im[i * 4 + k][j * 4 + 2 + p] = v[k][p] * fract1[i * 2][j * 2+ 1].koef1 + fract1[i * 2][j * 2 + 1].koef2;
					}
				}
				v = get_kusok(image1, fract1[i * 2 + 1][j * 2], 2);
				for (int k = 0; k < 2; k++) {
					for (int p = 0; p < 2; p++) {

						im[i * 4 + k + 2][j * 4 + p] = v[k][p] * fract1[i * 2 + 1][j * 2].koef1 + fract1[i * 2 + 1][j * 2].koef2;
					}
				}
				v = get_kusok(image1, fract1[i * 2 + 1][j * 2 + 1], 2);
				for (int k = 0; k < 2; k++) {
					for (int p = 0; p < 2; p++) {

						im[i * 4 + 2 + k][j * 4 + 2 + p] = v[k][p] * fract1[i * 2 + 1][j * 2 + 1].koef1 + fract1[i * 2 + 1][j * 2 + 1].koef2;
					}
				}

			}
			
			
		}
	}
	return im;
}
