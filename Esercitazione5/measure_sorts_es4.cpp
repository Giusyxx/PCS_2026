#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "timecounter.h"
#include "randfiller.h"
#include "sorts.h"

int main(void)
{
	randfiller rf;
	timecounter tc;
	
	for (int n = 4; n <= 8192; n *= 2) {
		
		std::vector<int> v(n);
		rf.fill(v, -1000, 1000);
		
		std::vector<int> v1 = v;
		std::vector<int> v2 = v;
		std::vector<int> v3 = v;
		std::vector<int> v4 = v;
		
		tc.tic();
		bubble_sort(v1);
		double secs_bubble = tc.toc();
		
		tc.tic();
		insertion_sort(v2);
		double secs_insertion = tc.toc();
		
		tc.tic();
		selection_sort(v3);
		double secs_selection = tc.toc();
		
		tc.tic();
		std::sort( v4.begin(), v4.end() );
		double secs_sort = tc.toc();
		
		std::cout << "n = " << n << ";" << "bubble: " << secs_bubble << ";"
										<< "insertion: " << secs_insertion << ";"
										<< "selection: " << secs_selection << ";"
										<< "std::sort:" << secs_sort << "\n";
	}
	return 0;
}
		