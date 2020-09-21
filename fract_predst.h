#pragma once
#include <vector>
#include "Image8.h"



/*
0 - прямо
1 - на право
2 - вниз
3 - влево
4 - 7 - отраженное тоже самое
*/
struct el_fract {
	int x, y, n;
	double koef1, koef2;
};

struct number {
	int x, y;
};

class fract_predst
{
	Image8 image;
	
	std::vector<std::vector<unsigned int>> integr_predst;
	std::vector<std::vector<el_fract>> fract;
	std::vector<std::vector<el_fract>> fract1;
	std::vector<std::vector<number>> klass;
	std::vector<std::pair<int, int>> norm;
	std::vector<std::pair<int, int>> ne_norm;
	double koef1;
	double koef2;


	void get_integr_predst();

	int get_klass(int i, int j, int n);

	void klassification();

	int raven(int x1, int y1, std::vector<std::vector<int>>, int shag, const int razm);
	std::vector<std::vector<BYTE>> get_kusok(Image8, el_fract, int shag);

	std::vector<std::vector<int>> get_im(Image8 image2, int n1, int n2, int p);
	std::vector<std::vector<int>> get_im(int n1, int n2, int p, const int razm);
	std::vector<double> get_koef(int x1, int y1, std::vector<std::vector<int>>);
	
	
public:
	void build_fract();
	Image8 create_image(Image8);
	fract_predst(Image8 i) { image = i; }
	~fract_predst(){}
};
