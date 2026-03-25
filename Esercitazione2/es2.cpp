#include <iostream>
#include <cmath>

using namespace std;

int main() {
	static const int N = 7;
	double arr[N] = {8.5, 6.9, 2.2, 4.0, 1.3, 0.1, 9.7};
	
	double minimo = arr[0];
	double massimo = arr[0];
	double sum = 0;
	
	
	for (int i= 0; i < N; i ++) {
		minimo = min(minimo,arr[i]);
		massimo = max(massimo,arr[i]);
		sum = sum + arr[i];
	}
	
	double media = sum / N;
	
	double scarto_quad = 0;
		
	for (int i = 0; i < N; i ++) {
		scarto_quad = scarto_quad + (arr[i] - media) * (arr[i] - media);
	}
	
	double varianza = scarto_quad / N;
	double dev_std = sqrt(varianza);
		
	
	cout << "minimo:" << minimo << "\n";
	cout << "massimo:" << massimo << "\n";
	cout << "media:" << media << "\n";
	cout << "deviazione standard:" << dev_std << "\n";
	
	return 0;
}