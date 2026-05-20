#pragma once
#include <iostream>
#include <algorithm> 


// si implementi una classe undirected_eddge che rappresenta un arco in un grafo non diretto. La classe deve
//avere un costruttore che permette di specificare i due nodi connessi dall’arco, inoltre devono esserci
//due metodi from() e to() che restituiscono i due nodi.

template <typename T>
class undirected_edge {
    T nodo1;
	T nodo2;
public:
// Costruttore di default 
	undirected_edge(T u, T v) {
		// Garantisce che from sia sempre <= to
		if (u < v) {
			nodo1 = u;
			nodo2 = v;
			} else {
                nodo1 = v ;
				nodo2 = u;
            }
    }

// Metodo from() che restituisce il nodo minore

    T from() const {
        return nodo1;
    }

// Metodo to() che restituisce il nodo maggiore

    T to() const {
        return nodo2;
    }

// operator< per ordinare gli archi
    bool operator<(const undirected_edge& other) const {
        if (nodo1 == other.nodo1) {
            return nodo2 < other.nodo2;
        }
        return nodo1 < other.nodo1;
    }
// operator==: due archi sono uguali eìse hanno gli stessi nodi
    bool operator==(const undirected_edge& other) const {
        return (nodo1 == other.nodo1 && nodo2 == other.nodo2);
    }

// operator<< per stampare l'arco
    //dichiaro l'operatore come friend per accedere ai membri privati della classe
    friend std::ostream& operator<<(std::ostream& os, const undirected_edge& edge) {
        os << "(" << edge.nodo1 << ", " << edge.nodo2 << ")";
        return os;
    }
};