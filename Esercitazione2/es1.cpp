# include <iostream>

int main() {
	double ad[4] =  {0.0, 1.1, 2.2, 3.3};
	float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
	int ai[3] = {0, 1, 2};
	
	int x = 1;
	float y = 1.1;
	
	(&y)[1] = 0;
	
	std::cout << &x << "\n"; //stampo l'indirizzo di x: 0xffffdcef68ec : 844
	std::cout << &y << "\n"; //stampo l'indirizzo di y: 0xffffdcef68e8 : 840
	
	std::cout << x << "\n"; // 0
	
	std::cout << &ad[2] << "\n"; // 0xffffdcef6930 : 912

	std::cout << &ad[0] << "\n"; // 0xffffdcef6920 : 896
	std::cout << &ad[1] << "\n"; // 0xffffdcef6928 : 904
	
	std::cout << &af[0] << "\n"; // 0xffffdcef6900 : 864
	std::cout << &af[1] << "\n"; // 0xffffdcef6904 : 868
	
	std::cout << &ai[0] << "\n"; // 0xffffdcef68f0 : 848
	std::cout << &ai[1] << "\n"; // 0xffffdcef68f4 : 852
	std::cout << &ai[2] << "\n"; // 0xffffdcef68f8 : 856
	
	return 0;
	
}