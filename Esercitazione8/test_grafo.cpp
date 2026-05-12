#include <iostream> 
#include "undirected_graph.hpp" 
#include "undirected_edge.hpp"
#include <set>
#include <map>


int main() {
	// creo un grafo
	undirected_graph<int> grafo;
	grafo.add_edge(1,2);
	grafo.add_edge(2,1); // non dovrebbe essere aggiunto perchè è un duplicato
	grafo.add_edge(2,3);
	
	// test per all_edges: restituisce tutti gli archi del grafo
	std::cout << "Archi del grafo: " << std::endl;
	std::set<undirected_edge<int>> tutti_archi = grafo.all_edges() ;
	for (const auto& arco : tutti_archi) {
		std::cout << arco << std::endl;
	}
		
	// test per all_nodes: restituisce tutti i nodi del grafo
	std::cout << "Nodi del grafo: " << std::endl;
	std::set<int> tutti_nodi = grafo.all_nodes() ; // questo metodo restituusce il set
	for (const auto& nodo : tutti_nodi) {
		std::cout << nodo << std::endl;
	}
		
	// test per neighbours: restituisce i vicini del nodo 2 -> dovrebbero essere 1 e 3
	std::cout << "Vicini del nodo 2: " << std::endl;
	std::set<int> vicini = grafo.neighbours(2) ;
	for (const auto& vicini_2 : vicini) {
		std::cout << vicini_2 << std::endl;
	}
	
	// test per edge_number: restituisce il numero dell'arco
	undirected_edge<int> arco_test(1,2);
	int numero_arco = grafo.edge_number(arco_test);
	std::cout << "Numero dell'arco (1,2): " << numero_arco << std::endl;
	
	// test per edge_at(): restituisce l'arco corrispondente al numero 1
	undirected_edge<int> arco_at_numero = grafo.edge_at(1);
	std::cout << "Arco corrispondente al numero 1: " << arco_at_numero << std::endl;
	
	// test per operator-(): calcola la differenza tra due grafi
	undirected_graph<int> altro_grafo;
	altro_grafo.add_edge(2,3); // aggiungo un arco che è presente in grafo
	altro_grafo.add_edge(3,4); // aggiungo un arco che non è presente in grafo 
	undirected_graph<int> grafo_differenza = grafo - altro_grafo; // dovrebbe contenere solo (1,2) 
	std::cout << "Archi del grafo differenza: " << std::endl;
	std::set<undirected_edge<int>> archi_differenza = grafo_differenza.all_edges() ;
	for (const auto& arco : archi_differenza) {
		std::cout << arco << std::endl;
	}
	
	return 0;
}
	
		