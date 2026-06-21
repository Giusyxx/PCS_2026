#include <iostream>
#include <fstream>
#include <vector>
#include "maglie.hpp"
#include "gradiente_coniugato.hpp"
#include <Eigen/Dense>
#include <Eigen/SVD>

using namespace std;

struct Componente {  
	string nome;    
	double valore;  
	int nodo_from;   
	int nodo_to;     
};

int main(int argc, const char* argv[]) { 
	
	if (argc < 2) {
		cerr << "Errore: specificare il parametro (netlist)\n"; // se argc < 2 significa che non è stato passato il file come parametro
		return 1;
	}
	
	string filename = argv[1];
	ifstream ifs(filename); // apre il file passato come primo argomento
	
	if (!ifs.is_open() ) {
		cerr << "Errore: impossibile aprire il file\n";
		return 1;
	}
	undirected_graph<int> grafo;
	
	vector<Componente> resistori;
	vector<Componente> generatori;
	
	string nome;
	double valore;
	int nodo1;
	int nodo2;
	
	while (ifs >> nome >> valore >> nodo1 >> nodo2) {
		grafo.add_edge(nodo1,nodo2);
		
		Componente comp;
		comp.nome = nome;
		comp.valore = valore;
		comp.nodo_from = nodo1;
		comp.nodo_to = nodo2;
		
		if (nome[0] == 'R') {
			resistori.push_back(comp);
		} else if (nome[0] == 'V') {
			generatori.push_back(comp);
		}
	}
	
	// abbiamo costruito il grafo con i pesi
	// chiamiamo de pina per trovare i cicli fondamentali. Il risultato è un vettore di vettori: ogni elemento è una maglia scritta come sequenza di nodi.
	
	std::vector<std::vector<int>> mappa_maglie = de_pina(grafo);
	
	//CONTROLLO
	int numero_archi = grafo.all_edges().size();
	int numero_nodi = grafo.all_nodes().size();
	int numero_maglie_atteso = numero_archi - numero_nodi + 1; //|E| - |V| + 1
	
	if (mappa_maglie.size() != static_cast<size_t>(numero_maglie_atteso)) {
		cerr << "Errore: numero di maglie non coerente con |E| - |V| + 1 ";
		return 1;
	}
	
	int m = resistori.size(); // numero resistori
	int n = mappa_maglie.size(); // numero maglie
	
		Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m,n);
		Eigen::VectorXd v = Eigen::VectorXd::Zero(n);
		
		
		std::map<undirected_edge<int>, int> indice_resistore; 
		for (int i = 0; i < m; i++) {
			undirected_edge<int> arco_resistore(resistori[i].nodo_from, resistori[i].nodo_to);
			indice_resistore[arco_resistore] = i;
		}
		
		int j = 0; // colonna
		
		for (const auto& nodi_maglia : mappa_maglie) { //per ogni maglia
		if (nodi_maglia.empty()) {
			j++;
			continue;
		}
		
			// percorriamo ora le maglie
			for (size_t p = 0; p < nodi_maglia.size() -1; p ++) {
				int nodo_u = nodi_maglia[p];
				int nodo_v = nodi_maglia[p+1];
		
				//RIEMPIO LA MATRICE B
				undirected_edge<int> arco_maglia(nodo_u, nodo_v);
				auto it = indice_resistore.find(arco_maglia); 
				if ( it != indice_resistore.end()) { 
					int i = it->second; 
					if (nodo_u < nodo_v) {
						B(i,j) = 1.0;
					} else {
						B(i,j) = -1.0;
				}
			}
		
			
			//RIEMPIO IL VETTORE v (GENERATORI)
			for (size_t k = 0; k < generatori.size(); k++) {
				if (generatori[k].nodo_to == nodo_u && generatori[k].nodo_from == nodo_v) { // il generatore viene percorso da - a + nella maglia -_> contributo positivo
					v(j) += generatori[k].valore;
					break;
				} else if (generatori[k].nodo_from == nodo_u && generatori[k].nodo_to == nodo_v) { // da + a - --> contributo negativo
					v(j) -= generatori[k].valore;
					break;
				}
			}
					
		}
		
		j++;
	}
	
	
	Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m,m); // matrice R dei resistori
	for (int i = 0; i < m; i++) {
		R(i,i) = resistori[i].valore;
	}
	
	//la matrice A è data da A=B^T*R*B  e uso il gradiente coniugato per risolvere il sistema 
	Eigen::MatrixXd A = B.transpose()*R*B; 
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
	
	const unsigned int it_max = 10000;
	const double res_tol = 1.0e-12;
	unsigned int it = 0;
	
	Eigen::VectorXd I = gradiente_coniugato ( A, v, x0, res_tol, it_max, it);
	
	//ora le tensioni V
	Eigen::VectorXd V = R*B*I;
	Eigen::VectorXd I_reali = B * I;
	
	// STAMPA DEI RISULTATI
	for (int i = 0; i < m; i++) {
		std::cout << resistori[i].nome << ": V = " << V(i) << " volts, I = " << I_reali(i) << " amps." << std::endl;
	}

	return 0;
}
