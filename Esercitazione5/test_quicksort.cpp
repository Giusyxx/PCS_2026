#include <vector>
#include <iostream>

#include "sorts.hpp"
#include "is_sorted.h"
#include "randfiller.h"

int main(void) {
	
	randfiller rf; // generatore random
	
	for (int k = 0; k < 100; k++) {
		
		int size = rand() %100 +1;
		
		std::vector<int> vec;
		vec.resize(size);
		rf.fill(vec,-100,100);
		
		quick_sort(vec, 0 , size -1);
		
		if (!is_sorted(vec)) {
			std::cerr << "Errore: non è ordinato" << std::endl;
			return EXIT_FAILURE;
		}
	}
	
	std::vector<std::string> vs;
	vs = { "rosso", "giallo", "verde", "blu", "arancione", "viola", "nero", "bianco", "azzurro", "marrone"};
	
	quick_sort(vs, 0 , vs.size()- 1);
	
	if(!is_sorted(vs)) {
		std::cerr << "Errore: vettore stringa non ordinato" << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
