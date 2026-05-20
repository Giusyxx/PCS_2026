#pragma once
#include <list>
#include <stdexcept>  

template<typename T>
class fifo {
	std::list<T> coda;

public:
	// costruttore di default
	fifo() = default;
	
	// put: inserisce un elemento in fondo alla coda
	void put(const T& elemento) {
		coda.push_back(elemento);
	}
	
	// get: estrae l'elemento in testa alla coda
	T get() {
		T elemento = coda.front(); // trovo l'elemento in testa alla lista
		coda.pop_front(); // rimuovo il primo elemento
		return elemento;
	}
	
	// empty: verifica se la coda è vuota
	bool empty() const {
		return coda.empty();
	}
};
	                                                                                  