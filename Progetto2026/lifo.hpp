#pragma once
#include <list>
#include <stdexcept>  

template<typename T>
class lifo {
	std::list<T> stack;

public:
	// costruttore di default
	lifo() = default;
	
	// put: inserisce un elemento in cima allo stack
	void put(const T& elemento) {
		stack.push_back(elemento);
	}
	
	// get: estrae l'elemento sulla cima dello stack
	T get() {
		T elemento = stack.back(); // trovo l'elemento in cima alla lista (ultimo) 
		stack.pop_back(); // rimuovo il primo elemento
		return elemento;
	}
	
	// empty: verifica se lo stack è vuoto
	bool empty() const {
		return stack.empty();
	}
};
	                                                                                  