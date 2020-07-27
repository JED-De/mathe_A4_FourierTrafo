#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class CKomplex
{
private:
	double real;
	double imaginaer;


public:
	CKomplex() {
		real = 0;
		imaginaer = 0;
	}
	CKomplex(double a, double b) {
		real = a;
		imaginaer = b;
	}
	CKomplex(double phi) {
		real = cos(phi);
		imaginaer = sin(phi);
	}
	double re();
	double im();
	double abs();
};

inline CKomplex operator *(CKomplex a, CKomplex b) {
	CKomplex mult((a.re()*b.re() - a.im()*b.im()), (a.re() * b.im() + a.im() * b.re()));
	return mult;
};
inline CKomplex operator +(CKomplex a, CKomplex b) {
	CKomplex add(a.re() + b.re(), a.im() + b.im());
	return add;
}
inline CKomplex operator *(double x, CKomplex y) {
	CKomplex mult2(x*y.re(), x* y.im());
	return mult2;
}