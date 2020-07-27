#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "CKomplex.h"

using namespace std;



double CKomplex::re() {
	return real;
}
double CKomplex::im() {
	return imaginaer;
}
double CKomplex::abs() {
	return sqrt(real * real + imaginaer * imaginaer);
}

