#include <iostream>
#include "rational.hpp"

int main() {
	rational<int> a(3,6);
	rational<int> b(1,2);
	
	std::cout << a << "\n"; // semplificazione 
	
	
	rational<int> c = a + b;
	std::cout << "a + b = " << c << "\n"; // somma usando l'op binario +
	
	rational<int> d = a * b;
	std::cout << "a * b = " << d << "\n"; // prodotto usando l'op binario *
	
	rational<int> e = a - b;
	std::cout << "a - b = " << e << "\n"; // sottrazione
	
	rational<int> f = a/b;
	std::cout << "a / b = " << f << "\n";
	
	rational<int> inf(1,0);
	rational<int> g(2,1);
	std::cout << "inf + g = " << inf + g << "\n";
	
	rational<int> nan = inf - inf;
	std::cout << "Inf - Inf = " << nan << "\n";
	
	return 0;
}