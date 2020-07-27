#include <fstream>   
#include <vector>
#include "CKomplex.h"
#include <math.h>
#include <streambuf>
#include <algorithm>
using namespace std;

const long double PI = 3.14159265358979323846;

vector<CKomplex>  werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	for(int i = 0; i < N; i++){
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}


vector<CKomplex> Fourier(vector<CKomplex> f, bool HinRueck)
{
	vector<CKomplex> C;
	int N = f.size();
	C.resize(N);
	for (int n = 0; n < N; n++)
	{
		CKomplex sum(0, 0);
		for (int k = 0; k < N; k++)
		{
			double phi = ((HinRueck ? -1.0 : 1.0) * (2.0 * k * n * PI)) / N;
			CKomplex phi_tmp(phi);
			sum = sum + phi_tmp * f[k];
		}
		C[n] = (1.0 / sqrt(N)) * sum;
	}
	return C;
}

void abweichung(vector<CKomplex> a, vector<CKomplex> b, double epsilon) {
	double err = 0, tmp = 0;
	for (unsigned int i = 0; i < a.size(); i++) {
		err = max(err, abs(a[i].abs() - b[i].abs()));
	}

	std::cout << "Die maximale Abweichung bei e = " << epsilon << " liegt bei " << err << std::endl;
}


int main() {
	vector<CKomplex> input_ori = werte_einlesen("Daten_original.txt");
	vector<CKomplex> input = werte_einlesen("Daten_original.txt");
	vector<CKomplex> output =  Fourier(input, true);

	werte_ausgeben("Daten_hin_-1.txt", output, -1.0);
	input = werte_einlesen("Daten_hin_-1.txt");
	output = Fourier(input, false);
	werte_ausgeben("Daten_rueck_-1.txt", output, -1.0);
	abweichung(input_ori, output, -1.0);

	input = werte_einlesen("Daten_original.txt");
	output = Fourier(input, true);
	werte_ausgeben("Daten_hin_0,1.txt", output, 0.1);
	input = werte_einlesen("Daten_hin_0,1.txt");
	output = Fourier(input, false);
	werte_ausgeben("Daten_rueck_0,1.txt", output, 0.1);
	abweichung(input_ori, output, 0.1);


	input = werte_einlesen("Daten_original.txt");
	output = Fourier(input, true);
	werte_ausgeben("Daten_hin_1,0.txt", output, 1.0);
	input = werte_einlesen("Daten_hin_1,0.txt");
	output = Fourier(input, false);
	werte_ausgeben("Daten_rueck_1,0.txt", output, 1.0);
	abweichung(input_ori, output, 1.0);

	system("PAUSE");
	return 0;
}