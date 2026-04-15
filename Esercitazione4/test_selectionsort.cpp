#include <vector>
#include <iostream>

#include "sorts.h"
#include "is_sorted.h"
#include "randfiller.h"

int main(void)
{
	randfiller rf; // generatore random
	
	for (int k = 0; k < 100; k++) {
		
		int size = rand() %100 +1;
		
		std::vector<int> v;
		v.resize(size);
		rf.fill(v,-100,100);
		
		selection_sort(v);
		
		if (!is_sorted(v)) {
			std::cerr << "Errore: non è ordinato" << std::endl;
			return EXIT_FAILURE;
		}
	}
	
	std::vector<std::string> vs;
	vs = { "rosso", "giallo", "verde", "blu"};
	
	selection_sort(vs);
	
	if(!is_sorted(vs)) {
		std::cerr << "Errore: vettore stringa non ordinato" << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

